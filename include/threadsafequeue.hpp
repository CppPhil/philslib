/*! \file threadsafequeue.hpp
 *  \brief This header file defines the pl::ThreadSafeQueue class
**/

#ifndef INCG_PL_THREADSAFEQUEUE_HPP
#define INCG_PL_THREADSAFEQUEUE_HPP
#include "macros.hpp" // PL_IN, PL_NODISCARD
#include <queue> // std::queue
#include <mutex> // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <utility> // std::move
namespace pl
{
/*!
 * \brief Allows the user to push elements to the back of the ThreadSafeQueue
 *        and pop elements from the front.
 *
 * This class can be accessed from multiple threads at the same time.
**/
template <typename ValueType>
class ThreadSafeQueue final
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
            return !m_cont.empty();
        });
        auto retMe = m_cont.front();
        m_cont.pop();
        return retMe;
    }

    /*!
     * \brief Pushes the object passed into the parameter to the back of the
     *        queue.
     * \param data The object to push the the back of the queue.
     *
     * Will notify threads waiting for the queue to no longer be empty that
     * the queue is no longer empty.
    **/
    void push(PL_IN const value_type &data)
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cont.push(data);
        m_cvHasElements.notify_all();
    }

    /*!
     * \brief Pushes the rvalue passed to the back of the queue.
     * \param data The rvalue to add to the back of the queue
     *
     * Will notify threads waiting for the queue to no longer be empty that
     * the queue is no longer empty.
    **/
    void push(PL_IN value_type &&data)
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cont.push(std::move(data));
        m_cvHasElements.notify_all();
    }

    /*!
     * \brief Queries the queue as to whether or not it is empty.
     * \return true if the queue is empty; false otherwise.
    **/
    PL_NODISCARD bool empty() const
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        return m_cont.empty();
    }

    /*!
     * \brief Queries the queue's size.
     * \return The size of the queue.
    **/
    size_type size() const
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        return m_cont.size();
    }

private:
    container_type m_cont;
    mutable std::mutex m_mutex;
    std::condition_variable m_cvHasElements;
};
} // namespace pl
#endif // INCG_PL_THREADSAFEQUEUE_HPP
