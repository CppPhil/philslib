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

/*!
 * \file thread_pool.hpp
 * \brief Defines the thread_pool class.
 **/
#ifndef INCG_PL_THD_THREAD_POOL_HPP
#define INCG_PL_THD_THREAD_POOL_HPP
#include "../algo/destroy.hpp" // pl::algo::destroy
#include "../annotations.hpp"  // PL_IN, PL_NODISCARD
#include "../apply.hpp"        // pl::apply
#include "../byte.hpp"         // pl::byte
#include <algorithm>           // std::for_each
#include <condition_variable>  // std::condition_variable
#include <cstddef>             // std::size_t
#include <cstdint>             // std::uint8_t
#include <future>              // std::future, std::promise
#include <memory>              // std::shared_ptr, std::unique_ptr
#include <mutex>               // std::mutex
#include <new>                 // new
#include <queue>               // std::priority_queue
#include <thread>              // std::thread
#include <tuple>               // std::make_tuple
#include <utility>             // std::move
#include <vector>              // std::vector

namespace pl {
namespace thd {
/*!
 * \brief A thread pool. Can be created with a count of threads. Will manage
 *        that many threads. Tasks can be added with a priority. The threads
 *        will run the tasks added according to their priority. The count of
 *        threads and the count of tasks still waiting to be executed can be
 *        queried.
 **/
class thread_pool {
private:
  class executor_base;

public:
  using this_type = thread_pool;

  /*!
   * \brief Compares two executor_base's priorities.
   * \param a The first operand.
   * \param b The second operand.
   * \return true if a's priority is less than b's priority; false otherwise.
   **/
  friend bool operator<(
    PL_IN const executor_base& a,
    PL_IN const executor_base& b);

  /*!
   * \brief Constructs a thread_pool.
   * \param amt_threads The amount of threads that this thread_pool is going
   *                    to have.
   *
   * Will create as many threads as amt_threads. The threads will start
   * running the thread_function private member function.
   * You can use std::thread::hardware_concurrency() to get a good amount
   * of threads to be used. However, note that
   * std::thread::hardware_concurrency() may return 0 on error.
   **/
  explicit thread_pool(std::size_t amt_threads);

  /*!
   * \brief This type is non-copyable.
   **/
  thread_pool(const this_type&) = delete;

  /*!
   * \brief This type is non-copyable.
   **/
  this_type& operator=(const this_type&) = delete;

  /*!
   * \brief Destroys the thread_pool by joining all of the threads
   *        managed by the thread_pool and then destroying the threads.
   * \warning Will block the calling thread until all of the threads in the
   *          thread_pool are shut down.
   **/
  ~thread_pool();

  /*!
   * \brief adds the task passed to be called with the arguments passed
   *        to the queue of tasks still to be run.
   * \param task The task that shall be run by one of the threads in
   *        the thread_pool. Will be added to the queue of tasks still to be
   *        run.
   * \param args The arguments that task will be called with when it is
   *        run by a thread managed by this thread_pool.
   * \return a std::future to the result of invoking the task passed with
   *         the arguments passed in. Can be joined using .get() for instance.
   *         The std::future returned may hold an exception if an
   *         exception occurred while running the task.
   * \note May block the calling thread until the threads in the thread_pool
   *       are done accessing the shared queue of tasks.
   *
   * Delegates to the add_task overload that also expects a priority to be
   * passed. The priority used will be 0, which is the lowest possible
   * priority. Will wake up one thread waiting for something to be added
   * to the queue of tasks.
   **/
  template<typename Callable, typename... Args>
  PL_NODISCARD auto add_task(Callable task, Args... args)
  {
    // add the task using a priority of 0.
    return add_task(static_cast<std::uint8_t>(0U), task, args...);
  }

