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
 * \file disjunction.hpp
 * \brief Exports the disjunction C++17 meta function.
 **/
#ifndef INCG_PL_META_DISJUNCTION_HPP
#define INCG_PL_META_DISJUNCTION_HPP
#include "../type_traits.hpp" // pl::conditional_t
#include <type_traits>        // std::false_type

namespace pl {
namespace meta {
/*!
 * \brief Forms the logical disjunction of the type traits 'Traits',
 *        effectively performing a logical 'or' on the sequence of traits.
 **/
template<typename...>
struct disjunction : public std::false_type {};

/*!
 * \brief Forms the logical disjunction of the type traits 'Traits',
 *        effectively performing a logical 'or' on the sequence of traits.
 **/
template<typename Trait1>
struct disjunction<Trait1> : public Trait1 {};

/*!
 * \brief Forms the logical disjunction of the type traits 'Traits',
 *        effectively performing a logical 'or' on the sequence of traits.
 **/
template<typename Trait1, typename... Traits>
struct disjunction<Trait1, Traits...>
  : public conditional_t<bool(Trait1::value), Trait1, disjunction<Traits...>> {
};
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_DISJUNCTION_HPP
