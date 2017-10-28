/*!
 * \file for_each_n.hpp
 * \brief Exports the C++17 for_each_n algorithm.
**/
#ifndef INCG_PL_ALGO_FOR_EACH_N_HPP
#define INCG_PL_ALGO_FOR_EACH_N_HPP
#include "../invoke.hpp" // pl::invoke

namespace pl
{
namespace algo
{
/*!
 * \brief Applies the given Invocable 'unaryInvocable' to the result of
 *        dereferencing every iterator in the range ['first', 'first' + 'n'),
 *        in order.
 * \param first the beginning of the range to apply the UnaryInvocable to
 * \param n the number of elements to apply the UnaryInvocable to
 * \param unaryInvocable function object, to be applied to the result of
 *                       dereferencing every iterator in the
 *                       range ['first', 'first' + 'n').
 *                       The signature of the function should be equivalent
 *                       to the following:
 *                       void fun(const Type &a);
 *                       The signature does not need to have const &.
 *                       The type Type must be such that an object of type
 *                       InputIterator can be dereferenced and then implicitly
 *                       converted to Type.
 * \note If the iterator type is mutable, 'unaryInvocable' may modify the
 *       elements of the range through the dereferenced iterator.
 *       If 'unaryInvocable' returns a result, the result is ignored.
 * \warning If 'n' is less than zero, the behavior is undefined.
 *          If 'first' + 'n' is beyond the end iterator of the range,
 *          the behavior is undefined.
 * \return 'first' + 'n'
**/
template <typename InputIterator, typename SizeType, typename UnaryInvocable>
InputIterator for_each_n(
    InputIterator first,
    SizeType n,
    UnaryInvocable unaryInvocable)
{
    for (SizeType i{ }; i < n; ++first) {
        ::pl::invoke(unaryInvocable, *first);
        ++i;
    }

    return first;
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_FOR_EACH_N_HPP
