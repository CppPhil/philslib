/*!
 * \file is_reference_wrapper.hpp
 * \brief Exports the is_reference_wrapper meta function to checke whether
 *        or not a type is a std::reference_wrapper type.
**/
#ifndef INCG_PL_META_IS_REFERENCE_WRAPPER_HPP
#define INCG_PL_META_IS_REFERENCE_WRAPPER_HPP
#include <functional> // std::reference_wrapper
#include <type_traits> // std::false_type, std::true_type

namespace pl
{
namespace meta
{
/*!
 * \brief Detects whether Ty is a std::reference_wrapper type.
 * \note This is the false case.
 *
 * Detects whether Ty is a std::reference_wrapper type.
 * Is derived from std::false_type.
**/
template <typename Ty>
struct is_reference_wrapper
    : public std::false_type
{
};

/*!
 * \brief Detects whether Ty is a std::reference_wrapper type.
 * \note This is the true case.
 *
 * Detects whether Ty is a std::reference_wrapper type.
 * Is derived from std::true_type.
**/
template <typename Type>
struct is_reference_wrapper<std::reference_wrapper<Type>>
    : public std::true_type
{
};
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_IS_REFERENCE_WRAPPER_HPP
