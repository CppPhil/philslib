#include "../../include/pl/asprintf.hpp"
#include <cstddef> // std::size_t
#include <cstdio> // std::vsnprintf
#include <memory> // std::addressof

namespace pl
{
PL_NODISCARD int vasprintf(PL_OUT std::unique_ptr<char[]> *strp,
                           PL_IN PL_FMT_STR(const char *)fmt,
                           std::va_list ap) noexcept
{
    std::va_list args2{ };
    va_copy(args2, ap);

    const auto errCode = std::vsnprintf(nullptr, 0, fmt, ap);

    if (errCode < 0) {
        return errCode;
    }

    const auto bytesToAllocate = 1U + static_cast<std::size_t>(errCode);

    *strp = std::make_unique<char[]>(bytesToAllocate);
    const auto retVal = std::vsnprintf(strp->get(), bytesToAllocate,
                                       fmt, args2);
    va_end(args2);

    return retVal;
}

PL_NODISCARD int vasprintf(PL_OUT std::string *strp,
                           PL_IN PL_FMT_STR(const char *)fmt,
                           std::va_list ap) noexcept
{
    std::va_list args2{ };
    va_copy(args2, ap);

    const auto errCode = std::vsnprintf(nullptr, 0, fmt, ap);

    if (errCode < 0) {
        return errCode;
    }

    const auto bytesToAllocate = 1U + static_cast<std::size_t>(errCode);

    strp->resize(bytesToAllocate);
    const auto retVal = std::vsnprintf(std::addressof((*strp)[0]),
                                       bytesToAllocate, fmt, args2);
    va_end(args2);
    strp->resize(bytesToAllocate - 1);

    return retVal;
}

PL_NODISCARD int asprintf(PL_OUT std::unique_ptr<char[]> *strp,
                          PL_IN PL_FMT_STR(const char *)fmt,
                          ...) noexcept
{
    std::va_list args1{ };
    va_start(args1, fmt);

    const auto retVal = ::pl::vasprintf(strp, fmt, args1);
    va_end(args1);

    return retVal;
}

PL_NODISCARD int asprintf(PL_OUT std::string *strp,
                          PL_IN PL_FMT_STR(const char *)fmt,
                          ...) noexcept
{
    std::va_list args1{ };
    va_start(args1, fmt);

    const auto retVal = ::pl::vasprintf(strp, fmt, args1);
    va_end(args1);

    return retVal;
}
} // namespace pl
