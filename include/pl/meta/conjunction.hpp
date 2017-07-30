/*!
 * \file conjunction.hpp
 * \brief Exports the conjunction meta function from the C++17 standard library.
**/
#ifndef INCG_PL_META_CONJUNCTION_HPP
#define INCG_PL_META_CONJUNCTION_HPP
#include <type_traits> // std::conditional_t, std::true_type

namespace pl
{
namespace meta
{
/*!
 * \brief Forms the logical conjunction of the type traits 'Traits'
 *        effectively performing a logical 'and' on the sequence of traits.
**/
template <typename ...>
struct conjunction
    : public std::true_type
{
};

/*!
 * \brief Forms the logical conjunction of the type traits 'Traits'
 *        effectively performing a logical 'and' on the sequence of traits.
**/
template <typename Trait1>
struct conjunction<Trait1>
    : public Trait1
{
};

/*!
 * \brief Forms the logical conjunction of the type traits 'Traits'
 *        effectively performing a logical 'and' on the sequence of traits.
**/
template <typename Trait1, typename ...Traits>
struct conjunction<Trait1, Traits ...>
    : public std::conditional_t<bool(Trait1::value), conjunction<Traits ...>, Trait1>
{
};
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_CONJUNCTION_HPP
