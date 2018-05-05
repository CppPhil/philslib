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
 * \file thread_safe_queue.hpp
 * \brief This header file defines the pl::ThreadSafeQueue class
**/
#ifndef INCG_PL_THD_THREAD_SAFE_QUEUE_HPP
#define INCG_PL_THD_THREAD_SAFE_QUEUE_HPP
#include "../annotations.hpp" // PL_IN, PL_NODISCARD
#include <queue> // std::queue
#include <mutex> // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <utility> // std::move
#include <ciso646> // not

namespace pl
{
namespace thd
{
/*!
 * \brief Allows the user to push elements to the back of the ThreadSafeQueue
 *        and pop elements from the front.
 *
 * This class can be accessed from multiple threads at the same time.
**/
template <typename ValueType>
class ThreadSafeQueue
{
public:
    using this_type = ThreadSafeQueue;
    using value_type = ValueType;
    using container_type = std::queue<value_type>;
    using size_type = typename container_type::size_type;

    /*!
     * \brief Creates a ThreadSafeQueue.
     *        The ThreadSafeQueue will start out empty.
    **/
    ThreadSafeQueue() noexcept
        : m_cont{ },
          m_mutex{ },
          m_cvHasElements{ }
    {
    }

    /*!
     * \brief This type is non-copyable.
    **/
    ThreadSafeQueue(const this_type &) = delete;

    /*!
     * \brief This type is non-copyable.
    **/
    this_type &operator=(const this_type &) = delete;

    /*!
     * \brief Removes the first element and returns it.
     * \return The element that used to be at the front of the queue.
     *
     * If the queue is currently empty the calling thread will be put to sleep
     * until the queue is no longer empty.
    **/
    value_type pop()
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cvHasElements.wait(lock, [this] {
            return not m_cont.empty();
        });
        auto retMe = m_cont.front();
        m_cont.pop();
        return retMe;
    }

    /*!
     * \brief Pushes the object passed into the parameter to the back of the
     *        queue.
     * \param data The object to push to the back of the queue.
     * \return A reference to this object.
     *
     * Will notify threads waiting for the queue to no longer be empty that
     * the queue is no longer empty.
    **/
    this_type &push(PL_IN const value_type &data)
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cont.push(data);
        lock.unlock();
        m_cvHasElements.notify_all();
        return *this;
    }

    /*!
     * \brief Pushes the rvalue passed to the back of the queue.
     * \param data The rvalue to add to the back of the queue
     * \return A reference to this object.
     *
     * Will notify threads waiting for the queue to no longer be empty that
     * the queue is no longer empty.
    **/
    this_type &push(PL_IN value_type &&data)
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cont.push(std::move(data));
        lock.unlock();
        m_cvHasElements.notify_all();
        return *this;
    }

    /*!
     * \brief Queries the queue as to whether or not it is empty.
     * \return true if the queue is empty; false otherwise.
    **/
    PL_NODISCARD bool empty() const noexcept
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        return m_cont.empty();
    }

    /*!
     * \brief Queries the queue's size.
     * \return The size of the queue.
    **/
    size_type size() const noexcept
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        return m_cont.size();
    }

private:
    container_type m_cont;
    mutable std::mutex m_mutex;
    std::condition_variable m_cvHasElements;
};
} // namespace thd
} // namespace pl
#endif // INCG_PL_THD_THREAD_SAFE_QUEUE_HPP
