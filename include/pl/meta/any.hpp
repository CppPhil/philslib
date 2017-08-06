/*!
 * \file any.hpp
 * \brief Defines the Any meta function.
**/
#ifndef INCG_PL_META_ANY_HPP
#define INCG_PL_META_ANY_HPP
#include <type_traits> // std::false_type, std::true_type std::conditional_t

namespace pl
{
namespace meta
{
namespace detail
{
/*!
 * \brief Implementation of Any. Not to be used directly.
**/
template <typename ...Traits>
struct AnyImpl
    : public std::false_type
{
};

/*!
 * \brief Implementation of Any. Not to be used directly.
**/
template <typename Trait1, typename ...Traits>
struct AnyImpl<Trait1, Traits ...>
    : public std::conditional_t<Trait1::value,
                                std::true_type,
                                AnyImpl<Traits ...>>
{
};
} // namespace detail

/*!
 * \brief Will behave like std::true_type if any of the traits passed in
 *        are satisfied, that is their value non-static data member evaluates to
 *        true. Otherwise will behave like std::false_type.
 * \example template <typename ...Args>
 * void f(Args ...args)
 * {
 *     static_assert(pl::meta::Any<std::is_pod<Args> ...>::value,
 *                   "At least one element of the template type parameter pack in function f must be pod."
 *     );
 * }
**/
template <typename ...Traits>
using Any = typename detail::AnyImpl<Traits ...>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_ANY_HPP
