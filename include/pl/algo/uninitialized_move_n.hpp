/*!
 * \file uninitialized_move_n.hpp
 * \brief Exports the C++17 uninitialized_move_n algorithm.
**/
#ifndef INCG_PL_ALGO_UNINITIALIZED_MOVE_N_HPP
#define INCG_PL_ALGO_UNINITIALIZED_MOVE_N_HPP
#include <new> // ::operator new
#include <utility> // std::pair, std::make_pair, std::move
#include <iterator> // std::iterator_traits
#include <memory> // std::addressof

namespace pl
{
namespace algo
{
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
template <typename InputIterator, typename SizeType, typename ForwardIterator>
std::pair<InputIterator, ForwardIterator> uninitialized_move_n(
    InputIterator first,
    SizeType count,
    ForwardIterator dest)
{
    using value_type = typename std::iterator_traits<ForwardIterator>::value_type;

    ForwardIterator cur{ dest };

    try {
        while (count > 0) {
            ::new(static_cast<void *>(std::addressof(*cur))) value_type(std::move(*first));

            ++first;
            ++cur;
            --count;
        }

    } catch (...) {
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
