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
 * \file type_traits.hpp
 * \brief Header file that includes the type_traits header of your standard
 *        library implementation and exports the possibly missing
 *        C++14 style _t type aliases.
**/
#ifndef INCG_PL_TYPE_TRAITS_HPP
#define INCG_PL_TYPE_TRAITS_HPP
#include <cstddef>     // std::size_t
#include <type_traits> // std::remove_const, ...

namespace pl {
template <typename Ty>
using remove_const_t = typename std::remove_const<Ty>::type;

template <typename Ty>
using remove_volatile_t = typename std::remove_volatile<Ty>::type;

template <typename Ty>
using remove_cv_t = typename std::remove_cv<Ty>::type;

template <typename Ty>
using add_const_t = typename std::add_const<Ty>::type;

template <typename Ty>
using add_volatile_t = typename std::add_volatile<Ty>::type;

template <typename Ty>
using add_cv_t = typename std::add_cv<Ty>::type;

template <typename Ty>
using remove_reference_t = typename std::remove_reference<Ty>::type;

template <typename Ty>
using add_lvalue_reference_t = typename std::add_lvalue_reference<Ty>::type;

template <typename Ty>
using add_rvalue_reference_t = typename std::add_rvalue_reference<Ty>::type;

template <typename Ty>
using make_signed_t = typename std::make_signed<Ty>::type;

template <typename Ty>
using make_unsigned_t = typename std::make_unsigned<Ty>::type;

template <typename Ty>
using remove_extent_t = typename std::remove_extent<Ty>::type;

template <typename Ty>
using remove_all_extents_t = typename std::remove_all_extents<Ty>::type;

template <typename Ty>
using remove_pointer_t = typename std::remove_pointer<Ty>::type;

template <typename Ty>
using add_pointer_t = typename std::add_pointer<Ty>::type;

template <std::size_t Len, typename... Types>
using aligned_union_t = typename std::aligned_union<Len, Types...>::type;

template <typename Ty>
using decay_t = typename std::decay<Ty>::type;

template <bool Bool, typename Ty = void>
using enable_if_t = typename std::enable_if<Bool, Ty>::type;

template <bool Bool, typename Ty, typename False>
using conditional_t = typename std::conditional<Bool, Ty, False>::type;

template <typename... Ty>
using common_type_t = typename std::common_type<Ty...>::type;

template <typename Ty>
using underlying_type_t = typename std::underlying_type<Ty>::type;
} // namespace pl
#endif // INCG_PL_TYPE_TRAITS_HPP
