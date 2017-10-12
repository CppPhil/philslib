/*!
 * \file apply.hpp
 * \brief Exports the apply function template.
**/
#ifndef INCG_PL_APPLY_HPP
#define INCG_PL_APPLY_HPP
#include "annotations.hpp" // PL_IN
#include "invoke.hpp" // pl::invoke
#include <cstddef> // std::size_t
#include <utility> // std::index_sequence, std::make_index_sequence, std::forward
#include <tuple> // std::get, std::tuple_size
#include <type_traits> // std::decay_t

namespace pl
{
namespace detail
{
/*!
 * \brief Implementation function of apply; not to be used directly!
**/
template <typename Callable, typename TupleLike, std::size_t ...Indices>
constexpr auto applyImpl(
    PL_IN Callable &&callable,
    PL_IN TupleLike &&tupleLike,
    std::index_sequence<Indices ...>) -> decltype(auto)
{
    return ::pl::invoke(
        std::forward<Callable>(callable),
        std::get<Indices>(std::forward<TupleLike>(tupleLike)) ...);
}
} // namespace detail

/*!
 * \brief Invokes the callable object 'callable' with a tuple of arguments.
 * \param callable The callable object to be invoked.
 * \param tupleLike The tuple whose elements to be used as arguments to 'callable'
 * \return The result that was returned by 'callable'.
 * \note The 'tupleLike' need not be std::tuple, and instead may be anything
 *       that supports std::get and std::tuple_size; in particular,
 *       std::array and std::pair may be used.
**/
template <typename Callable, typename TupleLike>
constexpr auto apply(
    PL_IN Callable &&callable,
    PL_IN TupleLike &&tupleLike) -> decltype(auto)
{
    return detail::applyImpl(
        std::forward<Callable>(callable),
        std::forward<TupleLike>(tupleLike),
        std::make_index_sequence<std::tuple_size<std::decay_t<TupleLike>>::value>{ });
}
} // namespace pl
#endif // INCG_PL_APPLY_HPP
