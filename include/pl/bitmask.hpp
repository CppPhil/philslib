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
 * \file bitmask.hpp
 * \brief Defines a macro to allow the user to enable bitmask operators for
 *        scoped enum types.
 **/
#ifndef INCG_PL_BITMASK_HPP
#define INCG_PL_BITMASK_HPP
#include "annotations.hpp" // PL_INOUT
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC, PL_COMPILER_VERSION, PL_COMPILER_VERSION_CHECK
#include "type_traits.hpp" // pl::underlying_type_t

/*!
 * \def PL_ENABLE_BITMASK_OPERATORS(scoped_enum)
 * \brief Enables bitmask operators for the scoped enum type passed in.
 * \warning Must appear in the same namespace the scoped enum type passed in
 *          is defined in.
 * \note When using MSVC the operators will only be constexpr functions if the
 *       compiler is new enough to support them.
 * \example namespace user
 *          {
 *              enum class scoped_enum : std::uint8_t
 *              {
 *                  optionA = 0B1U,  // 1
 *                  optionB = 0B10U, // 2
 *                  optionC = 0B100U // 4
 *              };
 *              PL_ENABLE_BITMASK_OPERATORS(scoped_enum)
 *          }
 *
 *          int main()
 *          {
 *              std::cout << std::boolalpha;
 *
 *              // enm is A and B toggled on
 *              auto enm = user::scoped_enum::optionA
 *                         | user::scoped_enum::optionB;
 *              enm &= ~user::scoped_enum::optionA; // toggle A off
 *              std::cout << (enm == user::scoped_enum::optionB)
 *                        << std::endl;
 *          }
 **/

#if (PL_COMPILER != PL_COMPILER_MSVC) \
  || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
#define PL_ENABLE_BITMASK_OPERATORS(scoped_enum)                                 \
  constexpr scoped_enum operator|(scoped_enum lhs, scoped_enum rhs)              \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    return static_cast<scoped_enum>(                                             \
      static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));              \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum operator&(scoped_enum lhs, scoped_enum rhs)              \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    return static_cast<scoped_enum>(                                             \
      static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs));              \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum operator^(scoped_enum lhs, scoped_enum rhs)              \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    return static_cast<scoped_enum>(                                             \
      static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs));              \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum operator~(scoped_enum lhs)                               \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    return static_cast<scoped_enum>(~static_cast<Underlying>(lhs));              \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum& operator|=(                                             \
    PL_INOUT scoped_enum& lhs, scoped_enum rhs)                                  \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    lhs              = static_cast<scoped_enum>(                                 \
      static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs)); \
    return lhs;                                                                  \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum& operator&=(                                             \
    PL_INOUT scoped_enum& lhs, scoped_enum rhs)                                  \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    lhs              = static_cast<scoped_enum>(                                 \
      static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs)); \
    return lhs;                                                                  \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum& operator^=(                                             \
    PL_INOUT scoped_enum& lhs, scoped_enum rhs)                                  \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    lhs              = static_cast<scoped_enum>(                                 \
      static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs)); \
    return lhs;                                                                  \
  }
#else
#define PL_ENABLE_BITMASK_OPERATORS(scoped_enum)                                 \
  constexpr scoped_enum operator|(scoped_enum lhs, scoped_enum rhs)              \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    return static_cast<scoped_enum>(                                             \
      static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));              \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum operator&(scoped_enum lhs, scoped_enum rhs)              \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    return static_cast<scoped_enum>(                                             \
      static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs));              \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum operator^(scoped_enum lhs, scoped_enum rhs)              \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    return static_cast<scoped_enum>(                                             \
      static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs));              \
  }                                                                              \
                                                                                 \
  constexpr scoped_enum operator~(scoped_enum lhs)                               \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    return static_cast<scoped_enum>(~static_cast<Underlying>(lhs));              \
  }                                                                              \
                                                                                 \
  inline scoped_enum& operator|=(PL_INOUT scoped_enum& lhs, scoped_enum rhs)     \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    lhs              = static_cast<scoped_enum>(                                 \
      static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs)); \
    return lhs;                                                                  \
  }                                                                              \
                                                                                 \
  inline scoped_enum& operator&=(PL_INOUT scoped_enum& lhs, scoped_enum rhs)     \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    lhs              = static_cast<scoped_enum>(                                 \
      static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs)); \
    return lhs;                                                                  \
  }                                                                              \
                                                                                 \
  inline scoped_enum& operator^=(PL_INOUT scoped_enum& lhs, scoped_enum rhs)     \
  {                                                                              \
    using Underlying = ::pl::underlying_type_t<scoped_enum>;                     \
    lhs              = static_cast<scoped_enum>(                                 \
      static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs)); \
    return lhs;                                                                  \
  }
#endif
#endif // INCG_PL_BITMASK_HPP
