/*!
 * \file thread_pool.hpp
 * \brief Defines the ThreadPool class.
**/
#ifndef INCG_PL_THD_THREAD_POOL_HPP
#define INCG_PL_THD_THREAD_POOL_HPP
#include "../annotations.hpp" // PL_IN, PL_NODISCARD
#include "../byte.hpp" // pl::Byte
#include <memory> // std::shared_ptr, std::unique_ptr
#include <functional> // std::bind
#include <thread> // std::thread
#include <mutex> // std::mutex
#include <vector> // std::vector
#include <condition_variable> // std::condition_variable
#include <future> // std::future, std::promise
#include <queue> // std::priority_queue
#include <cstddef> // std::size_t
#include <cstdint> // std::uint8_t

namespace pl
{
namespace thd
{
/*!
 * \brief A thread pool. Can be created with a count of threads. Will manage
 *        that many threads. Tasks can be added with a priority. The threads
 *        will run the tasks added according to their priority. The count of
 *        threads and the count of tasks still waiting to be executed can be
 *        queried.
**/
class ThreadPool final
{
private:
    class ExecutorBase;
public:
    using this_type = ThreadPool;

    /*!
     * \brief Compares two ExecutorBase's priorities.
     * \param a The first operand.
     * \param b The second operand.
     * \return true if a's priority is less than b's priority; false otherwise.
    **/
    PL_NODISCARD friend bool operator<(PL_IN const ExecutorBase &a,
                                       PL_IN const ExecutorBase &b);

    /*!
     * \brief Constructs a ThreadPool.
     * \param amtThreads The amount of threads that this ThreadPool is going to
     *        have.
     *
     * Will create as many threads as amtThreads. The threads will start
     * running the threadFunction private member function.
     * You can use std::thread::hardware_concurrency() to get a good amount
     * of threads to be used. However, note that
     * std::thread::hardware_concurrency() may return 0 on error.
    **/
    explicit ThreadPool(std::size_t amtThreads);

    ThreadPool(const this_type &) = delete;

    this_type &operator=(const this_type &) = delete;

    /*!
     * \brief Destroys the ThreadPool by joining all of the threads
     *        managed by the ThreadPool and then destroying the threads.
     * \warning Will block the calling thread until all of the threads in the
     *          ThreadPool are shut down.
    **/
    ~ThreadPool();

    /*!
     * \brief adds the task passed to be called with the arguments passed
     *        to the queue of tasks still to be run.
     * \param task The task that shall be run by one of the threads in
     *        the ThreadPool. Will be added to the queue of tasks still to be
     *        run.
     * \param args The arguments that task will be called with when it is
     *        run by a thread managed by this ThreadPool.
     * \return a std::future to the result of invoking the task passed with
     *         the arguments passed in. Can be joined using .get() for instance.
     *         The std::future returned may hold an exception if an
     *         exception occurred while running the task.
     * \note May block the calling thread until the threads in the ThreadPool
     *       are done accessing the shared queue of tasks.
     *
     * Delegates to the addTask overload that also expects a priority to be
     * passed. The priority used will be 0, which is the lowest possible
     * priority. Will wake up one thread waiting for something to be added
     * to the queue of tasks.
    **/
    template <typename Callable, typename ...Args>
    PL_NODISCARD auto addTask(Callable task, Args ...args)
    -> std::future<decltype(task(args...))>
    {
        // add the task using a priority of 0.
        return addTask(static_cast<std::uint8_t>(0U), task, args...);
    }

    /*!
     * \brief Will add the task passed in to be called with the arguments
     *        passed in to the queue of tasks still to be run.
     * \param prio The priority to be used. The higher the priority the earlier
     *        the task will be scheduled to be run. The value of prio must be
     *        within [0..255].
     * \param task The task that should be scheduled to be run by one of the
     *        threads managed by this ThreadPool. This task will be called with
     *        the arguments (args) passed in. This task will be added to the
     *        underlying priority queue using the priority passed.
     * \param args The arguments to call the task with.
     * \return Returns a std::future to the result of calling task(args...).
     *         The std::future can be joined and the result be extracted using
     *         .get(). The std::future returned may hold an exception if an
     *         exception occurred while running the task.
     * \note May block the calling thread until the threads in the ThreadPool
     *       are done accessing the shared queue of tasks.
     *
     * The task passed with the arguments it is to be called with will be added
     * to the queue of tasks still to be run using the priority passed into
     * the first parameter of this member function. Will wake up one thread
     * that is waiting for a task to be added to the queue. Will return a
     * std::future to the result of invoking the task with the arguments passed.
     * That std::future can be joined using .get() for instance.
    **/
    template <typename Callable, typename ...Args>
    PL_NODISCARD auto addTask(std::uint8_t prio, Callable task, Args ...args)
    -> std::future<decltype(task(args...))>
    {
        // return type for the Executor template
        using Ret = decltype(task(args...));

        // lock the mutex, shared data is going to be accessed
        std::unique_lock<std::mutex> lock{ m_mutex };
        auto t = std::make_shared<Executor<decltype(std::bind(task, args...)), Ret>>
            (std::bind(task, args...), prio);
        m_tasksShared.push(t); // add the task to the queue.
        m_cv.notify_one(); // wake one thread
        return t->getResult().get_future(); // return the future back to caller.
    }