  /*!
   * \brief Will add the task passed in to be called with the arguments
   *        passed in to the queue of tasks still to be run.
   * \param prio The priority to be used. The higher the priority the earlier
   *        the task will be scheduled to be run. The value of prio must be
   *        within [0..255].
   * \param task The task that should be scheduled to be run by one of the
   *        threads managed by this thread_pool. This task will be called with
   *        the arguments (args) passed in. This task will be added to the
   *        underlying priority queue using the priority passed.
   * \param args The arguments to call the task with.
   * \return Returns a std::future to the result of invoking the task with
   *         the arguments supplied.
   *         The std::future can be joined and the result be extracted using
   *         .get(). The std::future returned may hold an exception if an
   *         exception occurred while running the task.
   * \note May block the calling thread until the threads in the thread_pool
   *       are done accessing the shared queue of tasks.
   *
   * The task passed with the arguments it is to be called with will be added
   * to the queue of tasks still to be run using the priority passed into
   * the first parameter of this member function. Will wake up one thread
   * that is waiting for a task to be added to the queue. Will return a
   * std::future to the result of invoking the task with the arguments passed.
   * That std::future can be joined using .get() for instance.
   **/
  template<typename Callable, typename... Args>
  PL_NODISCARD auto add_task(std::uint8_t prio, Callable task, Args... args)
  {
    auto invoker
      = [t = std::move(task), tup = std::make_tuple(std::move(args)...)] {
          return ::pl::apply(std::move(t), std::move(tup));
        };

    // return type for the Executor template
    using ret = decltype(invoker());

    // lock the mutex, shared data is going to be accessed
    std::unique_lock<std::mutex> lock{m_mutex};
    auto t = std::make_shared<executor<decltype(invoker), ret>>(
      std::move(invoker), prio);

    m_tasks_shared.push(t); // add the task to the queue.
    auto fut = t->result().get_future();
    lock.unlock();
    m_cv.notify_one(); // wake one thread
    return fut;
  }

  /*!
   * \brief Function to query the amount of threads that this thread_pool
   *        manages.
   * \return The count of threads that this thread_pool manages.
   **/
  PL_NODISCARD std::size_t thread_count() const;

  /*!
   * \brief Function to query the amount of tasks that are still waiting
   *        to be run.
   * \return The number of tasks still waiting in the queue.
   * \warning May block the calling thread while other threads access
   *          the underlying priority queue of tasks.
   **/
  PL_NODISCARD std::size_t tasks_waiting_for_execution() const;

private:
  /*!
   * \brief Base class for the executors. Can run a task and store
   *        the result as a promise. Has a priority associated with it
   *        that represents the priority of the task to be run.
   *        Can be compared by that priority.
   **/
  class executor_base {
  public:
    /*!
     * \brief Constructor for excutor_base.
     * \param p the priority to be stored in the protected data member,
     *        defaults to 0xFFU, which is 255.
     **/
    explicit executor_base(std::uint8_t p = 0xFFU);

    /*!
     * \brief Destroys an executor_base.
     **/
    virtual ~executor_base();

    /*!
     * \brief Compares two executor_base's priorities.
     * \param a The first operand.
     * \param b The second operand.
     * \return true if a's priority is less than b's priority; false
     *         otherwise.
     **/
    friend bool operator<(
      PL_IN const executor_base& a,
      PL_IN const executor_base& b);

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
   * \brief executor for tasks returning a non-void type.
   *
   * Runs the task in its call operator and sets the result to its promise.
   **/
  template<typename Task, typename Ret>
  class executor final : public executor_base {
  public:
    /*!
     * \brief Constructs an executor from a task and a priority.
     * \param task The task to be run in the call operator.
     * \param priority The priority with which the task is to be run.
     *        The executors will remain sorted by this criterion.
     **/
    executor(PL_IN const Task& task, std::uint8_t priority)
      : executor_base{priority}, m_task{task}, m_result{}
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
      }
      catch (...) {
        m_result.set_exception(std::current_exception());
      }
    }

    /*!
     * \brief Returns a non-const lvalue reference to the promise stored.
     * \return A non-const lvalue reference to the promise stored.
     * \note Used by thread_pool::add_task to access the promise and get its
     *       associated future.
     **/
    PL_NODISCARD std::promise<Ret>& result()
    {
      return m_result;
    }

