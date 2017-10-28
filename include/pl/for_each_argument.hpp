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
 * \file for_each_argument.hpp
 * \brief Exports the forEachArgument function template.
**/
#ifndef INCG_PL_FOR_EACH_ARGUMENT_HPP
#define INCG_PL_FOR_EACH_ARGUMENT_HPP
#include "annotations.hpp" // PL_IN
#include "invoke.hpp" // pl::invoke
#include <initializer_list> // std::initializer_list
#include <utility> // std::forward

namespace pl
{
/*!
 * \brief Calls a unary callable with every argument in the template type
 *        parameter pack individually.
 * \param callable The unary callable to be invoked with every argument of
 *        the template type parameter pack.
 * \param args The arguments that callable will be called with. callable will
 *        be called with each and every element of this template type
 *        parameter pack individually one after the other.
 * \return A copy of 'callable'.
 * \note 'callable' should be cheap to copy.
 * \example pl::forEachArgument([](const auto &e) { std::cout << e << ' ';},
 *                              1, 2.1, "hello", .3F, 44U, std::string{ "world" });
**/
template <typename Callable, typename ...Args>
Callable forEachArgument(Callable callable, PL_IN Args &&...args)
{
    static_cast<void>(
        std::initializer_list<int>{
            ((void)::pl::invoke(callable, std::forward<Args>(args)), 0)...
        }
    );

    return callable;
}
} // namespace pl
#endif // INCG_PL_FOR_EACH_ARGUMENT_HPP
