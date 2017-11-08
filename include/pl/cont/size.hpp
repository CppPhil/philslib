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
 * \file size.hpp
 * \brief Exports the size function that return the size of a container or
 *        C-style array.
**/
#ifndef INCG_PL_CONT_SIZE_HPP
#define INCG_PL_CONT_SIZE_HPP
#include "../annotations.hpp" // PL_IN
#include <cstddef> // std::size_t

namespace pl
{
namespace cont
{
/*!
 * \brief Gets the size of a container, which is the amount of elements
 *        currently stored in that container.
 * \param cont The container to get the size of.
 * \return The size of the container passed into the parameter.
**/
template <typename Cont>
constexpr auto size(PL_IN const Cont &cont) -> decltype(cont.size())
{
    return cont.size();
}

/*!
 * \brief Gets the size of a C-Array.
 * \param arr The C-Array to get the size of.
 * \return The size of the C-Array passed into the parameter is returned.
**/
template <typename Type, std::size_t Size>
constexpr std::size_t size(PL_IN const Type (&arr)[Size]) noexcept
{
    (void)arr;
    return Size;
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_SIZE_HPP
