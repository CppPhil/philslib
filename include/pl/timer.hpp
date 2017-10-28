/*!
 * \file timer.hpp
 * \brief Exports the Timer type.
**/
#ifndef INCG_PL_TIMER_HPP
#define INCG_PL_TIMER_HPP
#include <chrono> // std::chrono::steady_clock, std::chrono::time_point

namespace pl
{
/*!
 * \brief A timer that can be used to measure durations of time.
**/
class Timer
{
public:
    using this_type = Timer;

    /*!
     * \brief Constructs the Timer object.
     *        The time stored is initialized with the current time.
     *        Effectively 'starts' the Timer.
    **/
    Timer() noexcept;

    /*!
     * \brief Calculates the distance between the current time and the time
     *        stored in this Timer object.
     * \return The duration between the current time (when this function is
     *         invoked) and the time stored. The return value can be cast
     *         to the desired duration type using std::chrono::duration_cast.
    **/
    std::chrono::steady_clock::duration elapsedTime() const noexcept;

    /*!
     * \brief Resets the time stored. The time stored is discarded and
     *        replaced with the current time (when this function is invoked)
     * \return A reference to this Timer object.
    **/
    this_type &reset() noexcept;

private:
    std::chrono::time_point<std::chrono::steady_clock> m_timeStored; /*!< The time stored */
};
} // namespace pl
#endif // INCG_PL_TIMER_HPP
