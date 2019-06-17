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
 * \file slide.hpp
 * \brief Exports the slide algorithm.
 **/
#ifndef INCG_PL_ALGO_SLIDE_HPP
#define INCG_PL_ALGO_SLIDE_HPP
#include <algorithm> // std::rotate
#include <utility>   // std::pair

namespace pl {
namespace algo {
/*!
 * \brief The slide algorithm slides a range in a container to another place
 *        in the same container.
 * \param first The beginning of the range to slide.
 * \param last The end of the range to slide. (One after the last element
 *        considered part of the range)
 * \param place The position in the container to slide the range to.
 * \return The new first and last iterators of the range that was slid
 *         within the container. (note that last is one after the last element
 *         considered part of the range)
 * \note All iterators passed in must point into the same container.
 * \note The last iterator is not considered part of the range. Ranges are
 *       typically half open in C++.
 * \note After running this function the range denoted by first and last will
 *       now begin at place.
 *
 * Slides the range in a container denoted by first and last to place
 * in the same container. After the operation the range denoted by first
 * and last will now begin at place. Returns the new first and last iterators
 * of the range that was slid within the container.
 * Note that all iterators must point into the same container
 * Also note the last iterator is not considered part of the range as
 * ranges are typically half open in C++.
 **/
template<typename RandomAccessIterator>
inline auto slide(
    RandomAccessIterator first,
    RandomAccessIterator last,
    RandomAccessIterator place)
    -> std::pair<RandomAccessIterator, RandomAccessIterator>
{
    if (place < first) { return {place, std::rotate(place, first, last)}; }

    if (last < place) { return {std::rotate(first, last, place), place}; }

    return {first, last};
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_SLIDE_HPP
