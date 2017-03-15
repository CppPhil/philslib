/*!
 * \file monitor.hpp
 * \brief Defines the Monitor class that can be used to synchronize access
 *         from multiple threads to some shared data.
**/
#ifndef INCG_PL_MONITOR_HPP
#define INCG_PL_MONITOR_HPP
#include "macros.hpp" // PL_IN
#include <mutex> // std::mutex, std::lock_guard
#include <utility> // std::move
namespace pl
{
/*!
 * \brief Stores shared data in its private section.
 *        Allows different threads to operate on the shared data
 *        by passing in callables that operate on the shared data.
**/
template <typename SharedData>
class Monitor final
{
public:
    using this_type = Monitor;
    using element_type = SharedData;

    /*!
     * \brief Creates a Monitor.
     * \param sharedData the data to be protected by the Monitor.
    **/
    Monitor(element_type sharedData)
        : m_sharedData{ std::move(sharedData) },
          m_mutex{ }
    {
    }

    /*!
     * \brief Receives a callable and invokes that callable by passing the
     *        shared data to it. The call itself is protected by a mutex.
     * \param callable The callable to be used to operate on the shared data.
     * \return The result of calling the callable passed in with the shared data
     *         as the callable's call operator's argument.
    **/
    template <typename Callable>
    auto operator()(PL_IN Callable &&callable) const -> decltype(auto)
    {
        std::lock_guard<std::mutex> lockGuard{ m_mutex };
        return callable(m_sharedData);
    }

private:
    mutable element_type m_sharedData; //!< the shared data
    mutable std::mutex m_mutex; /*!< the mutex to guard access
                                 *   to the shared data
                                **/
};
} // namespace pl
#endif // INCG_PL_MONITOR_HPP
