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
 * \file is_reference_wrapper.hpp
 * \brief Exports the is_reference_wrapper meta function to check whether
 *        or not a type is a std::reference_wrapper type.
 *        Also exports is_not_reference_wrapper.
**/
#ifndef INCG_PL_META_IS_REFERENCE_WRAPPER_HPP
#define INCG_PL_META_IS_REFERENCE_WRAPPER_HPP
#include "../type_traits.hpp" // pl::decay_t
#include "negation.hpp"       // pl::meta::negation
#include <functional>         // std::reference_wrapper
#include <type_traits>        // std::false_type, std::true_type

namespace pl {
namespace meta {
/*!
 * \brief Detects whether Ty is a std::reference_wrapper type.
 * \note This is the false case.
 *
 * Detects whether Ty is a std::reference_wrapper type.
 * Is derived from std::false_type.
**/
template <typename Ty>
struct is_reference_wrapper : public std::false_type {
};

/*!
 * \brief Detects whether Ty is a std::reference_wrapper type.
 * \note This is the true case.
 *
 * Detects whether Ty is a std::reference_wrapper type.
 * Is derived from std::true_type.
**/
template <typename Ty>
struct is_reference_wrapper<std::reference_wrapper<Ty>>
    : public std::true_type {
};

/*!
 * \brief Negation of is_reference_wrapper.
**/
template <typename Type>
using is_not_reference_wrapper = negation<is_reference_wrapper<decay_t<Type>>>;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_IS_REFERENCE_WRAPPER_HPP
