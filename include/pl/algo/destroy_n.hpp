/*!
 * \file destroy_n.hpp
 * \brief Exports the C++17 destroy_n algorithm.
**/
#ifndef INCG_PL_ALGO_DESTROY_N_HPP
#define INCG_PL_ALGO_DESTROY_N_HPP
#include "destroy_at.hpp" // pl::algo::destroy_at
#include <memory> // std::addressof

namespace pl
{
namespace algo
{
/*!
 * \brief Destroys the 'n' objects in the range starting at 'first'.
 * \param first The beginning of the range of elements to destroy.
 * \param n The number of elements to destroy. May not be larger than the
 *          amount of elements that the range beginning with 'first' holds.
 * \return The end of the range of objects that has been
 *         destroyed (i.e., std::next('first', 'n')).
 * \warning No increment, assignment, comparison, or indirection through valid
 *          instances of 'ForwardIterator' may throw exceptions.
 * \note The complexity is linear in 'n'.
**/
template <typename ForwardIterator, typename SizeType>
ForwardIterator destroy_n(ForwardIterator first, SizeType n)
{
    while (n > 0) {
        ::pl::algo::destroy_at(std::addressof(*first));

        ++first;
        --n;
    }
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_DESTROY_N_HPP
