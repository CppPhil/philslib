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
 * \file strcontains.hpp
 * \brief Exports strcontains.
 **/
#ifndef INCG_PL_STRCONTAINS_HPP
#define INCG_PL_STRCONTAINS_HPP
#include "annotations.hpp" // PL_NODISCARD, PL_IN, PL_NULL_TERMINATED
#include "string_view.hpp" // pl::basic_string_view
#include <cstring>         // std::strstr
#include <cwchar>          // std::wcsstr
#include <type_traits>     // std::is_pointer, std::decay_t

namespace pl {
namespace detail {
PL_NODISCARD inline bool strcontains(
    PL_IN PL_NULL_TERMINATED(const char*) haystack,
    PL_IN PL_NULL_TERMINATED(const char*) needle) noexcept
{
    return std::strstr(haystack, needle) != nullptr;
}

PL_NODISCARD inline bool strcontains(
    PL_IN PL_NULL_TERMINATED(const wchar_t*) haystack,
    PL_IN PL_NULL_TERMINATED(const wchar_t*) needle) noexcept
{
    return std::wcsstr(haystack, needle) != nullptr;
}

template<typename CharT>
PL_NODISCARD inline bool strcontains(
    PL_IN PL_NULL_TERMINATED(const CharT*) haystack,
    PL_IN PL_NULL_TERMINATED(const CharT*) needle) noexcept
{
    const auto* str1 = haystack;
    const auto* str2 = needle;

    for (;;) {
        if (*str2 == CharT{0}) { return true; }

        if (*str1 == CharT{0}) { return false; }

        if (*str1++ != *str2++) {
            ++haystack;
            str1 = haystack;
            str2 = needle;
        }
    }
}

template<typename Ptr>
inline Ptr get_pointer(Ptr ptr, std::true_type) noexcept
{
    return ptr;
}

template<typename Str>
inline auto* get_pointer(const Str& str, std::false_type) noexcept
{
    return str.c_str();
}
} // namespace detail

template<typename Str1, typename Str2>
PL_NODISCARD inline bool strcontains(
    const Str1& haystack,
    const Str2& needle) noexcept
{
    return ::pl::detail::strcontains(
        ::pl::detail::get_pointer(
            haystack, typename std::is_pointer<std::decay_t<Str1>>::type{}),
        ::pl::detail::get_pointer(
            needle, typename std::is_pointer<std::decay_t<Str2>>::type{}));
}
} // namespace pl
#endif // INCG_PL_STRCONTAINS_HPP
