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
 * \file for_each_n.hpp
 * \brief Exports the C++17 for_each_n algorithm.
 **/
#ifndef INCG_PL_ALGO_FOR_EACH_N_HPP
#define INCG_PL_ALGO_FOR_EACH_N_HPP
#include "../invoke.hpp" // pl::invoke

namespace pl {
namespace algo {
/*!
 * \brief Applies the given Invocable 'unary_invocable' to the result of
 *        dereferencing every iterator in the range ['first', 'first' + 'n'),
 *        in order.
 * \param first the beginning of the range to apply the UnaryInvocable to
 * \param n the number of elements to apply the UnaryInvocable to
 * \param unary_invocable function object, to be applied to the result of
 *                        dereferencing every iterator in the
 *                        range ['first', 'first' + 'n').
 *                        The signature of the function should be equivalent
 *                        to the following:
 *                        void fun(const Type& a);
 *                        The signature does not need to have const &.
 *                        The type Type must be such that an object of type
 *                        InputIterator can be dereferenced and then implicitly
 *                        converted to Type.
 * \note If the iterator type is mutable, 'unary_invocable' may modify the
 *       elements of the range through the dereferenced iterator.
 *       If 'unary_invocable' returns a result, the result is ignored.
 * \note When using msvc will only be constexpr if msvc17 or newer is used.
 * \warning If 'n' is less than zero, the behavior is undefined.
 *          If 'first' + 'n' is beyond the end iterator of the range,
 *          the behavior is undefined.
 * \return 'first' + 'n'
 **/
template<typename InputIterator, typename SizeType, typename UnaryInvocable>
inline InputIterator
for_each_n(InputIterator first, SizeType n, UnaryInvocable unary_invocable)
{
    for (SizeType i{}; i < n; ++first) {
        ::pl::invoke(unary_invocable, *first);
        ++i;
    }

    return first;
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_FOR_EACH_N_HPP
