#include "include/pl/strdup.hpp"
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
    std::size_t maximumLength)
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
    PL_IN PL_NULL_TERMINATED(const char *)str)
{
      const auto bytesNeeded = std::strlen(str) + static_cast<std::size_t>(1U);
      auto returnValue = std::make_unique<char[]>(bytesNeeded);
      std::memcpy(returnValue.get(), str, bytesNeeded);
      return returnValue;
}

PL_NODISCARD std::unique_ptr<char[]> strndup(
    PL_IN PL_NULL_TERMINATED(const char *)str,
    std::size_t size)
{
    const auto stringLength = strnlen(str, size);
    auto returnValue = std::make_unique<char[]>(stringLength + 1U);
    std::memcpy(returnValue.get(), str, stringLength);
    returnValue[stringLength] = '\0';
    return returnValue;
}
} // namespace pl
