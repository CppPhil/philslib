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

#include "../../include/pl/asprintf.hpp"
#include <cstddef> // std::size_t
#include <cstdio> // std::vsnprintf
#include <memory> // std::addressof

namespace pl
{
PL_NODISCARD int vasprintf(
    PL_OUT std::unique_ptr<char[]> *strp,
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

PL_NODISCARD int vasprintf(
    PL_OUT std::string *strp,
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
    const auto retVal
        = std::vsnprintf(
            std::addressof((*strp)[0]),
            bytesToAllocate,
            fmt,
            args2);

    va_end(args2);
    strp->resize(bytesToAllocate - 1);

    return retVal;
}

PL_NODISCARD int asprintf(
    PL_OUT std::unique_ptr<char[]> *strp,
    PL_IN PL_FMT_STR(const char *)fmt,
    ...) noexcept
{
    std::va_list args1{ };
    va_start(args1, fmt);

    const auto retVal = ::pl::vasprintf(strp, fmt, args1);
    va_end(args1);

    return retVal;
}

PL_NODISCARD int asprintf(
    PL_OUT std::string *strp,
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
