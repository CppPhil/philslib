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
 * \file make_array.hpp
 * \brief Exports the make_array function that creates a std::array
 *        from a given template type parameter pack.
 **/
#ifndef INCG_PL_CONT_MAKE_ARRAY_HPP
#define INCG_PL_CONT_MAKE_ARRAY_HPP
#include "../annotations.hpp"               // PL_IN
#include "../meta/conjunction.hpp"          // pl::meta::conjunction
#include "../meta/is_reference_wrapper.hpp" // pl::meta::is_not_reference_wrapper
#include <array>                            // std::array
#include <type_traits>                      // std::common_type
#include <utility>                          // std::forward

namespace pl {
namespace cont {
namespace detail {
/*!
 * \brief Implementation of make_array. Do not use directly.
 **/
template<typename DesiredType, typename...>
struct return_type_helper {
  using type = DesiredType;
};

/*!
 * \brief Implementation of make_array. Do not use directly.
 **/
template<typename... Types>
struct return_type_helper<void, Types...> : public std::common_type<Types...> {
  static_assert(
    ::pl::meta::conjunction<
      ::pl::meta::is_not_reference_wrapper<Types>...>::value,
    "Types cannot contain reference_wrappers when DesiredType is void");
};

/*!
 * \brief Implementation of make_array. Do not use directly.
 **/
template<typename DesiredType, typename... Types>
using return_type = std::array<
  typename return_type_helper<DesiredType, Types...>::type,
  sizeof...(Types)>;
} // namespace detail

/*!
 * \brief Creates a std::array from a template type parameter pack.
 * \param args The arguments to construct the std::array returned from.
 * \return The resulting std::array.
 **/
template<typename DesiredType = void, typename... Args>
constexpr detail::return_type<DesiredType, Args...> make_array(
  PL_IN Args&&... args)
{
  return {{std::forward<Args>(args)...}};
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_MAKE_ARRAY_HPP
