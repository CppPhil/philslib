/*!
 * \file metafunctions.hpp
 * \brief Defines various meta functions.
**/
#ifndef INCG_PL_METAFUNCTIONS_HPP
#define INCG_PL_METAFUNCTIONS_HPP
#include <type_traits> // std::is_same
namespace pl
{
namespace detail
{
/*!
 * \brief Type of an arbitrary amount of compile time booleans.
**/
template <bool ...>
struct BoolPack;
} // namespace detail

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
    = std::is_same<detail::BoolPack<true, Values ...>, detail::BoolPack<Values ..., true>>;

/*!
 * \brief Alias of the nested type value_type of Type.
**/
template <typename Type>
using value_type = typename Type::value_type;

/*!
 * \brief Alias of the nested type allocator_type of Type.
**/
template <typename Type>
using allocator_type = typename Type::allocator_type;

/*!
 * \brief Alias of the nested type difference_type of Type.
**/
template <typename Type>
using difference_type = typename Type::difference_type;

/*!
 * \brief Alias of the nested type size_type of Type.
**/
template <typename Type>
using size_type = typename Type::size_type;

/*!
 * \brief Alias of the nested type key_type of Type.
**/
template <typename Type>
using key_type = typename Type::key_type;

/*!
 * \brief Alias of the nested type mapped_type of Type.
**/
template <typename Type>
using mapped_type = typename Type::mapped_type;

/*!
 * \brief Alias of the nested type element_type of Type.
**/
template <typename Type>
using element_type = typename Type::element_type;

/*!
 * \brief Alias of the nested type deleter_type of Type.
**/
template <typename Type>
using deleter_type = typename Type::deleter_type;
} // namespace pl
#endif // INCG_PL_METAFUNCTIONS_HPP
