#include "../../include/pl/eprintf.hpp"
#include <cstdarg> // std::va_list, va_start, va_end
#include <cstdio> // std::vfprintf

namespace pl
{
int eprintf(PL_IN PL_FMT_STR(const char *)formatString, ...) noexcept
{
    std::va_list args{ };
    va_start(args, formatString);
    const int retVal{ std::vfprintf(stderr, formatString, args) };
    va_end(args);

    return retVal;
}
} // namespace pl
