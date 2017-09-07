/*!
 * \file uncvref.hpp
 * \brief Exports the uncvref meta function.
**/
#ifndef INCG_PL_META_UNCVREF_HPP
#define INCG_PL_META_UNCVREF_HPP
#include <type_traits> // std::remove_cv, std::remove_reference_t

namespace pl
{
namespace meta
{
/*!
 * \brief Meta function to get the unqualified type of a type.
 *
 * The nested type type will have its reference type modifiers removed
 * and will have its const and volatile type qualifiers removed.
**/
template <typename Type>
struct uncvref
    : public std::remove_cv<std::remove_reference_t<Type>>
{
};

/*!
 * \brief C++14 style meta function helper that is an alias of the nested type
 *        type of pl::uncvref. Reduces the necessity of the typename keyword
 *        in application code.
**/
template <typename Type>
using uncvref_t = typename uncvref<Type>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_UNCVREF_HPP
