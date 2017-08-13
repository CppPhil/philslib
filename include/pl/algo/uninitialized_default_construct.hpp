/*!
 * \file uninitialized_default_construct.hpp
 * \brief Exports the C++17 uninitialized_default_construct algorithm.
**/
#ifndef INCG_PL_ALGO_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
#define INCG_PL_ALGO_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
#include <new> // ::operator new
#include <iterator> // std::iterator_traits
#include <memory> // std::addressof

namespace pl
{
namespace algo
{
/*!
 * \brief Constructs objects of type
 *        typename iterator_traits<'ForwardIterator'>::value_type in the
 *        uninitialized storage designated by the range ['first', 'last') by
 *        default-initialization.
 * \param first The begin iterator of the range to initialize.
 * \param last The end iterator of the range to initialize.
 * \warning No increment, assignment, comparison, or indirection through valid
 *          instances of 'ForwardIterator' may throw exceptions.
 * \note If an exception is thrown during the initialization,
 *       the function has no effects.
 *       The complexity is linear in the distance between 'first' and 'last'.
**/
template <typename ForwardIterator>
void uninitialized_default_construct(ForwardIterator first, ForwardIterator last)
{
    using value_type = typename std::iterator_traits<ForwardIterator>::value_type;

    ForwardIterator cur{ first };

    try {
        while (cur != last) {
            ::new(static_cast<void *>(std::addressof(*cur))) value_type;
            ++cur;
        }

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
#endif // INCG_PL_ALGO_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
