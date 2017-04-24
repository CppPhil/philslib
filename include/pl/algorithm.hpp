/*!
 * \file algorithm.hpp
 * \brief This file defines various algorithms and associated utilities.
**/
#ifndef INCG_PL_ALGORITHM_HPP
#define INCG_PL_ALGORITHM_HPP
#include "macros.hpp" // PL_IN, PL_INOUT
#include "functional.hpp" // pl::negatePredicate
#include "container.hpp" // pl::vectorlike_tag, pl::listlike_tag, pl::associative_tag
#include <algorithm> // std::rotate, std::stable_partition, std::remove, std::remove_if, ...
#include <utility> // std::pair, std::forward
#include <numeric> // std::iota
#include <iterator> // std::begin, std::end

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

template <typename UnaryPredicate, typename Container>
inline auto all_of(Container &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::all_of(std::begin(cont), std::end(cont),
                       std::forward<UnaryPredicate>(pred));
}

template <typename UnaryPredicate, typename Container>
inline auto any_of(Container &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::any_of(std::begin(cont), std::end(cont),
                       std::forward<UnaryPredicate>(pred));
}

template <typename UnaryPredicate, typename Container>
inline auto none_of(Container &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::none_of(std::begin(cont), std::end(cont),
                        std::forward<UnaryPredicate>(pred));
}

template <typename Callable, typename Container>
inline auto for_each(Container &&cont, Callable &&callable) -> decltype(auto)
{
    return std::for_each(std::begin(cont), std::end(cont),
                         std::forward<Callable>(callable));
}

template <typename Type, typename Container>
inline auto find(Container &&cont, Type &&val) -> decltype(auto)
{
    return std::find(std::begin(cont), std::end(cont),
                     std::forward<Type>(val));
}

template <typename UnaryPredicate, typename Container>
inline auto find_if(Container &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::find_if(std::begin(cont), std::end(cont),
                        std::forward<UnaryPredicate>(pred));
}

template <typename UnaryPredicate, typename Container>
inline auto find_if_not(Container &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::find_if_not(std::begin(cont), std::end(cont),
                            std::forward<UnaryPredicate>(pred));
}

