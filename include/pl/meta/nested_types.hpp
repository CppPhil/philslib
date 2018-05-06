/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

/*!
 * \file nested_types.hpp
 * \brief Exports meta functions to fetch commonly defined nested types.
**/
#ifndef INCG_PL_META_NESTED_TYPES_HPP
#define INCG_PL_META_NESTED_TYPES_HPP

namespace pl {
namespace meta {
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