    /*!
     * \brief Function to query the amount of threads that this ThreadPool
     *        manages.
     * \return The count of threads that this ThreadPool manages.
    **/
    PL_NODISCARD std::size_t getThreadCount() const;

    /*!
     * \brief Function to query the amount of tasks that are still waiting
     *        to be run.
     * \return The number of tasks still waiting in the queue.
     * \warning May block the calling thread while other threads access
     *          the underlying priority queue of tasks.
    **/
    PL_NODISCARD std::size_t tasksWaitingForExecution() const;

private:
    /*!
     * \brief Base class for the Executors. Can run a task and store
     *        the result as a promise. Has a priority associated with it
     *        that represents the priority of the task to be run.
     *        Can be compared by that priority.
    **/
    class ExecutorBase
    {
    public:
        /*!
         * \brief Constructor for ExecutorBase.
         * \param p the priority to be stored in the protected data member,
         *        defaults to 0xFFU, which is 255.
        **/
        explicit ExecutorBase(std::uint8_t p = 0xFFU);

        /*!
         * \brief Destroys an ExecutorBase.
        **/
        virtual ~ExecutorBase();

        /*!
         * \brief Compares two ExecutorBase's priorities.
         * \param a The first operand.
         * \param b The second operand.
         * \return true if a's priority is less than b's priority; false otherwise.
        **/
        PL_NODISCARD friend bool operator<(PL_IN const ExecutorBase &a,
                                           PL_IN const ExecutorBase &b);

        /*!
         * \brief pure virtual member function to be implemented by deriving
         *        types. Invokes the task and stores the result in a promise.
        **/
        virtual void operator()() = 0;

    protected:
        std::uint8_t m_priority; /*!< the priority with which to run the task.
                                  *   Can be accessed by derived types.
                                 **/
    };

    /*!
     * \brief Executor for tasks returning a non-void type.
     *
     * Runs the task in its call operator and sets the result to its promise.
    **/
    template <typename Task, typename Ret>
    class Executor final
        : public ExecutorBase
    {
    public:
        /*!
         * \brief Constructs an Executor from a task and a priority.
         * \param task The task to be run in the call operator.
         * \param priority The priority with which the task is to be run.
         *        The Executors will remain sorted by this criterion.
        **/
        Executor(PL_IN const Task &task, std::uint8_t priority)
            : ExecutorBase{ priority },
              m_task{ task },
              m_result{ }
        {
        }

        /*!
         * \brief Is called by a thread. Invokes the task and sets its
         *        result to its promise.
         * \note If an exception occurs while running the task, the
         *       exception will be stored in the promise instead.
        **/
        virtual void operator()() override
        {
            try {
                m_result.set_value(m_task());
            } catch (...) {
                m_result.set_exception(std::current_exception());
            }
        }

        /*!
         * \brief Returns a non-const lvalue reference to the promise stored.
         * \return A non-const lvalue reference to the promise stored.
         * \note Used by ThreadPool::addTask to access the promise and get its
         *       associated future.
        **/
        PL_NODISCARD std::promise<Ret> &getResult()
        {
            return m_result;
        }

    private:
        Task m_task; //!< The task to be run.
        std::promise<Ret> m_result; //!< the result of running the task.
    };

