/*!
 * \file destroy.hpp
 * \brief Exports the C++17 destroy algorithm.
**/
#ifndef INCG_PL_ALGO_DESTROY_HPP
#define INCG_PL_ALGO_DESTROY_HPP
#include "destroy_at.hpp" // pl::algo::destroy_at
#include <memory> // std::addressof

namespace pl
{
namespace algo
{
/*!
 * \brief Destroys the objects in the range ['first', 'last').
 * \param first The begin iterator of the range of elements to destroy.
 * \param last The end iterator of the range of elements to destroy.
 * \warning No increment, assignment, comparison, or indirection through valid
 *          instances of 'ForwardIterator' may throw exceptions.
 * \note The complexity is linear in the distance between 'first' and 'last'.
**/
template <typename ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last)
{
    while (first != last) {
        ::pl::algo::destroy_at(std::addressof(*first));

        ++first;
    }
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_DESTROY_HPP
