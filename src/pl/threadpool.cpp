#include "../../include/pl/threadpool.hpp"
#include "../../include/pl/byte.hpp" // pl::Byte
#include <ciso646> // not, or
#include <algorithm> // std::for_each
#include <new> // new

namespace pl
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
                  [self, this] (PL_OUT std::thread &t) {
        new (&t) std::thread{ &ThreadPool::threadFunction, self };
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
    std::for_each(m_threadBegin, m_threadEnd,
                  [] (PL_OUT std::thread &t) {
        t.~thread();
    });
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

PL_NODISCARD bool operator<(PL_IN const ThreadPool::ExecutorBase &a,
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
    std::for_each(m_threadBegin, m_threadEnd,
                  [] (PL_OUT std::thread &t) {
        t.join();
    });
}
} // namespace pl
