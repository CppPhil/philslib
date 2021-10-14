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
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC, PL_COMPILER_VERSION, PL_COMPILER_VERSION_CHECK
#include <type_traits> // std::is_pointer, std::decay_t

namespace pl {
namespace detail {
namespace {
template<typename CharT>
#if (PL_COMPILER != PL_COMPILER_MSVC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
constexpr
#endif
    bool
    strcontains(
        PL_IN PL_NULL_TERMINATED(const CharT*) haystack,
        PL_IN PL_NULL_TERMINATED(const CharT*) needle) noexcept
{
    const auto* str1 = haystack;
    const auto* str2 = needle;

    for (;;) {
        if (*str2 == CharT{0}) {
            return true;
        }

        if (*str1 == CharT{0}) {
            return false;
        }

        if (*str1++ != *str2++) {
            ++haystack;
            str1 = haystack;
            str2 = needle;
        }
    }
}

template<typename Ptr>
#if (PL_COMPILER != PL_COMPILER_MSVC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
constexpr
#endif
    Ptr
    get_pointer(Ptr ptr, std::true_type) noexcept
{
    return ptr;
}

template<typename Str>
#if (PL_COMPILER != PL_COMPILER_MSVC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
constexpr
#endif
    auto
    get_pointer(const Str& str, std::false_type) noexcept
{
    return str.data();
}
} // anonymous namespace
} // namespace detail

namespace {
/*!
 * \brief Checks if the string `haystack` contains the string `needle`.
 * \tparam Str1 The type of the first parameter.
 * \tparam Str2 The type of the second parameter.
 * \param haystack The null-terminated string to search for `needle`.
 * \param needle The null-terminated string to search `haystack` for.
 * \return true if `haystack` contains `needle`; otherwise false.
 **/
template<typename Str1, typename Str2>
PL_NODISCARD
#if (PL_COMPILER != PL_COMPILER_MSVC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
    constexpr
#endif
    bool
    strcontains(const Str1& haystack, const Str2& needle) noexcept
{
    return ::pl::detail::strcontains(
        ::pl::detail::get_pointer(
            haystack, typename std::is_pointer<std::decay_t<Str1>>::type{}),
        ::pl::detail::get_pointer(
            needle, typename std::is_pointer<std::decay_t<Str2>>::type{}));
}
} // anonymous namespace
} // namespace pl
#endif // INCG_PL_STRCONTAINS_HPP
