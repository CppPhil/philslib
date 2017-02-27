/*! \file algorithm.hpp
 *  \brief This file defines various algorithms and associated utilities.
**/

#ifndef INCG_PL_ALGORITHM_HPP
#define INCG_PL_ALGORITHM_HPP
#include "macros.hpp" // PL_IN, PL_INOUT
#include "functional.hpp" // pl::negatePredicate
#include "container.hpp" // pl::vectorlike_tag, pl::listlike_tag, pl::associative_tag
#include <algorithm> // std::rotate, std::stable_partition, std::remove, std::remove_if
#include <utility> // std::pair, std::forward
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

namespace detail
{
/*!
 * \brief Helper function used by pl::erase. Removes all occurences that
 *        compare equal to elementToRemove from a vectorlike container.
 * \param container The container to remove all occurences of elementToRemove from.
 * \param elementToRemove The element to remove. All elements of the container that
 *        compare equal to this will be removed from the container.
**/
template <typename Container, typename Type>
inline void
eraseHelper(PL_INOUT Container &container, PL_IN const Type &elementToRemove, vectorlike_tag)
{
    container.erase(std::remove(container.begin(), container.end(), elementToRemove), container.end());
}

/*!
 * \brief helper function used by pl::eraseIf. Removes all elements for which
 *        unaryPredicate's call operator returns true from a vectorlike container.
 * \param container The container to remove all elements that satisfy unaryPredicate from.
 * \param unaryPredicate The unary predicate used to determine which elements to remove.
 *        All elements for which this object's call operator returns true will be removed
 *        from the container.
**/
template <typename Container, typename UnaryPredicate>
inline void
eraseIfHelper(PL_INOUT Container &container, PL_IN UnaryPredicate &&unaryPredicate, vectorlike_tag)
{
    container.erase(
        std::remove_if(container.begin(), container.end(),
                       std::forward<UnaryPredicate>(unaryPredicate)),
        container.end()
    );
}

/*!
 * \brief Helper function used by pl::erase. Removes all occurences that
 *        compare equal to elementToRemove from a listlike container.
 * \param container The container to remove all occurences of elementToRemove from.
 * \param elementToRemove The element to remove. All elements of the container that
 *        compare equal to this will be removed from the container.
**/
template <typename Container, typename Type>
inline void
eraseHelper(PL_INOUT Container &container, PL_IN const Type &elementToRemove, listlike_tag)
{
    container.remove(elementToRemove);
}

/*!
 * \brief helper function used by pl::eraseIf. Removes all elements for which
 *        unaryPredicate's call operator returns true from a listlike container.
 * \param container The container to remove all elements that satisfy unaryPredicate from.
 * \param unaryPredicate The unary predicate used to determine which elements to remove.
 *        All elements for which this object's call operator returns true will be removed
 *        from the container.
**/
template <typename Container, typename UnaryPredicate>
inline void
eraseIfHelper(PL_INOUT Container &container, PL_IN UnaryPredicate &&unaryPredicate, listlike_tag)
{
    container.remove_if(std::forward<UnaryPredicate>(unaryPredicate));
}

/*!
 * \brief Helper function used by pl::erase. Removes all occurences that
 *        compare equivalent to elementToRemove from a associative container.
 * \param container The container to remove all occurences equivalent to elementToRemove from.
 * \param elementToRemove The element to remove. All elements of the container that
 *        compare equivalent to this will be removed from the container.
**/
template <typename Container, typename Type>
inline void
eraseHelper(PL_INOUT Container &container, PL_IN const Type &elementToRemove, associative_tag)
{
    container.erase(elementToRemove);
}

/*!
 * \brief helper function used by pl::eraseIf. Removes all elements for which
 *        unaryPredicate's call operator returns true from a associative container.
 * \param container The container to remove all elements that satisfy unaryPredicate from.
 * \param unaryPredicate The unary predicate used to determine which elements to remove.
 *        All elements for which this object's call operator returns true will be removed
 *        from the container.
**/
template <typename Container, typename UnaryPredicate>
inline void
eraseIfHelper(PL_INOUT Container &container, UnaryPredicate unaryPredicate, associative_tag)
{
    const auto endIter = container.end();
    for (auto iterator = container.begin(); iterator != endIter;) {
        if (unaryPredicate(*iterator)) {
            container.erase(iterator++);
        } else {
            ++iterator;
        }
    }
}
} // namespace detail

/*!
 * \brief Function to remove elements from a container.
 * \param container The container to remove elements from.
 * \param elementToRemove The value of the elements to remove.
 * \note If the container is a std::vector, std::deque, std::forward_list or a
 *       std::list all elements that compare equal
 *       (using operator==) will be removed from the container.
 * \note If the container is a std::set, std::map, std::multiset, std::multimap,
 *       std::unordered_set, std::unordered_map, std::unordered_multiset or a
 *       std::unordered_multimap all pairs whose keys compare equivalent
 *       (using !((elementFromContainer < elementToRemove) || (elementFromContainer < elementToRemove)))
 *       will be removed from the container.
 * \note For std::set, std::map, std::multiset, std::multimap,
 *       std::unordered_set, std::unordered_map, std::unordered_multiset and
 *       std::unordered_multimap the function expects the key of the pair
 *       to remove from the container. So pass the key of the pair(s) to
 *       remove into elementToRemove.
**/
template <typename Container, typename Type>
inline void erase(PL_INOUT Container &container, PL_IN const Type &elementToRemove)
{
    detail::eraseHelper(container, elementToRemove, container_traits_category<Container>{ });
}

/*!
 * \brief Removes all elements from container that satisfy unaryPredicate.
 * \param container The container to remove elements from.
 * \param unaryPredicate The unary predicate that will select elements for removal.
 *
 * All elements from container for which the call operator of unaryPredicate
 * returns true will be removed from the container. The call operator
 * of unaryPredicate is invoked with each element of the container to determine
 * if it is to be removed.
**/
template <typename Container, typename UnaryPredicate>
inline void eraseIf(PL_INOUT Container &container, PL_IN UnaryPredicate &&unaryPredicate)
{
    detail::eraseIfHelper(
        container,
        std::forward<UnaryPredicate>(unaryPredicate),
        container_traits_category<Container>{ }
    );
}
} // namespace pl
#endif // INCG_PL_ALGORITHM_HPP
