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
 * \file to_array.hpp
 * \brief Exports the to_array function.
 **/
#ifndef INCG_PL_CONT_TO_ARRAY_HPP
#define INCG_PL_CONT_TO_ARRAY_HPP
#include "../annotations.hpp" // PL_IN, PL_INOUT
#include "../type_traits.hpp" // pl::remove_cv_t
#include <array>              // std::array
#include <cstddef>            // std::size_t
#include <utility>            // std::index_sequence, std::move

namespace pl {
namespace cont {
namespace detail {
/*!
 * \brief Implementation function of to_array, not to be used directly.
 **/
template<typename Ty, std::size_t Size, std::size_t... Indices>
constexpr std::array<remove_cv_t<Ty>, Size> to_array_impl(
    PL_IN Ty (&array)[Size],
    std::index_sequence<Indices...>)
{
    return {{array[Indices]...}};
}

/*!
 * \brief Implementation function of to_array, not to be used directly.
 **/
template<typename Ty, std::size_t Size, std::size_t... Indices>
constexpr std::array<remove_cv_t<Ty>, Size> to_array_impl(
    PL_INOUT Ty(&&array)[Size],
    std::index_sequence<Indices...>)

{
    return {{std::move(array[Indices])...}};
}
} // namespace detail

/*!
 * \brief Creates a std::array from a built-in array.
 * \param array The built-in array to be used to initialize the std::array.
 * \return A std::array object whose elements are copy-initialized from
 *         the corresponding element of 'array'.
 *
 * Creates a std::array from the built-in array 'array'.
 * The elements of the std::array are copy-initialized from the
 * corresponding element of 'array'.
 **/
template<typename Ty, std::size_t Size>
constexpr std::array<remove_cv_t<Ty>, Size> to_array(PL_IN Ty (&array)[Size])
{
    return ::pl::cont::detail::to_array_impl(
        array, std::make_index_sequence<Size>{});
}

/*!
 * \brief Creates a std::array from a built-in array.
 * \param array The built-in array to be used to initialize the std::array.
 * \return A std::array object whose elements are move-initialized from
 *         the corresponding element of 'array'.
 *
 * Creates a std::array from the built-in array 'array'.
 * The elements of the std::array are move-initialized from the
 * corresponding element of 'array'.
 **/
template<typename Ty, std::size_t Size>
constexpr std::array<remove_cv_t<Ty>, Size> to_array(PL_INOUT Ty(&&array)[Size])
{
    return ::pl::cont::detail::to_array_impl(
        std::move(array), std::make_index_sequence<Size>{});
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_TO_ARRAY_HPP
