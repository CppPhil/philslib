/*! \file algorithm.hpp
 *  \brief This file defines various algorithms and associated utilities.
**/

#ifndef INCG_PL_ALGORITHM_HPP
#define INCG_PL_ALGORITHM_HPP
#include "macros.hpp" // PL_IN
#include "functional.hpp" // pl::negatePredicate
#include <algorithm> // std::rotate, std::stable_partition
#include <utility> // std::pair
namespace pl
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
auto slide(PL_IN const RandomAccessIterator &first,
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

/*!
 * \brief Gathers the elements that satisfy unaryPredicate at place.
 * \param first The beginning of the range to gather elements from.
 * \param last The end of the range to gather elements from.
 * \param place The place at which to gather the elements that satisfy
 *        unaryPredicate.
 * \param unaryPredicate The predicate for which an element must be evaluated
 *        to true with in order for it to be gathered at place.
 * \return The begin and end iterators of the range of the gathered elements.
 * \note All iterators passed must point into the same container.
 * \note The last iterator passed into the second parameter of this function
 *       is not considered part of the range of elements to gather from as
 *       ranges are typically half open in C++.
 * \note The end iterator returned in the pair that is returned will also
 *       point to the element after the last element considered part of the
 *       range as the pair of iterators returned also denotes a half open range.
 *
 * Gathers all the elements in the range denoted by first and last that
 * satisfy unaryPredicate at place by deviding the range into a top and a
 * bottom subrange. Elements in the top range, that satisfy the condition
 * are moved down to 'place'. Elements in the bottom range, that satisfy
 * the condition are moved up to 'place'. The order of the other elements,
 * those that did not satisfy unaryPredicate remains stable.
 * Returns the begin and end iterators to the range of the gathered elements.
 * Note that all iterators must point into the same container.
 * Also note the the last iterator is not considered part of the range as
 * ranges are typically half open in C++.
**/
template <typename BidirectionalIterator, typename UnaryPredicate>
auto gather(PL_IN const BidirectionalIterator &first,
            PL_IN const BidirectionalIterator &last,
            PL_IN const BidirectionalIterator &place,
            PL_IN const UnaryPredicate &unaryPredicate)
-> std::pair<BidirectionalIterator, BidirectionalIterator>
{
    return { std::stable_partition(first, place, negatePredicate(unaryPredicate)),
             std::stable_partition(place, last, unaryPredicate) };
}
} // namespace pl
#endif // INCG_PL_ALGORITHM_HPP
