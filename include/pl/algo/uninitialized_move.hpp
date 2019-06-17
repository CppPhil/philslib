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
 * \file uninitialized_move.hpp
 * \brief Exports the C++17 uninitialized_move algorithm.
 **/
#ifndef INCG_PL_ALGO_UNINITIALIZED_MOVE_HPP
#define INCG_PL_ALGO_UNINITIALIZED_MOVE_HPP
#include <iterator> // std::iterator_traits
#include <memory>   // std::addressof
#include <new>      // ::operator new
#include <utility>  // std::move

namespace pl {
namespace algo {
/*!
 * \brief Moves elements from the range ['first', 'last') to an uninitialized
 *        memory area beginning at 'dest'.
 * \param first The begin iterator of the range to move from.
 * \param last The end iterator of the range to move from.
 * \param dest The beginning of the destination range.
 * \return Iterator to the element past the last element moved.
 * \warning No increment, assignment, comparison or indirection through
 *          valid instances of 'ForwardIterator' may throw exceptions!
 *          If an exception is thrown during the initialization, some objects
 *          in ['first', 'last') are left in a valid but unspecified state.
 * \note The complexity is linear in the distance between 'first' and 'last'.
 **/
template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_move(
    InputIterator   first,
    InputIterator   last,
    ForwardIterator dest)
{
    using value_type =
        typename std::iterator_traits<ForwardIterator>::value_type;

    ForwardIterator cur{dest};

    try {
        while (first != last) {
            ::new (static_cast<void*>(std::addressof(*cur)))
                value_type(std::move(*first));

            ++first;
            ++cur;
        }

        return cur;
    }
    catch (...) {
        while (dest != cur) {
            dest->~value_type();
            ++dest;
        }

        throw;
    }
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_UNINITIALIZED_MOVE_HPP
