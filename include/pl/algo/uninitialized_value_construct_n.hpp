/*!
 * \file uninitialized_value_construct_n.hpp
 * \brief Exports the C++17 uninitialized_value_construct_n algorithm.
**/
#ifndef INCG_PL_ALGO_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
#define INCG_PL_ALGO_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
#include <new> // ::operator new
#include <iterator> // std::iterator_traits
#include <memory> // std::addressof

namespace pl
{
namespace algo
{
/*!
 * \brief Constructs 'n' objects of type
 *        typename iterator_traits<'ForwardIterator'>::value_type
 *        in the uninitialized storage starting at first by value-initialization.
 * \param first The beginning of the range of elements to initialize.
 * \param n The number of elements to initialize. May not be larger than
 *          the amount of elements the range beginning with 'first' can hold!
 * \return The end of the range of objects (i.e., std::next('first', n)).
 * \warning No increment, assignment, comparison, or indirection through valid
 *          instances of 'ForwardIterator' may throw exceptions.
 * \note If an exception is thrown during the initialization,
 *       the function has no effects.
 *       The complexity is linear in 'n'.
**/
template <typename ForwardIterator, typename SizeType>
ForwardIterator uninitialized_value_construct_n(
    ForwardIterator first,
    SizeType n)
{
    using value_type = typename std::iterator_traits<ForwardIterator>::value_type;

    ForwardIterator cur{ first };

    try {
        while (n > 0) {
            ::new(static_cast<void *>(std::addressof(*cur))) value_type();

            ++cur;
            --n;
        }

        return cur;
    } catch (...) {
        while (first != cur) {
            first->~value_type();
            ++first;
        }

        throw;
    }
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
