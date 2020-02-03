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
 * \file unwrap_ref_decay.hpp
 * \brief Exports the unwrap_ref_decay meta function.
 **/
#ifndef INCG_PL_META_UNWRAP_REF_DECAY_HPP
#define INCG_PL_META_UNWRAP_REF_DECAY_HPP
#include "unwrap_reference.hpp" // pl::meta::unwrap_reference
#include <type_traits>          // std::decay_t

namespace pl {
namespace meta {
/*!
 * \brief unwrap_ref_decay C++20 meta function
 * \tparam Type the template type parameter.
 *
 * If `Type` is std::reference_wrapper<T> for some type T, ignoring
 * cv-qualification and referenceness, provides a member typedef type that
 * names T&; otherwise, provides a member typedef type that names
 * std::decay_t<Type>.
 **/
template<typename Type>
struct unwrap_ref_decay : public unwrap_reference<std::decay_t<Type>> {
};

/*!
 * \brief C++14 style helper type alias for unwrap_ref_decay
 **/
template<typename Type>
using unwrap_ref_decay_t = typename unwrap_ref_decay<Type>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_UNWRAP_REF_DECAY_HPP
