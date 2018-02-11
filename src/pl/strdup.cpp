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

#include "../../include/pl/strdup.hpp"
#include <cstddef> // std::size_t
#include <cstring> // std::memcpy, std::strlen

namespace pl
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
    const std::size_t maximumLength) noexcept
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

PL_NODISCARD std::unique_ptr<char[]> strdup(
    PL_IN PL_NULL_TERMINATED(const char *)str) noexcept
{
      const auto bytesNeeded = std::strlen(str) + static_cast<std::size_t>(1U);
      auto returnValue = std::make_unique<char[]>(bytesNeeded);
      std::memcpy(returnValue.get(), str, bytesNeeded);
      return returnValue;
}

PL_NODISCARD std::unique_ptr<char[]> strndup(
    PL_IN PL_NULL_TERMINATED(const char *)str,
    const std::size_t size) noexcept
{
    const auto stringLength = strnlen(str, size);
    auto returnValue = std::make_unique<char[]>(stringLength + 1U);
    std::memcpy(returnValue.get(), str, stringLength);
    returnValue[stringLength] = '\0';
    return returnValue;
}
} // namespace pl
