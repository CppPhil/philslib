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
 * \file uncvref.hpp
 * \brief Exports the uncvref meta function.
**/
#ifndef INCG_PL_META_UNCVREF_HPP
#define INCG_PL_META_UNCVREF_HPP
#include <type_traits> // std::remove_cv, std::remove_reference_t

namespace pl
{
namespace meta
{
/*!
 * \brief Meta function to get the unqualified type of a type.
 *
 * The nested type type will have its reference type modifiers removed
 * and will have its const and volatile type qualifiers removed.
**/
template <typename Type>
struct uncvref
    : public std::remove_cv<std::remove_reference_t<Type>>
{
};

/*!
 * \brief C++14 style meta function helper that is an alias of the nested type
 *        type of pl::uncvref. Reduces the necessity of the typename keyword
 *        in application code.
**/
template <typename Type>
using uncvref_t = typename uncvref<Type>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_UNCVREF_HPP
