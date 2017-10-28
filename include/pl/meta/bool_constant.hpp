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
 * \file bool_constant.hpp
 * \brief Exports the bool_constant helper alias template that is defined
 *        in the C++17 C++ standard library.
**/
#ifndef INCG_PL_META_BOOL_CONSTANT_HPP
#define INCG_PL_META_BOOL_CONSTANT_HPP
#include <type_traits> // std::integral_constant

namespace pl
{
namespace meta
{
/*!
 * \brief The C++17 bool_constant alias template.
 *
 * The helper alias template defined for the common case
 * where the first template parameter of std::integral_constant is bool.
**/
template <bool BooleanValue>
using bool_constant = std::integral_constant<bool, BooleanValue>;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_BOOL_CONSTANT_HPP
