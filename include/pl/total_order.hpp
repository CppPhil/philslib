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
 * \file total_order.hpp
 * \brief Exports macros to define a total order for a type.
 **/
#ifndef INCG_PL_TOTAL_ORDER_HPP
#define INCG_PL_TOTAL_ORDER_HPP
#include "annotations.hpp" // PL_NODISCARD

/*!
 * \def PL_TOTAL_ORDER
 * \brief Defines a total order for type by defining the corresponding operators
 * \warning There must be a correct operator< and operator== already defined for
 *          type.
 **/
#define PL_TOTAL_ORDER(type)                                            \
                                                                        \
  PL_NODISCARD inline bool operator!=(const type& lhs, const type& rhs) \
  {                                                                     \
    return not static_cast<bool>(lhs == rhs);                           \
  }                                                                     \
                                                                        \
  PL_NODISCARD inline bool operator>(const type& lhs, const type& rhs)  \
  {                                                                     \
    return rhs < lhs;                                                   \
  }                                                                     \
                                                                        \
  PL_NODISCARD inline bool operator<=(const type& lhs, const type& rhs) \
  {                                                                     \
    return not static_cast<bool>(lhs > rhs);                            \
  }                                                                     \
                                                                        \
  PL_NODISCARD inline bool operator>=(const type& lhs, const type& rhs) \
  {                                                                     \
    return not static_cast<bool>(lhs < rhs);                            \
  }

/*!
 * \def PL_TOTAL_ORDER_CONSTEXPR
 * \brief Defines a total order for type by defining the corresponding operators
 *        The operators are declared as constexpr
 * \warning There must be a correct operator< and operator== already defined for
 *          type. Additionally those operators must be declared constexpr.
 **/
#define PL_TOTAL_ORDER_CONSTEXPR(type)                                     \
                                                                           \
  PL_NODISCARD constexpr bool operator!=(const type& lhs, const type& rhs) \
  {                                                                        \
    return not static_cast<bool>(lhs == rhs);                              \
  }                                                                        \
                                                                           \
  PL_NODISCARD constexpr bool operator>(const type& lhs, const type& rhs)  \
  {                                                                        \
    return rhs < lhs;                                                      \
  }                                                                        \
                                                                           \
  PL_NODISCARD constexpr bool operator<=(const type& lhs, const type& rhs) \
  {                                                                        \
    return not static_cast<bool>(lhs > rhs);                               \
  }                                                                        \
                                                                           \
  PL_NODISCARD constexpr bool operator>=(const type& lhs, const type& rhs) \
  {                                                                        \
    return not static_cast<bool>(lhs < rhs);                               \
  }
#endif // INCG_PL_TOTAL_ORDER_HPP
