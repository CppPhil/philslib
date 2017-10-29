/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#include "../../../include/pl/thd/thread_pool.hpp"
#include "../../../include/pl/byte.hpp" // pl::Byte
#include "../../../include/pl/algo/destroy.hpp" // pl::algo::destroy
#include <ciso646> // not, or
#include <new> // new
#include <memory> // std::addressof
#include <algorithm> // std::for_each

namespace pl
{
namespace thd
{
ThreadPool::ThreadPool(std::size_t amtThreads)
    : m_tasksShared{ },
      m_mutex{ },
      m_cv{ },
      m_isFinishedShared{ false }, // start out not finished
      m_threadCount{ amtThreads },
      m_threads{ // get the memory needed for the threads.
                 // the unique_ptr will deallocate the memory automatically.
          std::make_unique<pl::Byte[]>(m_threadCount * sizeof(std::thread))
      },
      m_threadBegin{ // begin iterator to the range of threads
          reinterpret_cast<std::thread *>(m_threads.get())
      },
      m_threadEnd{ m_threadBegin + m_threadCount } // end iterator.
                                                   // is out of bounds.
{
    // pointer to the ThreadPool
    // used in the lambda below.
    auto self = this;

    // construct the threads into the raw memory.
    // start running the thread running the threadFunction which is a
    // non-static member function of ThreadPool.
    std::for_each(m_threadBegin, m_threadEnd,
                  [self] (PL_OUT std::thread &t) {
        ::new(static_cast<void *>(std::addressof(t))) std::thread{ &ThreadPool::threadFunction, self };
    });
}

ThreadPool::~ThreadPool()
{
    // join the threads
    // this will shut all the threads down and then actually join them.
    join();

    /* Call the destructors of the threads.
     * the unique_ptr will only free the raw memory of pl::Bytes.
    **/
    algo::destroy(m_threadBegin, m_threadEnd);
}

PL_NODISCARD std::size_t ThreadPool::getThreadCount() const
{
    return m_threadCount; // return the requested constant.
}

PL_NODISCARD std::size_t ThreadPool::tasksWaitingForExecution() const
{
    // lock the mutex,
    // the queue of tasks is shared data
    // the threads of the thread pool remove tasks from it.
    std::unique_lock<std::mutex> lock{ m_mutex };
    return m_tasksShared.size(); // return the number of tasks still to be run.
}

ThreadPool::ExecutorBase::ExecutorBase(std::uint8_t p)
    : m_priority{ p } // just set the priority
{
}

ThreadPool::ExecutorBase::~ExecutorBase()
{
}

bool operator<(
    PL_IN const ThreadPool::ExecutorBase &a,
    PL_IN const ThreadPool::ExecutorBase &b)
{
    return a.m_priority < b.m_priority; // compare the priorities stored.
}

void ThreadPool::threadFunction()
{
    // by default we're running.
    auto running = true;

    while (running) {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cv.wait(lock, // wait until shutdown or got task to run.
                  [this] {
                       return m_isFinishedShared
                              or not m_tasksShared.empty();
                   });

        // if we woke up because there's a task to run.
        if (not m_tasksShared.empty()) {
            auto task = m_tasksShared.top(); // get the highest priority task.
            m_tasksShared.pop(); // remove it from the queue
            lock.unlock(); // unlock the mutex, we're not accessing shared data
                           // any more, the task is local to this thread.
            (*task)(); // run your task.
        } else {
            // if there was no task.
            // set running to false if we're shutting down.
            running = !m_isFinishedShared;
            // exit the loop if we're shutting down.
            // if running is still true it was just a spurious wake.
        }
    }
}

void ThreadPool::join()
{
    {
        // lock the mutex, the boolean flag is shared data.
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_isFinishedShared = true;
    }

    // wake all threads, we're shutting down.
    m_cv.notify_all();

    // join every thread.
    std::for_each(
        m_threadBegin,
        m_threadEnd,
        [] (PL_INOUT std::thread &t) {
            t.join();
        }
    );
}
} // namespace thd
} // namespace pl
