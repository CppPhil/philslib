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
 * \file destroy_n.hpp
 * \brief Exports the C++17 destroy_n algorithm.
**/
#ifndef INCG_PL_ALGO_DESTROY_N_HPP
#define INCG_PL_ALGO_DESTROY_N_HPP
#include "destroy_at.hpp" // pl::algo::destroy_at
#include <memory> // std::addressof

namespace pl
{
namespace algo
{
/*!
 * \brief Destroys the 'n' objects in the range starting at 'first'.
 * \param first The beginning of the range of elements to destroy.
 * \param n The number of elements to destroy. May not be larger than the
 *          amount of elements that the range beginning with 'first' holds.
 * \return The end of the range of objects that has been
 *         destroyed (i.e., std::next('first', 'n')).
 * \warning No increment, assignment, comparison, or indirection through valid
 *          instances of 'ForwardIterator' may throw exceptions.
 * \note The complexity is linear in 'n'.
**/
template <typename ForwardIterator, typename SizeType>
ForwardIterator destroy_n(ForwardIterator first, SizeType n)
{
    while (n > 0) {
        ::pl::algo::destroy_at(std::addressof(*first));

        ++first;
        --n;
    }

    return first;
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_DESTROY_N_HPP
