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
 * \file ssize.hpp
 * \brief Exports the ssize function that return the size of a container or
 *        C-style array.
**/
#ifndef INCG_PL_CONT_SSIZE_HPP
#define INCG_PL_CONT_SSIZE_HPP
#include "../annotations.hpp" // PL_IN
#include "../type_traits.hpp" // pl::common_type_t, pl::make_signed_t
#include <cstddef>            // std::ptrdiff_t


namespace pl {
namespace cont {
/*
 * \brief Returns the size of a given container as a signed integer.
 * \tparam Container The type of the container to get the size of.
 * \param container The container to get the size of.
 * \return The size of the container given as a signed integer.
**/
template <typename Container>
constexpr auto ssize(PL_IN const Container& container)
    -> common_type_t<std::ptrdiff_t, make_signed_t<decltype(container.size())>>
{
    return static_cast<common_type_t<std::ptrdiff_t, make_signed_t<decltype(container.size())>>>(container.size());
}

/*
 * \brief Returns the size of a given C-style array.
 * \tparam Type The type of the elements in the C-style array.
 * \tparam Size The size of the C-style array.
 * \param array The C-style array to get the size of.
 * \return The size of the C-style array given as a signed integer.
**/
template <typename Type, std::ptrdiff_t Size>
constexpr std::ptrdiff_t ssize(PL_IN const Type (&array)[Size]) noexcept
{
    (void)array;
    return Size;
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_SSIZE_HPP
