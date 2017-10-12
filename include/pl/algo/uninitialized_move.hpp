/*!
 * \file uninitialized_move.hpp
 * \brief Exports the C++17 uninitialized_move algorithm.
**/
#ifndef INCG_PL_ALGO_UNINITIALIZED_MOVE_HPP
#define INCG_PL_ALGO_UNINITIALIZED_MOVE_HPP
#include <new> // ::operator new
#include <utility> // std::move
#include <iterator> // std::iterator_traits
#include <memory> // std::addressof

namespace pl
{
namespace algo
{
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
template <typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_move(
    InputIterator first,
    InputIterator last,
    ForwardIterator dest)
{
    using value_type = typename std::iterator_traits<ForwardIterator>::value_type;

    ForwardIterator cur{ dest };

    try {
        while (first != last) {
            ::new(static_cast<void *>(std::addressof(*cur))) value_type(std::move(*first));

            ++first;
            ++cur;
        }

        return cur;
    } catch (...) {
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
