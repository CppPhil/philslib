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
 * \file at.hpp
 * \brief Exports a bounds checked index based interface for accessing
 *        containers, C-Arrays and std::initializer_lists.
**/
#ifndef INCG_PL_CONT_AT_HPP
#define INCG_PL_CONT_AT_HPP
#include "../annotations.hpp" // PL_IN
#include <ciso646> // not
#include <cstddef> // std::size_t
#include <stdexcept> // std::out_of_range
#include <initializer_list> // std::initializer_list

namespace pl
{
namespace cont
{
/*!
 * \brief Retrieves a reference to the element at position 'index' in the
 *        C-Array 'arr'.
 * \param arr The C-Array to access.
 * \param index The index of the element in 'arr' to get a reference to.
 * \return A reference to the element at position 'index' in 'arr'.
 * \throws std::out_of_range if 'index' is out of bounds.
**/
template <typename Ty, std::size_t Size>
inline constexpr Ty &at(PL_IN Ty (&arr)[Size], const std::size_t index)
{
    if (not (index < Size)) {
        throw std::out_of_range{
            "index was out of bounds in pl::cont::at (C-Array)"
        };
    }

    return arr[index];
}

/*!
 * \brief Retrieves a reference to the element at position 'index' in the
 *        container 'container'.
 * \param container The container to access.
 * \param index The index of the element in 'container' to get a reference to.
 * \return A reference to the element at position 'index' in 'container'.
 * \throws std::out_of_range if 'index' is out of bounds.
**/
template <typename Container>
inline constexpr auto at(PL_IN Container &container, const std::size_t index)
    -> decltype(container[container.size()])
{
    if (not (index < container.size())) {
        throw std::out_of_range{
            "index was out of bounds in pl::cont::at (container)"
        };
    }

    return container[index];
}

/*!
 * \brief Retrieves a copy of the element at position 'index' in the
 *        std::initializer_list 'il'.
 * \param il The initializer_list to access.
 * \param index The index of the element to get a copy of.
 * \return A copy of the element at position 'index'.
 * \throws std::out_of_range if 'index' is out of bounds.
**/
template <typename Ty>
inline constexpr Ty at(std::initializer_list<Ty> il, const std::size_t index)
{
    if (not (index < il.size())) {
        throw std::out_of_range{
            "index was out of bounds in pl::cont::at (initializer_list)"
        };
    }

    return *(il.begin() + index);
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_AT_HPP
