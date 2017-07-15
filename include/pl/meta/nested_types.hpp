/*!
 * \file nested_types.hpp
 * \brief Exports meta functions to fetch commonly defined nested types.
**/
#ifndef INCG_PL_META_NESTED_TYPES_HPP
#define INCG_PL_META_NESTED_TYPES_HPP

namespace pl
{
namespace meta
{
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

/*!
 * \brief Alias of the nested type container_type of Type.
**/
template <typename Type>
using container_type = typename Type::container_type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_NESTED_TYPES_HPP
