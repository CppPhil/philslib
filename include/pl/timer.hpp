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
 * \file timer.hpp
 * \brief Exports the timer type.
 **/
#ifndef INCG_PL_TIMER_HPP
#define INCG_PL_TIMER_HPP
#include <chrono> // std::chrono::steady_clock, std::chrono::time_point

namespace pl {
/*!
 * \brief A timer that can be used to measure durations of time.
 **/
class timer {
public:
    using this_type = timer;

    /*!
     * \brief Constructs the timer object.
     *        The time stored is initialized with the current time.
     *        Effectively 'starts' the timer.
     **/
    timer() noexcept;

    /*!
     * \brief Calculates the distance between the current time and the time
     *        stored in this timer object.
     * \return The duration between the current time (when this function is
     *         invoked) and the time stored. The return value can be cast
     *         to the desired duration type using std::chrono::duration_cast.
     **/
    std::chrono::steady_clock::duration elapsed_time() const noexcept;

    /*!
     * \brief Resets the time stored. The time stored is discarded and
     *        replaced with the current time (when this function is invoked)
     * \return A reference to this Timer object.
     **/
    this_type& reset() noexcept;

private:
    std::chrono::time_point<std::chrono::steady_clock>
        m_time_stored; /*!< The time stored */
};

inline timer::timer() noexcept : m_time_stored{std::chrono::steady_clock::now()}
{
}

inline std::chrono::steady_clock::duration timer::elapsed_time() const noexcept
{
    return std::chrono::steady_clock::now() - m_time_stored;
}

inline timer& timer::reset() noexcept
{
    // replace the time stored with the current time.
    m_time_stored = std::chrono::steady_clock::now();
    return *this;
}
} // namespace pl
#endif // INCG_PL_TIMER_HPP