template <typename Container1, typename Container2>
inline auto find_end(Container1 &&cont1, Container2 &&cont2) -> decltype(auto)
{
    return std::find_end(std::begin(cont1), std::end(cont1),
                         std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Container1, typename Container2>
inline auto find_end(Container1 &&cont1, Container2 &&cont2, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::find_end(std::begin(cont1), std::end(cont1),
                         std::begin(cont2), std::end(cont2),
                         std::forward<BinaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto find_first_of(Cont1 &&cont1, Cont2 &&cont2) -> decltype(auto)
{
    return std::find_first_of(std::begin(cont1), std::end(cont1),
                              std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto find_first_of(Cont1 &&cont1, Cont2 &&cont2, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::find_first_of(std::begin(cont1), std::end(cont1),
                              std::begin(cont2), std::end(cont2),
                              std::forward<BinaryPredicate>(pred));
}

template <typename Cont>
inline auto adjacent_find(Cont &&cont) -> decltype(auto)
{
    return std::adjacent_find(std::begin(cont), std::end(cont));
}

template <typename BinaryPredicate, typename Cont>
inline auto adjacent_find(Cont &&cont, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::adjacent_find(std::begin(cont), std::end(cont),
                              std::forward<BinaryPredicate>(pred));
}

template <typename Type, typename Cont>
inline auto count(Cont &&cont, Type &&val) -> decltype(auto)
{
    return std::count(std::begin(cont), std::end(cont),
                      std::forward<Type>(val));
}

template <typename UnaryPredicate, typename Cont>
inline auto count_if(Cont &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::count_if(std::begin(cont), std::end(cont),
                         std::forward<UnaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto mismatch(Cont1 &&cont1, Cont2 &&cont2) -> decltype(auto)
{
    return std::mismatch(std::begin(cont1), std::end(cont1),
                         std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto mismatch(Cont1 &&cont1, Cont2 &&cont2, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::mismatch(std::begin(cont1), std::end(cont1),
                         std::begin(cont2), std::end(cont2),
                         std::forward<BinaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto equal(Cont1 &&cont1, Cont2 &&cont2) -> decltype(auto)
{
    return std::equal(std::begin(cont1), std::end(cont1),
                      std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto equal(Cont1 &&cont1, Cont2 &&cont2, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::equal(std::begin(cont1), std::end(cont1),
                      std::begin(cont2), std::end(cont2),
                      std::forward<BinaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto is_permutation(Cont1 &&cont1, Cont2 &&cont2) -> decltype(auto)
{
    return std::is_permutation(std::begin(cont1), std::end(cont1),
                               std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto is_permutation(Cont1 &&cont1, Cont2 &&cont2, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::is_permutation(std::begin(cont1), std::end(cont1),
                               std::begin(cont2), std::end(cont2),
                               std::forward<BinaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto search(Cont1 &&cont1, Cont2 &&cont2) -> decltype(auto)
{
    return std::search(std::begin(cont1), std::end(cont1),
                       std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto search(Cont1 &&cont1, Cont2 &&cont2, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::search(std::begin(cont1), std::end(cont1),
                       std::begin(cont2), std::end(cont2),
                       std::forward<BinaryPredicate>(pred));
}

template <typename Size, typename Type, typename Cont>
inline auto search_n(Cont &&cont, Size &&count, Type &&val) -> decltype(auto)
{
    return std::search_n(std::begin(cont), std::end(cont),
                         std::forward<Size>(count), std::forward<Type>(val));
}

template <typename Size, typename Type, typename BinaryPredicate, typename Cont>
inline auto search_n(Cont &&cont, Size &&count, Type &&val, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::search_n(std::begin(cont), std::end(cont),
                         std::forward<Size>(count),
                         std::forward<Type>(val),
                         std::forward<BinaryPredicate>(pred));
}

template <typename Cont, typename OutputIterator>
inline auto copy(Cont &&cont, OutputIterator &&destination) -> decltype(auto)
{
    return std::copy(std::begin(cont), std::end(cont),
                     std::forward<OutputIterator>(destination));
}

template <typename Cont, typename Size, typename OutputIterator>
inline auto copy_n(Cont &&cont, Size &&n, OutputIterator &&destination) -> decltype(auto)
{
    return std::copy_n(std::begin(cont), std::forward<Size>(n),
                       std::forward<OutputIterator>(destination));
}

template <typename Cont1, typename OutputIterator, typename UnaryPredicate>
inline auto copy_if(Cont1 &&cont1, OutputIterator &&destination, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::copy_if(std::begin(cont1), std::end(cont1),
                        std::forward<OutputIterator>(destination),
                        std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename BidirectionalIterator>
inline auto copy_backward(Cont &&cont, BidirectionalIterator &&destination) -> decltype(auto)
{
    return std::copy_backward(std::begin(cont), std::end(cont),
                              std::forward<BidirectionalIterator>(destination));
}

template <typename Cont, typename OutputIterator, typename UnaryOperation>
inline auto transform(Cont &&cont, OutputIterator &&destination, UnaryOperation &&op) -> decltype(auto)
{
    return std::transform(std::begin(cont), std::end(cont),
                          std::forward<OutputIterator>(destination),
                          std::forward<UnaryOperation>(op));
}

template <typename Cont, typename InputIterator, typename OutputIterator, typename BinaryOperation>
inline auto transform(Cont &&cont, InputIterator &&beginOfSecondRange,
                      OutputIterator &&destination, BinaryOperation &&binary_op) -> decltype(auto)
{
    return std::transform(std::begin(cont), std::end(cont),
                          std::forward<InputIterator>(beginOfSecondRange),
                          std::forward<OutputIterator>(destination),
                          std::forward<BinaryOperation>(binary_op));
}

template <typename Cont, typename Type1, typename Type2>
inline auto replace(Cont &&cont, Type1 &&old_value, Type2 &&new_value) -> decltype(auto)
{
    return std::replace(std::begin(cont), std::end(cont),
                        std::forward<Type1>(old_value),
                        std::forward<Type2>(new_value));
}

template <typename Cont, typename UnaryPredicate, typename Type>
inline auto replace_if(Cont &&cont, UnaryPredicate &&pred, Type &&new_value) -> decltype(auto)
{
    return std::replace_if(std::begin(cont), std::end(cont),
                           std::forward<UnaryPredicate>(pred),
                           std::forward<Type>(new_value));
}

template <typename Cont, typename OutputIterator, typename Type1, typename Type2>
inline auto replace_copy(Cont &&cont, OutputIterator &&destination,
                         Type1 &&old_value, Type2 &&new_value) -> decltype(auto)
{
    return std::replace_copy(std::begin(cont), std::end(cont),
                             std::forward<OutputIterator>(destination),
                             std::forward<Type1>(old_value),
                             std::forward<Type2>(new_value));
}

template <typename Cont, typename OutputIterator, typename UnaryPredicate, typename Type>
inline auto replace_copy_if(Cont &&cont, OutputIterator &&destination,
                            UnaryPredicate &&pred, Type &&new_value) -> decltype(auto)
{
    return std::replace_copy_if(std::begin(cont), std::end(cont),
                                std::forward<OutputIterator>(destination),
                                std::forward<UnaryPredicate>(pred),
                                std::forward<Type>(new_value));
}

template <typename Cont, typename Type>
inline auto fill(Cont &&cont, Type &&val) -> decltype(auto)
{
    return std::fill(std::begin(cont), std::end(cont),
                     std::forward<Type>(val));
}

template <typename Cont, typename Generator>
inline auto generate(Cont &&cont, Generator &&gen) -> decltype(auto)
{
    return std::generate(std::begin(cont), std::end(cont),
                         std::forward<Generator>(gen));
}

template <typename Cont, typename Type>
inline auto remove(Cont &&cont, Type &&val) -> decltype(auto)
{
    return std::remove(std::begin(cont), std::end(cont),
                       std::forward<Type>(val));
}

template <typename Cont, typename UnaryPredicate>
inline auto remove_if(Cont &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::remove_if(std::begin(cont), std::end(cont),
                          std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename OutputIterator, typename Type>
inline auto remove_copy(Cont &&cont, OutputIterator &&destination, Type &&val) -> decltype(auto)
{
    return std::remove_copy(std::begin(cont), std::end(cont),
                            std::forward<OutputIterator>(destination),
                            std::forward<Type>(val));
}

template <typename Cont, typename OutputIterator, typename UnaryPredicate>
inline auto remove_copy_if(Cont &&cont, OutputIterator &&destination,
                           UnaryPredicate &&pred) -> decltype(auto)
{
    return std::remove_copy_if(std::begin(cont), std::end(cont),
                               std::forward<OutputIterator>(destination),
                               std::forward<UnaryPredicate>(pred));
}

template <typename Cont>
inline auto unique(Cont &&cont) -> decltype(auto)
{
    return std::unique(std::begin(cont), std::end(cont));
}

template <typename Cont, typename BinaryPredicate>
inline auto unique(Cont &&cont, BinaryPredicate &&pred) -> decltype(auto)
{
    return std::unique(std::begin(cont), std::end(cont),
                       std::forward<BinaryPredicate>(pred));
}

template <typename Cont, typename OutputIterator>
inline auto unique_copy(Cont &&cont, OutputIterator &&destination) -> decltype(auto)
{
    return std::unique_copy(std::begin(cont), std::end(cont),
                            std::forward<OutputIterator>(destination));
}

template <typename Cont, typename OutputIterator, typename BinaryPredicate>
inline auto unique_copy(Cont &&cont, OutputIterator &&destination,
                        BinaryPredicate &&pred) -> decltype(auto)
{
    return std::unique_copy(std::begin(cont), std::end(cont),
                            std::forward<OutputIterator>(destination),
                            std::forward<BinaryPredicate>(pred));
}

template <typename Cont>
inline auto reverse(Cont &&cont) -> decltype(auto)
{
    return std::reverse(std::begin(cont), std::end(cont));
}

template <typename Cont, typename OutputIterator>
inline auto reverse_copy(Cont &&cont, OutputIterator &&destination) -> decltype(auto)
{
    return std::reverse_copy(std::begin(cont), std::end(cont),
                             std::forward<OutputIterator>(destination));
}

template <typename Cont, typename Urbg>
inline auto shuffle(Cont &&cont, Urbg &&g) -> decltype(auto)
{
    return std::shuffle(std::begin(cont), std::end(cont), std::forward<Urbg>(g));
}

template <typename Cont, typename UnaryPredicate>
inline auto is_partitioned(Cont &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::is_partitioned(std::begin(cont), std::end(cont),
                               std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename UnaryPredicate>
inline auto partition(Cont &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::partition(std::begin(cont), std::end(cont),
                          std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename UnaryPredicate>
inline auto stable_partition(Cont &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::stable_partition(std::begin(cont), std::end(cont),
                                 std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename OutputIterator1, typename OutputIterator2, typename UnaryPredicate>
inline auto partition_copy(Cont &&cont, OutputIterator1 &&result_true,
                           OutputIterator2 &&result_false, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::partition_copy(std::begin(cont), std::end(cont),
                               std::forward<OutputIterator1>(result_true),
                               std::forward<OutputIterator2>(result_false),
                               std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename UnaryPredicate>
inline auto partition_point(Cont &&cont, UnaryPredicate &&pred) -> decltype(auto)
{
    return std::partition_point(std::begin(cont), std::end(cont),
                                std::forward<UnaryPredicate>(pred));
}

template <typename Cont>
inline auto sort(Cont &&cont) -> decltype(auto)
{
    return std::sort(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto sort(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::sort(std::begin(cont), std::end(cont),
                     std::forward<Compare>(comp));
}

template <typename Cont>
inline auto stable_sort(Cont &&cont) -> decltype(auto)
{
    return std::stable_sort(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto stable_sort(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::stable_sort(std::begin(cont), std::end(cont),
                            std::forward<Compare>(comp));
}

template <typename Cont>
inline auto is_sorted(Cont &&cont) -> decltype(auto)
{
    return std::is_sorted(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto is_sorted(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::is_sorted(std::begin(cont), std::end(cont),
                          std::forward<Compare>(comp));
}

template <typename Cont>
inline auto is_sorted_until(Cont &&cont) -> decltype(auto)
{
    return std::is_sorted_until(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto is_sorted_until(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::is_sorted_until(std::begin(cont), std::end(cont),
                                std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto lower_bound(Cont &&cont, Type &&val) -> decltype(auto)
{
    return std::lower_bound(std::begin(cont), std::end(cont),
                            std::forward<Type>(val));
}

template <typename Cont, typename Type, typename Compare>
inline auto lower_bound(Cont &&cont, Type &&val, Compare &&comp) -> decltype(auto)
{
    return std::lower_bound(std::begin(cont), std::end(cont),
                            std::forward<Type>(val),
                            std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto upper_bound(Cont &&cont, Type &&val) -> decltype(auto)
{
    return std::upper_bound(std::begin(cont), std::end(cont),
                            std::forward<Type>(val));
}

template <typename Cont, typename Type, typename Compare>
inline auto upper_bound(Cont &&cont, Type &&val, Compare &&comp) -> decltype(auto)
{
    return std::upper_bound(std::begin(cont), std::end(cont),
                            std::forward<Type>(val),
                            std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto equal_range(Cont &&cont, Type &&val) -> decltype(auto)
{
    return std::equal_range(std::begin(cont), std::end(cont),
                            std::forward<Type>(val));
}

template <typename Cont, typename Type, typename Compare>
inline auto equal_range(Cont &&cont, Type &&val, Compare &&comp) -> decltype(auto)
{
    return std::equal_range(std::begin(cont), std::end(cont),
                            std::forward<Type>(val),
                            std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto binary_search(Cont &&cont, Type &&val) -> decltype(auto)
{
    return std::binary_search(std::begin(cont), std::end(cont),
                              std::forward<Type>(val));
}

template <typename Cont, typename Type, typename Compare>
inline auto binary_search(Cont &&cont, Type &&val, Compare &&comp) -> decltype(auto)
{
    return std::binary_search(std::begin(cont), std::end(cont),
                              std::forward<Type>(val),
                              std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto merge(Cont1 &&cont1, Cont2 &&cont2, OutputIterator &&destination) -> decltype(auto)
{
    return std::merge(std::begin(cont1), std::end(cont1),
                      std::begin(cont2), std::end(cont2),
                      std::forward<OutputIterator>(destination));
}

template <typename Cont1, typename Cont2, typename OutputIterator, typename Compare>
inline auto merge(Cont1 &&cont1, Cont2 &&cont2, OutputIterator &&destination,
                  Compare &&comp) -> decltype(auto)
{
    return std::merge(std::begin(cont1), std::end(cont1),
                      std::begin(cont2), std::end(cont2),
                      std::forward<OutputIterator>(destination),
                      std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2>
inline auto includes(Cont1 &&cont1, Cont2 &&cont2) -> decltype(auto)
{
    return std::includes(std::begin(cont1), std::end(cont1),
                         std::begin(cont2), std::end(cont2));
}

template <typename Cont1, typename Cont2, typename Compare>
inline auto includes(Cont1 &&cont1, Cont2 &&cont2, Compare &&comp) -> decltype(auto)
{
    return std::includes(std::begin(cont1), std::end(cont1),
                         std::begin(cont2), std::end(cont2),
                         std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto set_union(Cont1 &&cont1, Cont2 &&cont2, OutputIterator &&destination) -> decltype(auto)
{
    return std::set_union(std::begin(cont1), std::end(cont1),
                          std::begin(cont2), std::end(cont2),
                          std::forward<OutputIterator>(destination));
}

template <typename Cont1, typename Cont2, typename OutputIterator, typename Compare>
inline auto set_union(Cont1 &&cont1, Cont2 &&cont2,
                      OutputIterator &&destination, Compare &&comp) -> decltype(auto)
{
    return std::set_union(std::begin(cont1), std::end(cont1),
                          std::begin(cont2), std::end(cont2),
                          std::forward<OutputIterator>(destination),
                          std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto set_intersection(Cont1 &&cont1, Cont2 &&cont2,
                             OutputIterator &&destination) -> decltype(auto)
{
    return std::set_intersection(std::begin(cont1), std::end(cont1),
                                 std::begin(cont2), std::end(cont2),
                                 std::forward<OutputIterator>(destination));
}

template <typename Cont1, typename Cont2, typename OutputIterator, typename Compare>
inline auto set_intersection(Cont1 &&cont1, Cont2 &&cont2,
                             OutputIterator &&destination, Compare &&comp) -> decltype(auto)
{
    return std::set_intersection(std::begin(cont1), std::end(cont1),
                                 std::begin(cont2), std::end(cont2),
                                 std::forward<OutputIterator>(destination),
                                 std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto set_difference(Cont1 &&cont1, Cont2 &&cont2,
                           OutputIterator &&destination) -> decltype(auto)
{
    return std::set_difference(std::begin(cont1), std::end(cont1),
                               std::begin(cont2), std::end(cont2),
                               std::forward<OutputIterator>(destination));
}

template <typename Cont1, typename Cont2, typename OutputIterator, typename Compare>
inline auto set_difference(Cont1 &&cont1, Cont2 &&cont2,
                           OutputIterator &&destination, Compare &&comp) -> decltype(auto)
{
    return std::set_difference(std::begin(cont1), std::end(cont1),
                               std::begin(cont2), std::end(cont2),
                               std::forward<OutputIterator>(destination),
                               std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto set_symmetric_difference(Cont1 &&cont1, Cont2 &&cont2,
                                     OutputIterator &&destination) -> decltype(auto)
{
    return std::set_symmetric_difference(std::begin(cont1), std::end(cont1),
                                         std::begin(cont2), std::end(cont2),
                                         std::forward<OutputIterator>(destination));
}

template <typename Cont1, typename Cont2, typename OutputIterator, typename Compare>
inline auto set_symmetric_difference(Cont1 &&cont1, Cont2 &&cont2,
                                     OutputIterator &&destination, Compare &&comp) -> decltype(auto)
{
    return std::set_symmetric_difference(std::begin(cont1), std::end(cont1),
                                         std::begin(cont2), std::end(cont2),
                                         std::forward<OutputIterator>(destination),
                                         std::forward<Compare>(comp));
}

template <typename Cont>
inline auto min_element(Cont &&cont) -> decltype(auto)
{
    return std::min_element(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto min_element(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::min_element(std::begin(cont), std::end(cont),
                            std::forward<Compare>(comp));
}

template <typename Cont>
inline auto max_element(Cont &&cont) -> decltype(auto)
{
    return std::max_element(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto max_element(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::max_element(std::begin(cont), std::end(cont),
                            std::forward<Compare>(comp));
}

template <typename Cont>
inline auto minmax_element(Cont &&cont) -> decltype(auto)
{
    return std::minmax_element(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto minmax_element(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::minmax_element(std::begin(cont), std::end(cont),
                               std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2>
inline auto lexicographical_compare(Cont1 &&cont1, Cont2 &&cont2) -> decltype(auto)
{
    return std::lexicographical_compare(std::begin(cont1), std::end(cont1),
                                        std::begin(cont2), std::end(cont2));
}

template <typename Cont1, typename Cont2, typename Compare>
inline auto lexicographical_compare(Cont1 &&cont1, Cont2 &&cont2, Compare &&comp) -> decltype(auto)
{
    return std::lexicographical_compare(std::begin(cont1), std::end(cont1),
                                        std::begin(cont2), std::end(cont2),
                                        std::forward<Compare>(comp));
}

template <typename Cont>
inline auto next_permutation(Cont &&cont) -> decltype(auto)
{
    return std::next_permutation(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto next_permutation(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::next_permutation(std::begin(cont), std::end(cont),
                                 std::forward<Compare>(comp));
}

template <typename Cont>
inline auto prev_permutation(Cont &&cont) -> decltype(auto)
{
    return std::prev_permutation(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto prev_permutation(Cont &&cont, Compare &&comp) -> decltype(auto)
{
    return std::prev_permutation(std::begin(cont), std::end(cont),
                                 std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto accumulate(Cont &&cont, Type &&init) -> decltype(auto)
{
    return std::accumulate(std::begin(cont), std::end(cont),
                           std::forward<Type>(init));
}

template <typename Cont, typename Type, typename BinaryOperation>
inline auto accumulate(Cont &&cont, Type &&init, BinaryOperation &&binary_op) -> decltype(auto)
{
    return std::accumulate(std::begin(cont), std::end(cont),
                           std::forward<Type>(init),
                           std::forward<BinaryOperation>(binary_op));
}

template <typename Cont, typename OutputIterator>
inline auto adjacent_difference(Cont &&cont, OutputIterator &&destination) -> decltype(auto)
{
    return std::adjacent_difference(std::begin(cont), std::end(cont),
                                    std::forward<OutputIterator>(destination));
}

template <typename Cont, typename OutputIterator, typename BinaryOperation>
inline auto adjacent_difference(Cont &&cont, OutputIterator &&destination,
                                BinaryOperation &&binary_op) -> decltype(auto)
{
    return std::adjacent_difference(std::begin(cont), std::end(cont),
                                    std::forward<OutputIterator>(destination),
                                    std::forward<BinaryOperation>(binary_op));
}

template <typename Cont, typename Type>
inline auto iota(Cont &&cont, Type &&val) -> decltype(auto)
{
    return std::iota(std::begin(cont), std::end(cont), std::forward<Type>(val));
}
} // namespace pl
#endif // INCG_PL_ALGORITHM_HPP
