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

namespace pl {
/*!
 * \brief Checks if `haystack` contains `needle`.
 * \param haystack The null-terminated byte character string to search for
 *`needle`. \param needle The null-terminated byte character string to search
 *for in `haystack`. \return true if `haystack` contains `needle`; false
 *otherwise.
 **/
PL_NODISCARD inline bool strcontains(
    PL_IN PL_NULL_TERMINATED(const char*) haystack,
    PL_IN PL_NULL_TERMINATED(const char*) needle) noexcept
{
    return std::strstr(haystack, needle) != nullptr;
}

/*!
 * \brief Checks if `haystack` contains `needle`.
 * \param haystack The null-terminated wide character string to search for
 *`needle`. \param needle The null-terminated wide character string to search
 *for in `haystack`. \return true if `haystack` contains `needle`; false
 *otherwise.
 **/
PL_NODISCARD inline bool strcontains(
    PL_IN PL_NULL_TERMINATED(const wchar_t*) haystack,
    PL_IN PL_NULL_TERMINATED(const wchar_t*) needle) noexcept
{
    return std::wcsstr(haystack, needle) != nullptr;
}

/*!
 * \brief Checks if `haystack` contains `needle`.
 * \tparam CharT The type of character that the strings consist of.
 * \param haystack The null-terminated string to search for `needle`.
 * \param needle The null-terminated string to search for in `haystack`.
 * \return true if `haystack` contains `needle`; false otherwise.
 **/
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

/*!
 * \brief Checks if `haystack` contains `needle`.
 * \tparam CharT The type of character that the string_views consist of.
 * \tparam Traits The CharTraits class for `CharT`.
 * \param haystack The string_view to search for `needle`.
 * \param needle The string_view to search for in `haystack`.
 * \return true if `haystack` contains `needle`; false otherwise.
 * \warning Traits::char_type must be the same type as CharT or
 *          the behaviour is undefined.
 **/
template<typename CharT, typename Traits>
PL_NODISCARD inline bool strcontains(
    basic_string_view<CharT, Traits> haystack,
    basic_string_view<CharT, Traits> needle) noexcept
{
    return strcontains(haystack.c_str(), needle.c_str());
}

/*!
 * \brief Checks if `haystack` contains `needle`.
 * \tparam CharT The type of character that the strings consist of.
 * \tparam Traits The CharTraits class for `CharT`.
 * \param haystack The string_view to search for `needle`.
 * \param needle The null-terminated string to search for in `haystack`.
 * \return true if `haystack` contains `needle`; false otherwise.
 * \warning Traits::char_type must be the same type as CharT or
 *          the behaviour is undefined.
 **/
template<typename CharT, typename Traits>
PL_NODISCARD inline bool strcontains(
    basic_string_view<CharT, Traits> haystack,
    PL_IN PL_NULL_TERMINATED(const CharT*) needle) noexcept
{
    return strcontains(haystack.c_str(), needle);
}

/*!
 * \brief Checks if `haystack` contains `needle`.
 * \tparam CharT The type of character that the strings consist of.
 * \tparam Traits The CharTraits class for `CharT`.
 * \param haystack The null-terminated string to search for `needle`.
 * \param needle The string_view to search for in `haystack`.
 * \return true if `haystack` contains `needle`; false otherwise.
 * \warning Traits::char_type must be the same type as CharT or
 *          the behaviour is undefined.
 **/
template<typename CharT, typename Traits>
PL_NODISCARD inline bool strcontains(
    PL_IN                            PL_NULL_TERMINATED(const CharT*) haystack,
    basic_string_view<CharT, Traits> needle) noexcept
{
    return strcontains(haystack, needle.c_str());
}
} // namespace pl
#endif // INCG_PL_STRCONTAINS_HPP
