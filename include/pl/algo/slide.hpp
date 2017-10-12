/*!
 * \file slide.hpp
 * \brief Exports the slide algorithm.
**/
#ifndef INCG_PL_ALGO_SLIDE_HPP
#define INCG_PL_ALGO_SLIDE_HPP
#include "../annotations.hpp" // PL_IN
#include <utility> // std::pair
#include <algorithm> // std::rotate

namespace pl
{
namespace algo
{
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
 * Also note the the last iterator is not considered part of the range as
 * ranges are typically half open in C++.
**/
template <typename RandomAccessIterator>
auto slide(
    PL_IN const RandomAccessIterator &first,
    PL_IN const RandomAccessIterator &last,
    PL_IN const RandomAccessIterator &place)
-> std::pair<RandomAccessIterator, RandomAccessIterator>
{
    if (place < first) {
        return { place, std::rotate(place, first, last) };
    }

    if (last < place) {
        return { std::rotate(first, last, place), place };
    }

    return { first, last };
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_SLIDE_HPP
