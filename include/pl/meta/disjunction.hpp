/*!
 * \file disjunction.hpp
 * \brief Exports the disjunction C++17 meta function.
**/
#ifndef INCG_PL_META_DISJUNCTION_HPP
#define INCG_PL_META_DISJUNCTION_HPP
#include <type_traits> // std::false_type, std::conditional_t

namespace pl
{
namespace meta
{
/*!
 * \brief Forms the logical disjunction of the type traits 'Traits',
 *        effectively performing a logical 'or' on the sequence of traits.
**/
template <typename ...>
struct disjunction
    : public std::false_type
{
};

/*!
 * \brief Forms the logical disjunction of the type traits 'Traits',
 *        effectively performing a logical 'or' on the sequence of traits.
**/
template <typename Trait1>
struct disjunction<Trait1>
    : public Trait1
{
};

/*!
 * \brief Forms the logical disjunction of the type traits 'Traits',
 *        effectively performing a logical 'or' on the sequence of traits.
**/
template <typename Trait1, typename ...Traits>
struct disjunction<Trait1, Traits ...>
    : public std::conditional_t<bool(Trait1::value), Trait1, disjunction<Traits ...>>
{
};
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_DISJUNCTION_HPP
