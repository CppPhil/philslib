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
 * \file monitor.hpp
 * \brief Defines the monitor class that can be used to synchronize access
 *        from multiple threads to some shared data.
 **/
#ifndef INCG_PL_THD_MONITOR_HPP
#define INCG_PL_THD_MONITOR_HPP
#include "../annotations.hpp" // PL_IN
#include "../invoke.hpp"      // pl::invoke
#include <mutex>              // std::mutex, std::lock_guard
#include <utility>            // std::move, std::forward

namespace pl {
namespace thd {
/*!
 * \brief Stores shared data in its private section.
 *        Allows different threads to operate on the shared data
 *        by passing in callables that operate on the shared data.
 **/
template<typename SharedData>
class monitor {
public:
    using this_type    = monitor;
    using element_type = SharedData;

    /*!
     * \brief Creates a monitor.
     * \param shared_data the data to be protected by the Monitor.
     **/
    explicit monitor(element_type shared_data)
        : m_shared_data{std::move(shared_data)}, m_mutex{}
    {
    }

    /*!
     * \brief This type is non-copyable.
     **/
    monitor(const this_type&) = delete;

    /*!
     * \brief This type is non-copyable.
     **/
    this_type& operator=(const this_type&) = delete;

    /*!
     * \brief Receives a callable and invokes that callable by passing the
     *        shared data to it. The call itself is protected by a mutex.
     * \param callable The callable to be used to operate on the shared data.
     * \return The result of calling the callable passed in with the shared data
     *         as the callable's call operator's argument.
     **/
    template<typename Callable>
    auto operator()(PL_IN Callable&& callable) -> decltype(auto)
    {
        std::lock_guard<std::mutex> lock_guard{m_mutex};
        (void)lock_guard;
        return ::pl::invoke(std::forward<Callable>(callable), m_shared_data);
    }

private:
    element_type m_shared_data; //!< the shared data
    std::mutex   m_mutex;       /*!< the mutex to guard access
                                 *   to the shared data
                                 **/
};
} // namespace thd
} // namespace pl
#endif // INCG_PL_THD_MONITOR_HPP
