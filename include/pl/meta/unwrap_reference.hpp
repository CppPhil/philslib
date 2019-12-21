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
 * \file unwray_reference.hpp
 * \brief Exports the unwrap_reference meta function.
 **/
#ifndef INCG_PL_META_UNWRAP_REFERENCE_HPP
#define INCG_PL_META_UNWRAP_REFERENCE_HPP
#include <functional> // std::reference_wrapper

namespace pl {
namespace meta {
/*!
 * \brief Meta function to unwrap a reference wrapper.
 * \tparam Type The template type parameter
 *
 * If `Type` is a std::reference_wrapper<T> for some type T, provides
 * a member typedef type that names T&; otherwise, provides a member
 * typedef type that names `Type`.
 **/
template<typename Type>
struct unwrap_reference {
    using type = Type;
};

/*!
 * \brief Meta function to unwrap a reference wrapper.
 * \tparam Type The template type parameter
 *
 * If `Type` is a std::reference_wrapper<T> for some type T, provides
 * a member typedef type that names T&; otherwise, provides a member
 * typedef type that names `Type`.
 **/
template<typename Type>
struct unwrap_reference<std::reference_wrapper<Type>> {
    using type = Type&;
};

/*!
 * \brief C++14 style helper type alias for unwrap_reference
 **/
template<typename Type>
using unwrap_reference_t = typename unwrap_reference<Type>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_UNWRAP_REFERENCE_HPP