  private:
    Task              m_task;   //!< The task to be run.
    std::promise<Ret> m_result; //!< the result of running the task.
  };

  /*!
   * \brief executor for tasks that return void.
   *
   * Runs the task in its call operator, that is to be called by a thread.
   * and sets the result to its underlying promise.
   **/
  template<typename Task>
  class executor<Task, void> final : public executor_base {
  public:
    /*!
     * \brief Constructs an executor.
     * \param task The task to be stored in the executor.
     *        Will be run in the call operator.
     * \param priority The priority to store. This priority will be
     *        used to compare the different executors with so that
     *        they can remain sorted according to that criterion.
     * \note The function that is run by the threads will always take the
     *       'greatest' task, that is the one with the highest priority.
     **/
    executor(PL_IN const Task& task, std::uint8_t priority)
      : executor_base{priority}, m_task{task}, m_result{}
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
      }
      catch (...) {
        m_result.set_exception(std::current_exception());
      }
    }

    /*!
     * \brief Allows access to the promise stored.
     * \return A reference to the underlying std::promise<void>
     * \note This function is called in thread_pool::add_task so that
     *       the future associated with this promise can be gotten and be
     *       returned back to the user.
     **/
    PL_NODISCARD std::promise<void>& result()
    {
      return m_result;
    }

  private:
    Task               m_task; //!< The task to be called in the call operator.
    std::promise<void> m_result; /*!< The result of calling the Task.
                                  *   Will be void or if an exception
                                  *   occurred, it will be that exception.
                                  **/
  };

  /*!
   * \brief Comparator class used in the priority queue.
   *        Helper to keep the tasks sorted according to their priority.
   *        Dereferences two objects passed in and compares the results using
   *        std::less.
   **/
  class deref_less final {
  public:
    /*!
     * \brief Compares *p1 with *p2 using std::less.
     * \param p1 The first operand to be dereferenced and then compared.
     * \param p2 The second operator to be dereferenced and the compared.
     * \return The result of comparing *p1 and *p2 using std::less.
     *         true if *p1 is considered less than *p2; false otherwise.
     **/
    template<typename Pointer>
    PL_NODISCARD bool operator()(
      PL_IN Pointer const& p1,
      PL_IN Pointer const& p2)
    {
      std::less<decltype(*p1)> less_comparator{};
      return less_comparator(*p1, *p2);
    }
  };

  /*!
   * \brief The function that the threads in this thread_pool will run.
   *
   * A thread will keep running in a loop in this function until the
   * queue of tasks is empty and the thread_pool is being destroyed.
   * A thread running this function will wait until the thread_pool is being
   * destroyed or the queue of tasks is no longer empty. If the thread_pool
   * is being destroyed and the queue is empty the thread will stop running
   * this function. If the queue is not empty a thread running this function
   * will take the tasks from the queue of tasks that has the highest
   * priority and run it. That will invoke the executor's call operator
   * which will run the actual task and set the promise in the Executor
   * that the future that was returned to the user by add_task is associated
   * with.
   **/
  void thread_function();

  /*!
   * \brief Will set the is finished flag and wake all threads and then
   *        join them so that the thread_pool can shut down. Is called in
   *        thread_pool's destructor.
   * \warning Will let the calling thread wait until the threads of this
   *          thread_pool are shut down.
   **/
  void join();

  std::priority_queue<
    std::shared_ptr<executor_base>,
    std::vector<std::shared_ptr<executor_base>>,
    deref_less>
                     m_tasks_shared; //!< the queue of tasks still to be run
  mutable std::mutex m_mutex;        //!< mutex to protect the shared data
  std::condition_variable m_cv; /*!< condvar to wake threads waiting for the
                                 *   queue to no longer be empty. And to
                                 *   shutdown the threads in the join function
                                 **/
  bool m_is_finished_shared;    //!< flag that will be set to true on shutdown.
  const std::size_t           m_thread_count; //!< the amount of threads.
  std::unique_ptr<pl::byte[]> m_threads;      /*!< raw memory that the threads
                                               *   live in.
                                               **/
  std::thread* m_thread_begin;                //!< iterator to the first thread.
  std::thread* m_thread_end; //!< end iterator of the range of threads.
};

