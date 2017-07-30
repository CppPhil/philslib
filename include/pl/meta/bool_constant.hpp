/*!
 * \file bool_constant.hpp
 * \brief Exports the bool_constant helper alias template that is defined
 *        in the C++17 C++ standard library.
**/
#ifndef INCG_PL_META_BOOL_CONSTANT_HPP
#define INCG_PL_META_BOOL_CONSTANT_HPP
#include <type_traits> // std::integral_constant

namespace pl
{
namespace meta
{
/*!
 * \brief The C++17 bool_constant alias template.
 *
 * The helper alias template defined for the common case
 * where the first template parameter of std::integral_constant is bool.
**/
template <bool BooleanValue>
using bool_constant = std::integral_constant<bool, BooleanValue>;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_BOOL_CONSTANT_HPP
