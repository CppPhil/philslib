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
 * \file void_t.hpp
 * \brief Exports the void_t metafunction from C++17.
 **/
#ifndef INCG_PL_META_VOID_T_HPP
#define INCG_PL_META_VOID_T_HPP

namespace pl {
namespace meta {
namespace detail {
/*!
 * \brief Implementation struct of pl::meta::void_t, not to be used directly.
 **/
template<typename... Args>
struct void_t_impl {
    using type = void; /* C++14 compatibility */
};
} // namespace detail

/*!
 * \brief Utility metafunction that maps a sequence of any types to the type
 *        void.
 * \note This is just like std::void_t from C++17.
 *
 * This metafunction is used in template metaprogramming to detect
 * ill-formed types in SFINAE contexts.
 **/
template<typename... Args>
using void_t = typename detail::void_t_impl<Args...>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_VOID_T_HPP
