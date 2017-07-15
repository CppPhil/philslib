/*!
 * \file all_true.hpp
 * \brief Defines the AllTrue meta function.
**/
#ifndef INCG_PL_ALL_TRUE_HPP
#define INCG_PL_ALL_TRUE_HPP
#include "bool_pack.hpp" // pl::meta::BoolPack
#include <type_traits> // std::is_same

namespace pl
{
namespace meta
{
/*!
 * \brief Meta function to check if all of the booleans in the template parameter pack are true.
 * \note See: http://en.cppreference.com/w/cpp/types/integral_constant
 *       for documentation of std::true_type and std::false_type.
 * \example template <typename ...Args>
 *          void f(Args ...args)
 *          {
 *              static_assert(
 *                  pl::AllTrue<std::is_pod<Args>::value ...>::value,
 *                  "All elements of the template type parameter pack in function f must be pod."
 *              );
 *          }
 *
 * Is derived from std::true_type if all of the booleans are true, otherwise
 * is derived from std::false_type.
**/
template <bool ...Values>
using AllTrue
    = std::is_same<BoolPack<true, Values ...>, BoolPack<Values ..., true>>;
} // namespace meta
} // namespace pl
#endif // INCG_PL_ALL_TRUE_HPP
