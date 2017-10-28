#include "../../include/pl/timer.hpp"

namespace pl
{
Timer::Timer() noexcept
    : m_timeStored{ std::chrono::steady_clock::now() }
{
}

std::chrono::steady_clock::duration Timer::elapsedTime() const noexcept
{
    return std::chrono::steady_clock::now() - m_timeStored;
}

Timer &Timer::reset() noexcept
{
    // replace the time stored with the current time.
    m_timeStored = std::chrono::steady_clock::now();
    return *this;
}
} // namespace pl
