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
 * \file eprintf.hpp
 * \brief Exports the eprintf function.
 **/
#ifndef INCG_PL_EPRINTF_HPP
#define INCG_PL_EPRINTF_HPP
#include "annotations.hpp" // PL_IN, PL_FMT_STR, PL_PRINTF_FUNCTION
#include <cstdarg>         // std::va_list, va_start, va_end
#include <cstdio>          // std::vfprintf

namespace pl {
namespace {
/*!
 * \brief printf-style function that prints to stderr, rather than stdout.
 * \param format_string A null-terminated printf-style format string to use for
 *                      printing. May never be nullptr or otherwise be invalid.
 * \return Number of characters written if successful
 *         or negative value if an error occurred.
 * \note Behaves exactly like std::printf, but prints to stderr rather than
 *       stdout.
 * \warning Be careful not to use incorrect format specifiers or an incorrect
 *          amount of arguments for the printf-style string.
 **/
PL_PRINTF_FUNCTION(1, 2)
int eprintf(PL_IN PL_FMT_STR(const char*) format_string, ...) noexcept
{
    std::va_list args{};
    va_start(args, format_string);
    const auto ret_val = std::vfprintf(stderr, format_string, args);
    va_end(args);

    return ret_val;
}
} // anonymous namespace
} // namespace pl
#endif // INCG_PL_EPRINTF_HPP