inline thread_pool::thread_pool(std::size_t amt_threads)
    : m_tasks_shared{ },
      m_mutex{ },
      m_cv{ },
      m_is_finished_shared{ false }, // start out not finished
      m_thread_count{ amt_threads },
      m_threads{ // get the memory needed for the threads.
                 // the unique_ptr will deallocate the memory automatically.
          std::make_unique<pl::byte[]>(m_thread_count * sizeof(std::thread))
      },
      m_thread_begin{ // begin iterator to the range of threads
          reinterpret_cast<std::thread *>(m_threads.get())
      },
      m_thread_end{ m_thread_begin + m_thread_count } /* end iterator.
                                                       * is out of bounds.
                                                       */
{
  if (m_thread_count == 0) {
    return;
  }

  m_thread_begin = ::new (
    const_cast<void*>(static_cast<const volatile void*>(m_thread_begin)))
    std::thread{&thread_pool::thread_function, this};

  for (std::size_t i{1}; i < m_thread_count; ++i) {
    ::new (
      const_cast<void*>(static_cast<const volatile void*>(m_thread_begin + i)))
      std::thread{&thread_pool::thread_function, this};
  }
}

inline thread_pool::~thread_pool()
{
  // join the threads
  // this will shut all the threads down and then actually join them.
  join();

  /* Call the destructors of the threads.
   * the unique_ptr will only free the raw memory of pl::bytes.
   **/
  algo::destroy(m_thread_begin, m_thread_end);
}

PL_NODISCARD inline std::size_t thread_pool::thread_count() const
{
  return m_thread_count; // return the requested constant.
}

PL_NODISCARD inline std::size_t thread_pool::tasks_waiting_for_execution() const
{
  // lock the mutex,
  // the queue of tasks is shared data
  // the threads of the thread pool remove tasks from it.
  std::lock_guard<std::mutex> lock{m_mutex};
  (void)lock;
  return m_tasks_shared.size(); // return the number of tasks still to be run.
}

inline thread_pool::executor_base::executor_base(std::uint8_t p)
  : m_priority{p} // just set the priority
{
}

inline thread_pool::executor_base::~executor_base() = default;
inline bool operator<(
  PL_IN const thread_pool::executor_base& a,
  PL_IN const thread_pool::executor_base& b)
{
  return a.m_priority < b.m_priority; // compare the priorities stored.
}

inline void thread_pool::thread_function()
{
  // by default we're running.
  auto running = true;

  while (running) {
    std::unique_lock<std::mutex> lock{m_mutex};
    m_cv.wait(
      lock, // wait until shutdown or got task to run.
      [this] { return m_is_finished_shared || !m_tasks_shared.empty(); });

    // if we woke up because there's a task to run.
    if (!m_tasks_shared.empty()) {
      auto task = m_tasks_shared.top(); // get the highest priority task.
      m_tasks_shared.pop();             // remove it from the queue
      lock.unlock(); // unlock the mutex, we're not accessing shared data
                     // any more, the task is local to this thread.
      (*task)();     // run your task.
    }
    else {
      // if there was no task.
      // set running to false if we're shutting down.
      running = !m_is_finished_shared;
      // exit the loop if we're shutting down.
      // if running is still true it was just a spurious wake.
    }
  }
}

inline void thread_pool::join()
{
  {
    // lock the mutex, the boolean flag is shared data.
    std::lock_guard<std::mutex> lock{m_mutex};
    (void)lock;
    m_is_finished_shared = true;
  }

  // wake all threads, we're shutting down.
  m_cv.notify_all();

  // join every thread.
  std::for_each(
    m_thread_begin, m_thread_end, [](PL_INOUT std::thread& t) { t.join(); });
}
} // namespace thd
} // namespace pl
#endif // INCG_PL_THD_THREAD_POOL_HPP
