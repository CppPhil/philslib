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
 * \file empty.hpp
 * \brief Exports the non-member empty function from C++17.
**/
#ifndef INCG_PL_CONT_EMPTY_HPP
#define INCG_PL_CONT_EMPTY_HPP
#include "../annotations.hpp" // PL_IN, PL_NODISCARD
#include <cstddef>            // std::size_t
#include <initializer_list>   // std::initializer_list

namespace pl {
namespace cont {
/*!
 * \brief Returns whether the given 'container' is empty.
 * \param container A container with an empty member function.
 * \return container.empty()
 * \note The return value will be true if the container doesn't have
 *       any element, otherwise it will be false.
**/
template <typename Container>
PL_NODISCARD constexpr auto empty(PL_IN const Container& container)
    -> decltype(container.empty())
{
    return container.empty();
}

/*!
 * \brief Returns whether the given 'container' is empty.
 * \param array A C-Array of arbitrary type.
 * \return false
 * \note The return value will be true if the C-Array doesn't have
 *       any element, otherwise it will be false.
**/
template <typename Ty, std::size_t Size>
PL_NODISCARD constexpr bool empty(PL_IN const Ty (&array)[Size]) noexcept
{
    (void)array;
    return false;
}

/*!
 * \brief Returns whether the given 'container' is empty.
 * \param il An initializer list.
 * \return il.size() == 0U
 * \note The return value will be true if the std::initializer_list doesn't have
 *       any element, otherwise it will be false.
**/
template <typename Ty>
PL_NODISCARD constexpr bool empty(std::initializer_list<Ty> il) noexcept
{
    return il.size() == 0U;
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_EMPTY_HPP
