/*!
 * \file none.hpp
 * \brief Exports the None meta function.
**/
#ifndef INCG_PL_META_NONE_HPP
#define INCG_PL_META_NONE_HPP
#include "bool_constant.hpp" // pl::meta::bool_constant
#include "disjunction.hpp" // pl::meta::disjunction
#include <ciso646> // not

namespace pl
{
namespace meta
{
/*!
 * \brief Will behave like std::true_type if none of the traits passed in
 *        are satisfied. Otherwise will behave like std::false_type.
**/
template <typename ...Traits>
using None = bool_constant<not disjunction<Traits ...>::value>;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_NONE_HPP
