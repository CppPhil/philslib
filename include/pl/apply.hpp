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
 * \file apply.hpp
 * \brief Exports the apply function template.
 **/
#ifndef INCG_PL_APPLY_HPP
#define INCG_PL_APPLY_HPP
#include "annotations.hpp" // PL_IN
#include "compiler.hpp"    // PL_COMPILER, PL_COMPILER_MSVC
#include "invoke.hpp"      // pl::invoke
#include "type_traits.hpp" // pl::decay_t
#include <cstddef>         // std::size_t
#include <tuple>           // std::get, std::tuple_size
#include <utility> // std::index_sequence, std::make_index_sequence, std::forward

#if PL_COMPILER == PL_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 4100) // unreferenced formal parameter
#endif                          // PL_COMPILER == PL_COMPILER_MSVC
namespace pl {
namespace detail {
/*!
 * \brief Implementation function of apply; not to be used directly!
 **/
template<typename Callable, typename TupleLike, std::size_t... Indices>
inline auto apply_impl(
    PL_IN Callable&& callable,
    PL_IN TupleLike&& tuple_like,
    std::index_sequence<Indices...>) -> decltype(auto)
{
    return ::pl::invoke(
        std::forward<Callable>(callable),
        std::get<Indices>(std::forward<TupleLike>(tuple_like))...);
}
} // namespace detail

/*!
 * \brief Invokes the callable object 'callable' with a tuple of arguments.
 * \param callable The callable object to be invoked.
 * \param tuple_like The tuple whose elements to be used as arguments to
 *                   'callable'
 * \return The result that was returned by 'callable'.
 * \note 'tuple_like' need not be std::tuple, and instead may be anything
 *       that supports std::get and std::tuple_size; in particular,
 *       std::array and std::pair may be used.
 **/
template<typename Callable, typename TupleLike>
inline auto apply(PL_IN Callable&& callable, PL_IN TupleLike&& tuple_like)
    -> decltype(auto)
{
    return detail::apply_impl(
        std::forward<Callable>(callable),
        std::forward<TupleLike>(tuple_like),
        std::make_index_sequence<std::tuple_size<decay_t<TupleLike>>::value>{});
}
} // namespace pl
#if PL_COMPILER == PL_COMPILER_MSVC
#pragma warning(pop)
#endif // PL_COMPILER == PL_COMPILER_MSVC
#endif // INCG_PL_APPLY_HPP
