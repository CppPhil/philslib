/*!
 * \file gather.hpp
 * \brief Exports the gather algorithm.
**/
#ifndef INCG_PL_ALGO_GATHER_HPP
#define INCG_PL_ALGO_GATHER_HPP
#include "../macros.hpp" // PL_IN
#include "../functional.hpp" // pl::negatePredicate
#include <utility> // std::pair
#include <algorithm> // std::stable_partition

namespace pl
{
namespace algo
{
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
    return { std::stable_partition(first, place, ::pl::negatePredicate(unaryPredicate)),
             std::stable_partition(place, last, unaryPredicate) };
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_GATHER_HPP
