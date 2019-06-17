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
 * \file uninitialized_move_n.hpp
 * \brief Exports the C++17 uninitialized_move_n algorithm.
 **/
#ifndef INCG_PL_ALGO_UNINITIALIZED_MOVE_N_HPP
#define INCG_PL_ALGO_UNINITIALIZED_MOVE_N_HPP
#include <iterator> // std::iterator_traits
#include <memory>   // std::addressof
#include <new>      // ::operator new
#include <utility>  // std::pair, std::make_pair, std::move

namespace pl {
namespace algo {
/*!
 * \brief Moves 'count' elements from a range beginning at 'first' to an
 *        uninitialized memory area beginning at 'dest'.
 * \param first The begin iterator of the range to move from.
 * \param count The amount of elements to move from the source range beginning
 *              with 'first'. May not be larger than the amount of elements
 *              in the source range!
 * \param dest The beginning of the destination range.
 * \return A pair whose first element is an iterator to the element past
 *         the last element moved in the source range, and whose second element
 *         is an iterator to the element past the last element moved in the
 *         destination range.
 * \warning No increment, assignment, comparison, or indirection through
 *          valid instances of 'ForwardIterator' may throw exceptions.
 *          If an exception is thrown during the initialization, some objects
 *          in the source range are left in a valid but unspecified state.
 * \note The complexity is linear in 'count'.
 **/
template<typename InputIterator, typename SizeType, typename ForwardIterator>
inline std::pair<InputIterator, ForwardIterator>
uninitialized_move_n(InputIterator first, SizeType count, ForwardIterator dest)
{
    using value_type =
        typename std::iterator_traits<ForwardIterator>::value_type;

    ForwardIterator cur{dest};

    try {
        while (count > 0) {
            ::new (static_cast<void*>(std::addressof(*cur)))
                value_type(std::move(*first));

            ++first;
            ++cur;
            --count;
        }
    }
    catch (...) {
        while (dest != cur) {
            dest->~value_type();

            ++dest;
        }

        throw;
    }

    return std::make_pair(first, cur);
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_UNINITIALIZED_MOVE_N_HPP
