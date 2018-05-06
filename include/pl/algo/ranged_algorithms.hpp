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
 * \file ranged_algorithms.hpp
 * \brief Exports 'ranged' versions of standard library algorithms, that
 *        accept a container directly rather than the begin and end iterators.
**/
#ifndef INCG_PL_ALGO_RANGED_ALGORITHMS_HPP
#define INCG_PL_ALGO_RANGED_ALGORITHMS_HPP
#include <algorithm> // std::all_of, std::any_of, ...
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota
#include <utility>   // std::forward

namespace pl {
namespace algo {
template <typename UnaryPredicate, typename Container>
inline auto all_of(Container&& cont, UnaryPredicate&& pred) -> decltype(auto)
{
    return std::all_of(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename UnaryPredicate, typename Container>
inline auto any_of(Container&& cont, UnaryPredicate&& pred) -> decltype(auto)
{
    return std::any_of(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename UnaryPredicate, typename Container>
inline auto none_of(Container&& cont, UnaryPredicate&& pred) -> decltype(auto)
{
    return std::none_of(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename Callable, typename Container>
inline auto for_each(Container&& cont, Callable&& callable) -> decltype(auto)
{
    return std::for_each(
        std::begin(cont), std::end(cont), std::forward<Callable>(callable));
}

template <typename Type, typename Container>
inline auto find(Container&& cont, Type&& val) -> decltype(auto)
{
    return std::find(std::begin(cont), std::end(cont), std::forward<Type>(val));
}

template <typename UnaryPredicate, typename Container>
inline auto find_if(Container&& cont, UnaryPredicate&& pred) -> decltype(auto)
{
    return std::find_if(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename UnaryPredicate, typename Container>
inline auto find_if_not(Container&& cont, UnaryPredicate&& pred)
    -> decltype(auto)
{
    return std::find_if_not(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename Container1, typename Container2>
inline auto find_end(Container1&& cont1, Container2&& cont2) -> decltype(auto)
{
    return std::find_end(
        std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Container1, typename Container2>
inline auto
find_end(Container1&& cont1, Container2&& cont2, BinaryPredicate&& pred)
    -> decltype(auto)
{
    return std::find_end(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<BinaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto find_first_of(Cont1&& cont1, Cont2&& cont2) -> decltype(auto)
{
    return std::find_first_of(
        std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto find_first_of(Cont1&& cont1, Cont2&& cont2, BinaryPredicate&& pred)
    -> decltype(auto)
{
    return std::find_first_of(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<BinaryPredicate>(pred));
}

template <typename Cont>
inline auto adjacent_find(Cont&& cont) -> decltype(auto)
{
    return std::adjacent_find(std::begin(cont), std::end(cont));
}

template <typename BinaryPredicate, typename Cont>
inline auto adjacent_find(Cont&& cont, BinaryPredicate&& pred) -> decltype(auto)
{
    return std::adjacent_find(
        std::begin(cont), std::end(cont), std::forward<BinaryPredicate>(pred));
}

template <typename Type, typename Cont>
inline auto count(Cont&& cont, Type&& val) -> decltype(auto)
{
    return std::count(
        std::begin(cont), std::end(cont), std::forward<Type>(val));
}

template <typename UnaryPredicate, typename Cont>
inline auto count_if(Cont&& cont, UnaryPredicate&& pred) -> decltype(auto)
{
    return std::count_if(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto mismatch(Cont1&& cont1, Cont2&& cont2) -> decltype(auto)
{
    return std::mismatch(
        std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto mismatch(Cont1&& cont1, Cont2&& cont2, BinaryPredicate&& pred)
    -> decltype(auto)
{
    return std::mismatch(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<BinaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto equal(Cont1&& cont1, Cont2&& cont2) -> decltype(auto)
{
    return std::equal(
        std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto equal(Cont1&& cont1, Cont2&& cont2, BinaryPredicate&& pred)
    -> decltype(auto)
{
    return std::equal(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<BinaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto is_permutation(Cont1&& cont1, Cont2&& cont2) -> decltype(auto)
{
    return std::is_permutation(
        std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto is_permutation(Cont1&& cont1, Cont2&& cont2, BinaryPredicate&& pred)
    -> decltype(auto)
{
    return std::is_permutation(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<BinaryPredicate>(pred));
}

template <typename Cont1, typename Cont2>
inline auto search(Cont1&& cont1, Cont2&& cont2) -> decltype(auto)
{
    return std::search(
        std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2));
}

template <typename BinaryPredicate, typename Cont1, typename Cont2>
inline auto search(Cont1&& cont1, Cont2&& cont2, BinaryPredicate&& pred)
    -> decltype(auto)
{
    return std::search(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<BinaryPredicate>(pred));
}

template <typename Size, typename Type, typename Cont>
inline auto search_n(Cont&& cont, Size&& count, Type&& val) -> decltype(auto)
{
    return std::search_n(
        std::begin(cont),
        std::end(cont),
        std::forward<Size>(count),
        std::forward<Type>(val));
}

template <typename Size, typename Type, typename BinaryPredicate, typename Cont>
inline auto
search_n(Cont&& cont, Size&& count, Type&& val, BinaryPredicate&& pred)
    -> decltype(auto)
{
    return std::search_n(
        std::begin(cont),
        std::end(cont),
        std::forward<Size>(count),
        std::forward<Type>(val),
        std::forward<BinaryPredicate>(pred));
}

template <typename Cont, typename OutputIterator>
inline auto copy(Cont&& cont, OutputIterator&& destination) -> decltype(auto)
{
    return std::copy(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination));
}

template <typename Cont, typename Size, typename OutputIterator>
inline auto copy_n(Cont&& cont, Size&& n, OutputIterator&& destination)
    -> decltype(auto)
{
    return std::copy_n(
        std::begin(cont),
        std::forward<Size>(n),
        std::forward<OutputIterator>(destination));
}

template <typename Cont1, typename OutputIterator, typename UnaryPredicate>
inline auto
copy_if(Cont1&& cont1, OutputIterator&& destination, UnaryPredicate&& pred)
    -> decltype(auto)
{
    return std::copy_if(
        std::begin(cont1),
        std::end(cont1),
        std::forward<OutputIterator>(destination),
        std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename BidirectionalIterator>
inline auto copy_backward(Cont&& cont, BidirectionalIterator&& destination)
    -> decltype(auto)
{
    return std::copy_backward(
        std::begin(cont),
        std::end(cont),
        std::forward<BidirectionalIterator>(destination));
}

template <typename Cont, typename OutputIterator, typename UnaryOperation>
inline auto
transform(Cont&& cont, OutputIterator&& destination, UnaryOperation&& op)
    -> decltype(auto)
{
    return std::transform(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination),
        std::forward<UnaryOperation>(op));
}

template <typename Cont,
          typename InputIterator,
          typename OutputIterator,
          typename BinaryOperation>
inline auto transform(
    Cont&&            cont,
    InputIterator&&   beginOfSecondRange,
    OutputIterator&&  destination,
    BinaryOperation&& binary_op) -> decltype(auto)
{
    return std::transform(
        std::begin(cont),
        std::end(cont),
        std::forward<InputIterator>(beginOfSecondRange),
        std::forward<OutputIterator>(destination),
        std::forward<BinaryOperation>(binary_op));
}

template <typename Cont, typename Type1, typename Type2>
inline auto replace(Cont&& cont, Type1&& old_value, Type2&& new_value)
    -> decltype(auto)
{
    return std::replace(
        std::begin(cont),
        std::end(cont),
        std::forward<Type1>(old_value),
        std::forward<Type2>(new_value));
}

template <typename Cont, typename UnaryPredicate, typename Type>
inline auto replace_if(Cont&& cont, UnaryPredicate&& pred, Type&& new_value)
    -> decltype(auto)
{
    return std::replace_if(
        std::begin(cont),
        std::end(cont),
        std::forward<UnaryPredicate>(pred),
        std::forward<Type>(new_value));
}

template <typename Cont,
          typename OutputIterator,
          typename Type1,
          typename Type2>
inline auto replace_copy(
    Cont&&           cont,
    OutputIterator&& destination,
    Type1&&          old_value,
    Type2&&          new_value) -> decltype(auto)
{
    return std::replace_copy(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination),
        std::forward<Type1>(old_value),
        std::forward<Type2>(new_value));
}

template <typename Cont,
          typename OutputIterator,
          typename UnaryPredicate,
          typename Type>
inline auto replace_copy_if(
    Cont&&           cont,
    OutputIterator&& destination,
    UnaryPredicate&& pred,
    Type&&           new_value) -> decltype(auto)
{
    return std::replace_copy_if(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination),
        std::forward<UnaryPredicate>(pred),
        std::forward<Type>(new_value));
}

template <typename Cont, typename Type>
inline auto fill(Cont&& cont, Type&& val) -> decltype(auto)
{
    return std::fill(std::begin(cont), std::end(cont), std::forward<Type>(val));
}

template <typename Cont, typename Generator>
inline auto generate(Cont&& cont, Generator&& gen) -> decltype(auto)
{
    return std::generate(
        std::begin(cont), std::end(cont), std::forward<Generator>(gen));
}

template <typename Cont, typename Type>
inline auto remove(Cont&& cont, Type&& val) -> decltype(auto)
{
    return std::remove(
        std::begin(cont), std::end(cont), std::forward<Type>(val));
}

template <typename Cont, typename UnaryPredicate>
inline auto remove_if(Cont&& cont, UnaryPredicate&& pred) -> decltype(auto)
{
    return std::remove_if(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename OutputIterator, typename Type>
inline auto remove_copy(Cont&& cont, OutputIterator&& destination, Type&& val)
    -> decltype(auto)
{
    return std::remove_copy(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination),
        std::forward<Type>(val));
}

template <typename Cont, typename OutputIterator, typename UnaryPredicate>
inline auto
remove_copy_if(Cont&& cont, OutputIterator&& destination, UnaryPredicate&& pred)
    -> decltype(auto)
{
    return std::remove_copy_if(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination),
        std::forward<UnaryPredicate>(pred));
}

template <typename Cont>
inline auto unique(Cont&& cont) -> decltype(auto)
{
    return std::unique(std::begin(cont), std::end(cont));
}

template <typename Cont, typename BinaryPredicate>
inline auto unique(Cont&& cont, BinaryPredicate&& pred) -> decltype(auto)
{
    return std::unique(
        std::begin(cont), std::end(cont), std::forward<BinaryPredicate>(pred));
}

template <typename Cont, typename OutputIterator>
inline auto unique_copy(Cont&& cont, OutputIterator&& destination)
    -> decltype(auto)
{
    return std::unique_copy(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination));
}

template <typename Cont, typename OutputIterator, typename BinaryPredicate>
inline auto
unique_copy(Cont&& cont, OutputIterator&& destination, BinaryPredicate&& pred)
    -> decltype(auto)
{
    return std::unique_copy(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination),
        std::forward<BinaryPredicate>(pred));
}

template <typename Cont>
inline auto reverse(Cont&& cont) -> decltype(auto)
{
    return std::reverse(std::begin(cont), std::end(cont));
}

template <typename Cont, typename OutputIterator>
inline auto reverse_copy(Cont&& cont, OutputIterator&& destination)
    -> decltype(auto)
{
    return std::reverse_copy(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination));
}

template <typename Cont, typename Urbg>
inline auto shuffle(Cont&& cont, Urbg&& g) -> decltype(auto)
{
    return std::shuffle(
        std::begin(cont), std::end(cont), std::forward<Urbg>(g));
}

template <typename Cont, typename UnaryPredicate>
inline auto is_partitioned(Cont&& cont, UnaryPredicate&& pred) -> decltype(auto)
{
    return std::is_partitioned(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename UnaryPredicate>
inline auto partition(Cont&& cont, UnaryPredicate&& pred) -> decltype(auto)
{
    return std::partition(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename UnaryPredicate>
inline auto stable_partition(Cont&& cont, UnaryPredicate&& pred)
    -> decltype(auto)
{
    return std::stable_partition(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename Cont,
          typename OutputIterator1,
          typename OutputIterator2,
          typename UnaryPredicate>
inline auto partition_copy(
    Cont&&            cont,
    OutputIterator1&& result_true,
    OutputIterator2&& result_false,
    UnaryPredicate&&  pred) -> decltype(auto)
{
    return std::partition_copy(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator1>(result_true),
        std::forward<OutputIterator2>(result_false),
        std::forward<UnaryPredicate>(pred));
}

template <typename Cont, typename UnaryPredicate>
inline auto partition_point(Cont&& cont, UnaryPredicate&& pred)
    -> decltype(auto)
{
    return std::partition_point(
        std::begin(cont), std::end(cont), std::forward<UnaryPredicate>(pred));
}

template <typename Cont>
inline auto sort(Cont&& cont) -> decltype(auto)
{
    return std::sort(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto sort(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::sort(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont>
inline auto stable_sort(Cont&& cont) -> decltype(auto)
{
    return std::stable_sort(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto stable_sort(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::stable_sort(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont>
inline auto is_sorted(Cont&& cont) -> decltype(auto)
{
    return std::is_sorted(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto is_sorted(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::is_sorted(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont>
inline auto is_sorted_until(Cont&& cont) -> decltype(auto)
{
    return std::is_sorted_until(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto is_sorted_until(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::is_sorted_until(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto lower_bound(Cont&& cont, Type&& val) -> decltype(auto)
{
    return std::lower_bound(
        std::begin(cont), std::end(cont), std::forward<Type>(val));
}

template <typename Cont, typename Type, typename Compare>
inline auto lower_bound(Cont&& cont, Type&& val, Compare&& comp)
    -> decltype(auto)
{
    return std::lower_bound(
        std::begin(cont),
        std::end(cont),
        std::forward<Type>(val),
        std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto upper_bound(Cont&& cont, Type&& val) -> decltype(auto)
{
    return std::upper_bound(
        std::begin(cont), std::end(cont), std::forward<Type>(val));
}

template <typename Cont, typename Type, typename Compare>
inline auto upper_bound(Cont&& cont, Type&& val, Compare&& comp)
    -> decltype(auto)
{
    return std::upper_bound(
        std::begin(cont),
        std::end(cont),
        std::forward<Type>(val),
        std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto equal_range(Cont&& cont, Type&& val) -> decltype(auto)
{
    return std::equal_range(
        std::begin(cont), std::end(cont), std::forward<Type>(val));
}

template <typename Cont, typename Type, typename Compare>
inline auto equal_range(Cont&& cont, Type&& val, Compare&& comp)
    -> decltype(auto)
{
    return std::equal_range(
        std::begin(cont),
        std::end(cont),
        std::forward<Type>(val),
        std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto binary_search(Cont&& cont, Type&& val) -> decltype(auto)
{
    return std::binary_search(
        std::begin(cont), std::end(cont), std::forward<Type>(val));
}

template <typename Cont, typename Type, typename Compare>
inline auto binary_search(Cont&& cont, Type&& val, Compare&& comp)
    -> decltype(auto)
{
    return std::binary_search(
        std::begin(cont),
        std::end(cont),
        std::forward<Type>(val),
        std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto merge(Cont1&& cont1, Cont2&& cont2, OutputIterator&& destination)
    -> decltype(auto)
{
    return std::merge(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination));
}

template <typename Cont1,
          typename Cont2,
          typename OutputIterator,
          typename Compare>
inline auto merge(
    Cont1&&          cont1,
    Cont2&&          cont2,
    OutputIterator&& destination,
    Compare&&        comp) -> decltype(auto)
{
    return std::merge(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination),
        std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2>
inline auto includes(Cont1&& cont1, Cont2&& cont2) -> decltype(auto)
{
    return std::includes(
        std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2));
}

template <typename Cont1, typename Cont2, typename Compare>
inline auto includes(Cont1&& cont1, Cont2&& cont2, Compare&& comp)
    -> decltype(auto)
{
    return std::includes(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto
set_union(Cont1&& cont1, Cont2&& cont2, OutputIterator&& destination)
    -> decltype(auto)
{
    return std::set_union(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination));
}

template <typename Cont1,
          typename Cont2,
          typename OutputIterator,
          typename Compare>
inline auto set_union(
    Cont1&&          cont1,
    Cont2&&          cont2,
    OutputIterator&& destination,
    Compare&&        comp) -> decltype(auto)
{
    return std::set_union(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination),
        std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto
set_intersection(Cont1&& cont1, Cont2&& cont2, OutputIterator&& destination)
    -> decltype(auto)
{
    return std::set_intersection(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination));
}

template <typename Cont1,
          typename Cont2,
          typename OutputIterator,
          typename Compare>
inline auto set_intersection(
    Cont1&&          cont1,
    Cont2&&          cont2,
    OutputIterator&& destination,
    Compare&&        comp) -> decltype(auto)
{
    return std::set_intersection(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination),
        std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto
set_difference(Cont1&& cont1, Cont2&& cont2, OutputIterator&& destination)
    -> decltype(auto)
{
    return std::set_difference(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination));
}

template <typename Cont1,
          typename Cont2,
          typename OutputIterator,
          typename Compare>
inline auto set_difference(
    Cont1&&          cont1,
    Cont2&&          cont2,
    OutputIterator&& destination,
    Compare&&        comp) -> decltype(auto)
{
    return std::set_difference(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination),
        std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2, typename OutputIterator>
inline auto set_symmetric_difference(
    Cont1&&          cont1,
    Cont2&&          cont2,
    OutputIterator&& destination) -> decltype(auto)
{
    return std::set_symmetric_difference(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination));
}

template <typename Cont1,
          typename Cont2,
          typename OutputIterator,
          typename Compare>
inline auto set_symmetric_difference(
    Cont1&&          cont1,
    Cont2&&          cont2,
    OutputIterator&& destination,
    Compare&&        comp) -> decltype(auto)
{
    return std::set_symmetric_difference(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<OutputIterator>(destination),
        std::forward<Compare>(comp));
}

template <typename Cont>
inline auto min_element(Cont&& cont) -> decltype(auto)
{
    return std::min_element(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto min_element(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::min_element(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont>
inline auto max_element(Cont&& cont) -> decltype(auto)
{
    return std::max_element(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto max_element(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::max_element(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont>
inline auto minmax_element(Cont&& cont) -> decltype(auto)
{
    return std::minmax_element(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto minmax_element(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::minmax_element(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont1, typename Cont2>
inline auto lexicographical_compare(Cont1&& cont1, Cont2&& cont2)
    -> decltype(auto)
{
    return std::lexicographical_compare(
        std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2));
}

template <typename Cont1, typename Cont2, typename Compare>
inline auto
lexicographical_compare(Cont1&& cont1, Cont2&& cont2, Compare&& comp)
    -> decltype(auto)
{
    return std::lexicographical_compare(
        std::begin(cont1),
        std::end(cont1),
        std::begin(cont2),
        std::end(cont2),
        std::forward<Compare>(comp));
}

template <typename Cont>
inline auto next_permutation(Cont&& cont) -> decltype(auto)
{
    return std::next_permutation(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto next_permutation(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::next_permutation(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont>
inline auto prev_permutation(Cont&& cont) -> decltype(auto)
{
    return std::prev_permutation(std::begin(cont), std::end(cont));
}

template <typename Cont, typename Compare>
inline auto prev_permutation(Cont&& cont, Compare&& comp) -> decltype(auto)
{
    return std::prev_permutation(
        std::begin(cont), std::end(cont), std::forward<Compare>(comp));
}

template <typename Cont, typename Type>
inline auto accumulate(Cont&& cont, Type&& init) -> decltype(auto)
{
    return std::accumulate(
        std::begin(cont), std::end(cont), std::forward<Type>(init));
}

template <typename Cont, typename Type, typename BinaryOperation>
inline auto accumulate(Cont&& cont, Type&& init, BinaryOperation&& binary_op)
    -> decltype(auto)
{
    return std::accumulate(
        std::begin(cont),
        std::end(cont),
        std::forward<Type>(init),
        std::forward<BinaryOperation>(binary_op));
}

template <typename Cont, typename OutputIterator>
inline auto adjacent_difference(Cont&& cont, OutputIterator&& destination)
    -> decltype(auto)
{
    return std::adjacent_difference(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination));
}

template <typename Cont, typename OutputIterator, typename BinaryOperation>
inline auto adjacent_difference(
    Cont&&            cont,
    OutputIterator&&  destination,
    BinaryOperation&& binary_op) -> decltype(auto)
{
    return std::adjacent_difference(
        std::begin(cont),
        std::end(cont),
        std::forward<OutputIterator>(destination),
        std::forward<BinaryOperation>(binary_op));
}

template <typename Cont, typename Type>
inline auto iota(Cont&& cont, Type&& val) -> decltype(auto)
{
    return std::iota(std::begin(cont), std::end(cont), std::forward<Type>(val));
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_RANGED_ALGORITHMS_HPP
