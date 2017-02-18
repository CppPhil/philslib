/*! \file threadpool.hpp
 *  \brief Defines the ThreadPool class
**/

#ifndef INCG_PL_THREADPOOL_HPP
#define INCG_PL_THREADPOOL_HPP
#include "macros.hpp" // PL_NODISCARD
#include <memory> // std::unique_ptr, std::shared_ptr
#include <queue> // std::priority_queue
#include <vector> // std::vector
#include <mutex> // std::mutex
#include <condition_variable> // std::condition_variable
#include <cstdint> // std::uint8_t
#include <utility> // std::move, std::forward
#include <functional> // std::bind
#include <future> // std::promise, std::future
namespace pl
{
namespace detail
{
class ExecutorBase
{
public:
    using this_type = ExecutorBase;

    explicit ExecutorBase(std::uint8_t priority = 0xFFU);

    ExecutorBase(const this_type &) = delete;

    this_type &operator=(const this_type &) = delete;

    virtual ~ExecutorBase() = default;

    virtual void operator()() = 0;

    friend bool operator<(const this_type &a, const this_type &b);

protected:
    std::uint8_t m_priority;
};

ExecutorBase::ExecutorBase(std::uint8_t priority)
    : m_priority{ priority }
{
}

bool operator<(const ExecutorBase &a, const ExecutorBase &b)
{
    return a.m_priority < b.m_priority;
}

template <typename Task, typename Ret>
class Executor final
    : public ExecutorBase
{
public:
    using this_type = Executor;

    Executor(Task task, std::uint8_t priority)
        : ExecutorBase{ priority },
          m_task{ std::move(task) }
    {
    }

    virtual void operator()() override
    {
        try {
            auto result = m_task();
            m_promise.set_value(result);
        } catch (...) {
            m_promise.set_exception(std::current_exception());
        }
    }

    std::promise<Ret> &getPromise() const
    {
        return m_promise;
    }

private:
    Task m_task;
    std::promise<Ret> m_promise;
};

template <typename Task>
class Executor<Task, void> final
    : public ExecutorBase
{
public:
    Executor(Task task, std::uint8_t priority)
        : ExecutorBase{ priority },
          m_task{ std::move(task) }
    {
    }

    virtual void operator()() override
    {
        try {
            m_task();
            m_promise.set_value();
        } catch (...) {
            m_promise.set_exception(std::current_exception());
        }
    }

    std::promise<void> &getPromise() const
    {
        return m_promise;
    }

private:
    Task m_task;
    std::promise<void> m_promise;
};

class DerefComparator final
{
public:
    template <typename Pointer>
    bool operator()(const Pointer &p1, const Pointer &p2)
    {
        std::less<decltype(*p1)> lessComparator{ };
        return lessComparator(*p1, *p2);
    }
};

class ThreadPoolImpl;
} // namespace detail

/*!
 * \brief A ThreadPool.
 *
 * Tasks can be added to the thread pool.
 * The tasks will be run by the threads
 * managed by the thread pool according
 * to the priority of the tasks.
**/
class ThreadPool final
{
public:
    using this_type = ThreadPool;

    friend class detail::ThreadPoolImpl;

    /*!
     * \brief Launches the threads.
     * \param threadCount The amount of threads to use.
     * \note For the threadCount passed see std::thread::hardware_concurrency(),
     *       but be aware that std::thread::hardware_concurrency() may return 0
     *       on error.
    **/
    explicit ThreadPool(unsigned threadCount);

    ThreadPool(const this_type &) = delete;

    this_type &operator=(const this_type &) = delete;

    /*!
     * \brief Joins the underlying threads if they haven't already been joined.
    **/
    ~ThreadPool();

    template <typename Callable, typename ...Args>
    auto addTask(Callable &&task, Args &&...args)
    {
        return addTask(0U, std::forward<Callable>(task),
                       std::forward<Args>(args) ...);
    }

    template <typename Callable, typename ...Args>
    auto addTask(std::uint8_t priority, Callable task, Args ...args)
    {
        using Ret = decltype(task(std::move(args) ...));

        std::unique_lock<std::mutex> lock{ m_mutex };
        auto taskPtr
            = std::make_shared<
                  detail::Executor<
                      decltype(std::bind(taskPtr, std::move(args) ...)),
                      Ret>>(
                          std::bind(taskPtr, std::move(args ...), priority));
        m_tasks.push(std::move(taskPtr));
        m_cv.notify_one();

        return taskPtr->getPromise().get_future();
    }

    /*!
     * \brief joins the underlying threads.
    **/
    void join();

    /*!
     * \brief Returns whether the ThreadPool is finished; that is all threads
     *        have been joined.
     * \return true if all threads have been joined; false otherwise.
    **/
    PL_NODISCARD bool isFinished() const;

    /*!
     * \brief Gets the amount of threads managed by this thread pool.
     * \return The amount of threads managed by this thread pool.
    **/
    PL_NODISCARD unsigned getThreadCount() const;

private:
    std::unique_ptr<detail::ThreadPoolImpl> m_p;
    std::priority_queue<
        std::shared_ptr<detail::ExecutorBase>,
        std::vector<std::shared_ptr<detail::ExecutorBase>>,
        detail::DerefComparator> m_tasks;
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;
};
} // namespace pl
#endif // INCG_PL_THREADPOOL_HPP
