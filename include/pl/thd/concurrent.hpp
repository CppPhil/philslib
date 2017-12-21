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
 * \file concurrent.hpp
 * \brief Defines the Concurrent type which wraps an instance of any type
 *        and manages a thread that runs callables on the instance wrapped.
 *        Those callables are passed in by users.
**/
#ifndef INCG_PL_THD_CONCURRENT_HPP
#define INCG_PL_THD_CONCURRENT_HPP
#include "../annotations.hpp" // PL_IN, PL_OUT, PL_INOUT
#include "../compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC
#include "thread_safe_queue.hpp" // pl::ThreadSafeQueue
#include "../invoke.hpp" // pl::invoke
#include <functional> // std::function
#include <thread> // std::thread
#include <utility> // std::move
#include <ciso646> // not
#include <memory> // std::make_shared
#include <future> // std::future, std::promise
#include <exception> // std::current_exception

namespace pl
{
namespace thd
{
/*!
 * \brief Allows callables to be run on an object managed by a thread.
**/
template <typename Type>
class Concurrent
{
public:
    using this_type = Concurrent;

    /*!
     * \brief Type alias for the template type parameter of 'Concurrent'.
     *        Can be accessed to query the template type paramater
     *        that was used for a given 'Concurrent'.
    **/
    using element_type = Type;

    /*!
     * \brief Starts the underlying thread. The thread will remove and execute
     *        callables stored in the ThreadSafeQueue continuously.
     * \param value The object that the callables passed in the call operator
     *        will operate on.
    **/
    explicit Concurrent(Type value)
        : m_value{ std::move(value) },
          m_q{ },
          m_isDone{ false },
          m_thd{
              [this] {
                  while (not m_isDone) {
                      m_q.pop()();
                  }
              }
          }
    {
    }

    /*!
     * \brief This type is non-copyable.
    **/
    Concurrent(const this_type &) = delete;

    /*!
     * \brief This type is non-copyable.
    **/
    this_type &operator=(const this_type &) = delete;

    /*!
     * \brief Adds a callable to the ThreadSafeQueue that will set the
     *        is done boolean flag to true. Which will cause the thread to
     *        return. Then the thread is joined.
     *
     * The underlying thread will continue to run the callables still in the
     * ThreadSafeQueue. As soon as the callable that sets is done to true is
     * run the thread will exit its loop. Then the thread calling this
     * destructor joins this instances's underlying thread.
    **/
    ~Concurrent()
    {
        m_q.push([this] {
            m_isDone = true;
        });

        m_thd.join();
    }

    /*!
     * \brief Adds the callable passed in to the queue of things to be
     *        executed by the underlying thread.
     * \param callable The callable that is to be run on the object managed
     *        by the thread by the thread.
     * \return A future that will hold the result of calling the callable
     *         with m_value as soon as that callable has been run, or
     *         an exception, if an exception occurred.
     *         The returned future can be joined on using .get() for instance.
    **/
    template <typename Callable>
    auto operator()(PL_IN Callable &&callable)
    {
        auto p = std::make_shared<
            std::promise<decltype(::pl::invoke(callable, m_value))>>();

        auto ret = p->get_future();

        m_q.push([p, callable, this] {
            try {
                setValue(*p, callable, m_value);
            } catch (...) {
                p->set_exception(std::current_exception());
            }
        });

        return ret;
    }

private:
    // these type aliases are just for gcc
    using Function = std::function<void ()>;
    using concurrent_queue = ThreadSafeQueue<Function>;

    /*!
     * \brief Invokes the callable with ty and sets the result to the promise.
    **/
    template <typename Fut, typename Callable, typename Ty>
    static void setValue(
        PL_OUT std::promise<Fut> &p,
        PL_IN Callable &callable,
        PL_INOUT Ty &ty)
    {
        p.set_value(::pl::invoke(callable, ty));
    }

#if PL_COMPILER == PL_COMPILER_MSVC
#   pragma warning(push)
#   pragma warning(disable:4702) // unreachable code
#endif // PL_COMPILER == PL_COMPILER_MSVC
    /*!
     * \brief Invokes the callable with ty and sets the result to the promise.
     * \note This is the overload that handles the void case, as void is not
     *       a regular type.
    **/
    template <typename Callable, typename Ty>
    static void setValue(
        PL_OUT std::promise<void> &p,
        PL_IN Callable &callable,
        PL_INOUT Ty &ty)
    {
        ::pl::invoke(callable, ty);
        p.set_value();
    }
#if PL_COMPILER == PL_COMPILER_MSVC
#   pragma warning(pop)
#endif // PL_COMPILER == PL_COMPILER_MSVC

    Type m_value;
    concurrent_queue m_q;
    bool m_isDone; //!< only accessed from m_thd
    std::thread m_thd;
};
} // namespace thd
} // namespace pl
#endif // INCG_PL_THD_CONCURRENT_HPP
