#include "include/threadpool.hpp"
#include <cstdint> // std::uint8_t
#include <future> // std::promise
#include <utility> // std::move
#include <exception> // std::current_exception
#include <functional> // std::less
#include <queue> // std::priority_queue
#include <memory> // std::shared_ptr
#include <thread> // std::thread
#include <mutex> // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <vector> // std::vector
#include <ciso646> // not, or

namespace pl
{
namespace detail
{
class ThreadPoolImpl final
{
public:
    using this_type = ThreadPoolImpl;

    ThreadPoolImpl(unsigned threads, ThreadPool &threadPool);

    ThreadPoolImpl(const this_type &) = delete;

    this_type &operator=(const this_type &) = delete;

    ~ThreadPoolImpl();

    void threadFunction();

    void join();

    PL_NODISCARD bool isFinished() const;

    PL_NODISCARD unsigned getThreadCount() const;

private:
    std::vector<std::thread> m_threads;
    bool m_finished;
    const unsigned m_threadCount_;
    ThreadPool &m_threadPool;
};

ThreadPoolImpl::ThreadPoolImpl(unsigned threads, ThreadPool &threadPool)
    : m_threads{ },
      m_finished{ false },
      m_threadCount_{ threads },
      m_threadPool{ threadPool }
{
    for (auto i = 0U; i < threads; ++i) {
        m_threads.emplace_back(&this_type::threadFunction, this);
    }
}

ThreadPoolImpl::~ThreadPoolImpl()
{
    if (not isFinished()) {
        join();
    }
}

ThreadPoolImpl::threadFunction()
{
    auto running = true;
    while (running) {
        std::unique_lock<std::mutex> lock{ m_threadPool.m_mutex };
        m_threadPool.m_cv.wait(lock,
                  [this] {
            return m_finished or not m_threadPool.m_tasks.empty();
        });

        if (not m_threadPool.m_task.empty()) {
            auto task = m_threadPool.m_tasks.top();
            m_threadPool.m_tasks.pop();
            lock.unlock();
            (*task)();
        } else {
            running = not m_finished;
        }
    }
}

ThreadPoolImpl::join()
{
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_finished = true;
    }

    m_cv.notify_all();

    for (auto &thread : m_threadPool.m_threads) {
        thread.join();
    }
}

PL_NODISCARD bool ThreadPoolImpl::isFinished() const
{
    std::unique_lock<std::mutex> lock{ m_threadPool.m_mutex };
    return m_finished;
}

PL_NODISCARD unsigned ThreadPoolImpl::getThreadCount() const
{
    return m_threadCount_;
}
} // namespace detail

ThreadPool::ThreadPool(unsigned threadCount)
    : m_p{ std::make_unique<detail::ThreadPoolImpl>(threadCount, *this) },
      m_tasks{ },
      m_mutex{ },
      m_cv{ }
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::join()
{
    m_p->join();
}

PL_NODISCARD bool ThreadPool::isFinished() const
{
    auto p
        = static_cast<const detail::ThreadPoolImpl *>(
              m_p.get()
          );

    return p->isFinished();
}

PL_NODISCARD unsigned ThreadPool::getThreadCount() const
{
    auto p
        = static_cast<const detail::ThreadPoolImpl *>(
              m_p.get()
          );

    return p->getThreadCount();
}
} // namespace pl
