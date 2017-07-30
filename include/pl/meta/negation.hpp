/*!
 * \file negation.hpp
 * \brief Exports the negation C++17 meta function.
**/
#ifndef INCG_PL_META_NEGATION_HPP
#define INCG_PL_META_NEGATION_HPP
#include <type_traits> // std::integral_constant
#include <ciso646> // not

namespace pl
{
namespace meta
{
/*!
 * \brief Forms the logical negation of the type trait 'Trait'.
**/
template <typename Trait>
struct negation
    : public std::integral_constant<bool, not bool(Trait::value)>
{
};
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_NEGATION_HPP
