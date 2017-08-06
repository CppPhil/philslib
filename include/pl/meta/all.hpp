/*!
 * \file all_true.hpp
 * \brief Defines the All meta function.
**/
#ifndef INCG_PL_META_ALL_HPP
#define INCG_PL_META_ALL_HPP
#include "bool_pack.hpp" // pl::meta::BoolPack
#include <type_traits> // std::is_same

namespace pl
{
namespace meta
{
/*!
 * \brief Meta function to check if all of the traits in the template parameter are satisfied.
 * \note See: http://en.cppreference.com/w/cpp/types/integral_constant
 *       for documentation of std::true_type and std::false_type.
 * \example template <typename ...Args>
 *          void f(Args ...args)
 *          {
 *              static_assert(
 *                  pl::meta::All<std::is_pod<Args> ...>::value,
 *                  "All elements of the template type parameter pack in function f must be pod."
 *              );
 *          }
 *
 * Is derived from std::true_type if all of the traits are satisfied, otherwise
 * is derived from std::false_type.
**/
template <typename ...Traits>
using All
    = std::is_same<BoolPack<true, Traits::value ...>, BoolPack<Traits::value ..., true>>;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_ALL_HPP
