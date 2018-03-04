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
 * \file strdup.hpp
 * \brief Exports the strdup and strndup functions, which are similar
 *        to those specified by POSIX.
**/
#ifndef INCG_PL_STRDUP_HPP
#define INCG_PL_STRDUP_HPP
#include "annotations.hpp" // PL_NODISCARD, PL_IN, PL_NULL_TERMINATED
#include <cstddef> // std::size_t
#include <cstring> // std::memcpy, std::strlen
#include <memory> // std::unique_ptr

namespace pl
{
namespace detail
{
namespace
{
/*!
 * \brief Returns std::strlen(string) or maximumLength, whichever is less.
 * \param string The null-terminated byte string to check. May not be nullptr!
 * \param maximumLength The 'maximum length'.
 * \return std::strlen(string) or maximumLength, whichever is less.
**/
std::size_t strnlen(
    PL_IN PL_NULL_TERMINATED(const char *)string,
    std::size_t maximumLength) noexcept
{
    std::size_t pos{ 0U };

    for (; pos < maximumLength; ++pos) {
        if (string[pos] == '\0') {
            break;
        }
    }

    return pos;
}
} // anonymous namespace
} // namespace detail

namespace
{
/*!
 * \brief Creates a copy of a null-terminated string.
 * \param str Pointer to the null-terminated byte string to duplicate.
 *            May not be nullptr!
 * \return The copy.
**/
PL_NODISCARD std::unique_ptr<char[]> strdup(
    PL_IN PL_NULL_TERMINATED(const char *)str) noexcept
{
      const auto bytesNeeded = std::strlen(str) + static_cast<std::size_t>(1U);
      auto returnValue = std::make_unique<char[]>(bytesNeeded);
      std::memcpy(returnValue.get(), str, bytesNeeded);
      return returnValue;
}

/*!
 * \brief Creates a unique_ptr that holds a null-terminated byte string.
 * \param str Pointer to the null-terminated byte string to duplicate.
 *            May not be nullptr!
 * \param size Maximum number of bytes to copy from 'str'.
 * \return The duplicated string.
 *
 * Creates a unique_ptr that holds a null-terminated byte string,
 * which contains copies of at most 'size' bytes from the string pointed
 * to by 'str'. If the null terminator is not encountered in the first
 * 'size' bytes, it is added to the duplicated string.
**/
PL_NODISCARD std::unique_ptr<char[]> strndup(
    PL_IN PL_NULL_TERMINATED(const char *)str,
    std::size_t size) noexcept
{
    const auto stringLength = ::pl::detail::strnlen(str, size);
    auto returnValue = std::make_unique<char[]>(stringLength + 1U);
    std::memcpy(returnValue.get(), str, stringLength);
    returnValue[stringLength] = '\0';
    return returnValue;
}
} // anonymous namespace
} // namespace pl
#endif // INCG_PL_STRDUP_HPP