    /*!
     * \brief Executor for tasks that return void.
     *
     * Runs the task in its call operator, that is to be called by a thread.
     * and sets the result to its underlying promise.
    **/
    template <typename Task>
    class Executor<Task, void> final
        : public ExecutorBase
    {
    public:
        /*!
         * \brief Constructs an Executor.
         * \param task The task to be stored in the Executor.
         *        Will be run in the call operator.
         * \param priority The priority to store. This priority will be
         *        used to compare the different Executors with so that
         *        they can remain sorted according to that criterion.
         * \note The function that is run by the threads will always take the
         *       'greatest' task, that is the one with the highest priority.
        **/
        Executor(PL_IN const Task &task, std::uint8_t priority)
            : ExecutorBase{ priority },
              m_task{ task },
              m_result{ }
        {
        }

        /*!
         * \brief The call operator. Will call the task when invoked.
         *        And set the promise. The std::promise stored is a
         *        std::promise<void>.
         *
         * The task is called, when this function is invoked. The
         * promise stored will be made ready. If the invocation if the task
         * throws that exception will be caught and be put into the promise.
        **/
        virtual void operator()() override
        {
            try {
                m_task();
                m_result.set_value();
            } catch (...) {
                m_result.set_exception(std::current_exception());
            }
        }

        /*!
         * \brief Allows access to the promise stored.
         * \return A reference to the underlying std::promise<void>
         * \note This function is called in ThreadPool::addTask so that
         *       the future associated with this promise can be gotten and be
         *       returned back to the user.
        **/
        PL_NODISCARD std::promise<void> &getResult()
        {
            return m_result;
        }

    private:
        Task m_task; //!< The task to be called in the call operator.
        std::promise<void> m_result; /*!< The result of calling the Task.
                                      *   Will be void or if an exception
                                      *   occured, it will be that exception.
                                     **/
    };

    /*!
     * \brief Comparator class used in the priority queue.
     *        Helper to keep the tasks sorted according to their priority.
     *        Derefences two objects passed in and compares the results using
     *        std::less.
    **/
    class DerefLess final
    {
    public:
        /*!
         * \brief Compares *p1 with *p2 using std::less.
         * \param p1 The first operand to be dereferenced and then compared.
         * \param p2 The second operator to be dereferenced and the compared.
         * \return The result of comparing *p1 and *p2 using std::less.
         *         true if *p1 is considered less than *p2; false otherwise.
        **/
        template <typename Pointer>
        PL_NODISCARD bool operator()(PL_IN Pointer const &p1,
                                     PL_IN Pointer const &p2)
        {
            std::less<decltype(*p1)> lessComparator{ };
            return lessComparator(*p1, *p2);
        }
    };

    /*!
     * \brief The function that the threads in this ThreadPool will run.
     *
     * A thread will keep running in a loop in this function until the
     * queue of tasks is empty and the ThreadPool is being destroyed.
     * A thread running this function will wait until the ThreadPool is being
     * destroyed or the queue of tasks is no longer empty. If the ThreadPool
     * is being destroyed and the queue is empty the thread will stop running
     * this function. If the queue is not empty a thread running this function
     * will take the tasks from the queue of tasks that has the highest
     * priority and run it. That will invoke the Executor's call operator
     * which will run the actual task and set the promise in the Executor
     * that the future that was returned to the user by addTask is associated
     * with.
    **/
    void threadFunction();

    /*!
     * \brief Will set the is finished flag and wake all threads and then
     *        join them so that the ThreadPool can shut down. Is called in
     *        ThreadPool's destructor.
     * \warning Will let the calling thread wait until the threads of this
     *          ThreadPool are shut down.
    **/
    void join();

    std::priority_queue<
        std::shared_ptr<ExecutorBase>,
        std::vector<std::shared_ptr<ExecutorBase>>,
        DerefLess
    > m_tasksShared; //!< the queue of tasks still to be run
    mutable std::mutex m_mutex; //!< mutex to protect the shared data
    std::condition_variable m_cv; /*!< condvar to wake threads waiting for the
                                   *   queue to no longer be empty. And to
                                   *   shutdown the threads in the join function
                                  **/
    bool m_isFinishedShared; //!< flag that will be set to true on shutdown.
    const std::size_t m_threadCount; //!< the amount of threads.
    std::unique_ptr<pl::Byte[]> m_threads; /*!< raw memory that the threads
                                            *   live in.
                                           **/
    std::thread *m_threadBegin; //!< iterator to the first thread.
    std::thread *m_threadEnd; //!< end iterator of the range of threads.
};
} // namespace thd
} // namespace pl
#endif // INCG_PL_THD_THREAD_POOL_HPP
