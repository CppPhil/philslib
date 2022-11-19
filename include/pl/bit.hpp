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
 * \file bit.hpp
 * \brief This header defines various functions for bitwise operations.
 **/
#ifndef INCG_PL_BIT_HPP
#define INCG_PL_BIT_HPP
#include "annotations.hpp" // PL_INOUT, PL_IN
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC, PL_COMPILER_VERSION, PL_COMPILER_VERSION_CHECK
#include "type_traits.hpp" // pl::remove_const_t
#include <cstring>         // std::memcpy
#include <memory>          // std::addressof
#include <type_traits> // std::is_unsigned, std::is_trivially_copyable, std::is_trivial

namespace pl {
/*!
 * \brief Sets the bit at position bit of numeric.
 * \param numeric The number to have its bit bit set.
 * \param bit The bit to set in numeric. [0..bits(Numeric))
 * \return A reference to 'numeric'.
 * \warning Do not pass a value in bit that is larger than the amount
 *          of bits in Numeric - 1.
 * \note When using MSVC the function is only constexpr enabled with msvc17
 *       and newer.
 **/
template<typename Numeric>
#if (PL_COMPILER != PL_COMPILER_MSVC) \
  || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
constexpr
#else
inline
#endif
  Numeric&
  set_bit(PL_INOUT Numeric& numeric, Numeric bit) noexcept
{
  static_assert(
    std::is_unsigned<Numeric>::value,
    "Numeric in pl::setBit should be an unsigned type.");

  numeric |= static_cast<Numeric>(static_cast<Numeric>(1U) << bit);
  return numeric;
}

/*!
 * \brief Clears the bit bit in numeric.
 * \param numeric The number to have its bit bit cleared.
 * \param bit The bit to clear in numeric. [0..bits(Numeric))
 * \return A reference to 'numeric'.
 * \warning The value in bit must not be larger than the amount of bits in
 *          Numeric - 1.
 * \note When using MSVC the function is only constexpr enabled with msvc17
 *       and newer.
 **/
template<typename Numeric>
#if (PL_COMPILER != PL_COMPILER_MSVC) \
  || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
constexpr
#else
inline
#endif
  Numeric&
  clear_bit(PL_INOUT Numeric& numeric, Numeric bit) noexcept
{
  static_assert(
    std::is_unsigned<Numeric>::value,
    "Numeric in pl::clearBit should be an unsigned type.");

  numeric &= static_cast<Numeric>(~(static_cast<Numeric>(1U) << bit));
  return numeric;
}

/*!
 * \brief Toggles the bit bit in numeric.
 * \param numeric The number to have its bit bit toggled.
 * \param bit The bit in numeric to toggle. [0..bits(Numeric))
 * \return A reference to 'numeric'.
 * \warning Do not pass a value in bit that is larger than
 *          the number of bits in Numeric - 1.
 * \note When using MSVC the function is only constexpr enabled with msvc17
 *       and newer.
 *
 * Toggles the bit that was passed into the parameter bit in the
 * numeric (first parameter). If the bit bit in numeric is 1 it will be
 * 0 after having executed this function. If the bit bit in numeric is 0 it
 * will be 1 after having executed this function.
 **/
template<typename Numeric>
#if (PL_COMPILER != PL_COMPILER_MSVC) \
  || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
constexpr
#else
inline
#endif
  Numeric&
  toggle_bit(PL_INOUT Numeric& numeric, Numeric bit) noexcept
{
  static_assert(
    std::is_unsigned<Numeric>::value,
    "Numeric in pl::toggleBit should be an unsigned type.");

  numeric ^= static_cast<Numeric>(static_cast<Numeric>(1U) << bit);
  return numeric;
}

/*!
 * \brief Determines whether or not the bit bit in numeric is set.
 * \param numeric The number in which to check the bit bit.
 * \param bit The bit that is to be checked in number. [0..bits(Numeric))
 * \return true if the bit bit in numeric is set; false otherwise.
 * \warning Do not pass a value into the parameter bit that is larger than
 *          the number of bits in Numeric - 1.
 **/
template<typename Numeric>
constexpr bool is_bit_set(Numeric numeric, Numeric bit) noexcept
{
  static_assert(
    std::is_unsigned<Numeric>::value,
    "Numeric in pl::isBitSet should be an unsigned type.");

  return ((numeric & (static_cast<Numeric>(1U) << bit)) != 0);
}

/*!
 * \brief Obtain a value of type To by reinterpreting the object representation
 *        of from.
 * \param from The object to create a binary reinterpretation of as type To.
 * \return The resulting object of type To.
 * \note To and From must have the same size and must both be trivially
 *       copyable.
 *
 * Obtain a value of type To by reinterpreting the object representation of
 * from. Every bit in the value representation of the returned To object is
 * equal to the corresponding bit in the object representation of from. The
 * values of padding bits in the returned To object are unspecified.
 * If there is no value of type To corresponding to the value representation
 * produced, the behavior is undefined. If there are multiple such values, which
 * value is produced is unspecified.
 **/
template<typename To, typename From>
inline To bit_cast(PL_IN const From& from) noexcept
{
  static_assert(
    sizeof(To) == sizeof(From), "To and From must have the same byte size.");
  static_assert(
    alignof(To) == alignof(From),
    "To and From must have the same alignment requirements.");
  static_assert(std::is_trivial<To>::value, "To is not trivial!");
  static_assert(
    std::is_trivially_copyable<From>::value, "From is not trivially copyable!");

  remove_const_t<To> to;
  std::memcpy(std::addressof(to), std::addressof(from), sizeof(To));
  return to;
}
} // namespace pl
#endif // INCG_PL_BIT_HPP
