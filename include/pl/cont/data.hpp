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
 * \file data.hpp
 * \brief Exports the C++17 data function.
**/
#ifndef INCG_PL_CONT_DATA_HPP
#define INCG_PL_CONT_DATA_HPP
#include "../annotations.hpp" // PL_IN
#include <cstddef> // std::size_t
#include <initializer_list> // std::initializer_list

namespace pl
{
namespace cont
{
/*!
 * \brief Returns a pointer to the block of memory containing the elements of
 *        the container.
 * \param container The container to call .data() on.
 * \return A pointer to the block of memory containing the elements of
 *         the container.
 * \warning Do not dereference the pointer returned if 'container' is empty.
**/
template <typename Container>
constexpr auto data(PL_IN Container &container) -> decltype(container.data())
{
    return container.data();
}

/*!
 * \brief Returns a pointer to the block of memory containing the elements
 *        of the container.
 * \param container The container to call .data() on.
 * \return A pointer to the block of memory containing the elements
 *         of the container.
 * \warning Do not dereference the pointer returned if 'container' is empty.
 * \note This is the const overload.
**/
template <typename Container>
constexpr auto data(PL_IN const Container &container) -> decltype(container.data())
{
    return container.data();
}

/*!
 * \brief Returns a pointer to the block of memory containing the elements
 *        the C-Style array.
 * \param array The C-Style array for which to get the pointer resulting from
 *              array to pointer decay.
 * \return A pointer to the block of memory containing the elements of the
 *         C-Style array.
**/
template <typename Ty, std::size_t Size>
constexpr Ty *data(PL_IN Ty (&array)[Size]) noexcept
{
    return array;
}

/*!
 * \brief Returns a pointer to the block of memory containing the elements
 *        the std::initializer_list.
 * \param initList The initializer_list to get the pointer for.
 * \return A pointer to the block of memory containing the elements of the
 *         std::initializer_list.
**/
template <typename Ty>
constexpr const Ty *data(std::initializer_list<Ty> initList) noexcept
{
    return initList.begin();
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_DATA_HPP
