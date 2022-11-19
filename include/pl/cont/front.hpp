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
 * \file front.hpp
 * \brief Exports the front function that returns the first (index 0)
 *        element of container, a C-style array or an initializer_list.
 **/
#ifndef INCG_PL_CONT_FRONT_HPP
#define INCG_PL_CONT_FRONT_HPP
#include "../annotations.hpp" // PL_IN
#include "../assert.hpp"      // PL_DBG_CHECK_PRE
#include <ciso646>            // not
#include <cstddef>            // std::size_t
#include <initializer_list>   // std::initializer_list

namespace pl {
namespace cont {
/*!
 * \brief Gets the first (index 0) element of a container.
 * \param cont The container to get the first (index 0) element of.
 * \return The first (index 0) element of the container.
 * \warning Undefined behavior occurs if the container passed in is empty.
 **/
template<typename Cont>
constexpr auto front(PL_IN Cont& cont) -> decltype(auto)
{
  PL_DBG_CHECK_PRE(not cont.empty());

  return cont.front();
}

/*!
 * \brief Gets the first (index 0) element of a C-Array.
 * \param arr The C-Array to get the first (index 0) element of.
 * \return The first (index 0) element of the C-Array.
 **/
template<typename Type, std::size_t Size>
constexpr auto front(PL_IN Type (&arr)[Size]) noexcept -> decltype(auto)
{
  return arr[static_cast<std::size_t>(0U)];
}

/*!
 * \brief Gets the first (index 0) element of an initializer_list.
 * \param init_list The initializer_list to get the first (index 0) element of.
 * \return The first (index 0) element of the initializer_list.
 * \warning Undefined behavior occurs if the initializer_list passed in is
 *          empty.
 **/
template<typename Ty>
constexpr auto front(std::initializer_list<Ty> init_list) noexcept
  -> decltype(auto)
{
  return *(init_list.begin());
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_FRONT_HPP
