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
 * \file invoke.hpp
 * \brief Exports the invoke function template.
**/
#ifndef INCG_PL_INVOKE_HPP
#define INCG_PL_INVOKE_HPP
#include "annotations.hpp" // PL_IN
#include <ciso646> // not
#include <type_traits> // std::is_member_pointer, std::decay_t, std::true_type, std::false_type
#include <functional> // std::mem_fn
#include <utility> // std::forward

namespace pl
{
namespace detail
{
/*!
 * \brief Implementation function template of invoke.
 *        Not to be used directly.
**/
template <typename Callable, typename ...Args>
auto invokeImpl(
    std::true_type,
    PL_IN Callable &&callable,
    PL_IN Args &&...args)
    noexcept(noexcept(std::mem_fn(callable)(std::forward<Args>(args) ...)))
    -> decltype(auto)
{
    return std::mem_fn(callable)(std::forward<Args>(args) ...);
}

/*!
 * \brief Implementation function template of invoke.
 *        Not to be used directly.
**/
template <typename Callable, typename ...Args>
auto invokeImpl(
    std::false_type,
    PL_IN Callable &&callable,
    PL_IN Args &&...args)
    noexcept(noexcept(std::forward<Callable>(callable)(std::forward<Args>(args) ...)))
    -> decltype(auto)
{
    return std::forward<Callable>(callable)(std::forward<Args>(args) ...);
}
} // namespace detail

/*!
 * \brief Calls 'callable' with 'args'.
 * \param callable The callable object to be invoked.
 * \param args The arguments to pass to 'callable'.
 * \return The result of invoking 'callable' with 'args'.
 *
 * Calls the callable 'callable' with 'args'.
 * Offers a uniform interface to invoke free functions,
 * function objects (including lambdas), member function pointers,
 * as well as access non-static data members through member object pointers.
**/
template <typename Callable, typename ...Args>
auto invoke(PL_IN Callable &&callable, PL_IN Args &&...args)
    noexcept(noexcept(::pl::detail::invokeImpl(typename std::is_member_pointer<std::decay_t<Callable>>::type{ },
                                               std::forward<Callable>(callable), std::forward<Args>(args) ...)))
    -> decltype(auto)
{
    return ::pl::detail::invokeImpl(typename std::is_member_pointer<std::decay_t<Callable>>::type{ },
                                    std::forward<Callable>(callable), std::forward<Args>(args) ...);
}
} // namespace pl
#endif // INCG_PL_INVOKE_HPP
