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
 * \file bswap.hpp
 * \brief Exports the bswap function template that allows reversing the bytes
 *        of any object.
 **/
#ifndef INCG_PL_BSWAP_HPP
#define INCG_PL_BSWAP_HPP
#include "as_bytes.hpp" // pl::asBytes
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC, PL_COMPILER_GCC, PL_COMPILER_CLANG, PL_COMPILER_ICC
#include "inline.hpp"   // PL_ALWAYS_INLINE
#include "meta/disable_if.hpp"   // pl::meta::disable_if_t
#include "meta/remove_cvref.hpp" // pl::meta::remove_cvref_t
#include <algorithm>             // std::reverse
#include <ciso646>               // or
#include <cstdint> // std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, std::int8_t, std::int16_t, std::int32_t, std::int64_t
#if PL_COMPILER == PL_COMPILER_MSVC
#include <stdlib.h> // _byteswap_ushort, _byteswap_ulong, _byteswap_uint64
#endif              // PL_COMPILER == PL_COMPILER_MSVC

namespace pl {
namespace detail {
template<typename Type>
inline Type bswap_impl(Type ty) noexcept
{
  auto       begin = ::pl::as_bytes(ty);
  const auto end   = begin + sizeof(Type);

  std::reverse(begin, end);

  return ty;
}
} // namespace detail

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE char bswap(char val) noexcept
{
  return val;
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE std::uint8_t bswap(std::uint8_t val) noexcept
{
  return val;
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE std::uint16_t bswap(std::uint16_t val) noexcept
{
#if (PL_COMPILER == PL_COMPILER_GCC) or (PL_COMPILER == PL_COMPILER_CLANG) \
  or (PL_COMPILER == PL_COMPILER_ICC)
  return __builtin_bswap16(val);
#elif PL_COMPILER == PL_COMPILER_MSVC
  return _byteswap_ushort(val);
#else
  return detail::bswap_impl(val);
#endif
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE std::uint32_t bswap(std::uint32_t val) noexcept
{
#if (PL_COMPILER == PL_COMPILER_GCC) or (PL_COMPILER == PL_COMPILER_CLANG) \
  or (PL_COMPILER == PL_COMPILER_ICC)
  return __builtin_bswap32(val);
#elif PL_COMPILER == PL_COMPILER_MSVC
  return _byteswap_ulong(val);
#else
  return detail::bswap_impl(val);
#endif
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE std::uint64_t bswap(std::uint64_t val) noexcept
{
#if (PL_COMPILER == PL_COMPILER_GCC) or (PL_COMPILER == PL_COMPILER_CLANG) \
  or (PL_COMPILER == PL_COMPILER_ICC)
  return __builtin_bswap64(val);
#elif PL_COMPILER == PL_COMPILER_MSVC
  return _byteswap_uint64(val);
#else
  return detail::bswap_impl(val);
#endif
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE std::int8_t bswap(std::int8_t val) noexcept
{
  return static_cast<std::int8_t>(bswap(static_cast<std::uint8_t>(val)));
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE std::int16_t bswap(std::int16_t val) noexcept
{
  return static_cast<std::int16_t>(bswap(static_cast<std::uint16_t>(val)));
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE std::int32_t bswap(std::int32_t val) noexcept
{
  return static_cast<std::int32_t>(bswap(static_cast<std::uint32_t>(val)));
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param val The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
PL_ALWAYS_INLINE std::int64_t bswap(std::int64_t val) noexcept
{
  return static_cast<std::int64_t>(bswap(static_cast<std::uint64_t>(val)));
}

/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param ty The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
 **/
template<typename Ty>
PL_ALWAYS_INLINE auto bswap(Ty ty) noexcept -> meta::disable_if_t<
  std::is_same<meta::remove_cvref_t<Ty>, std::uint8_t>::value
    or std::is_same<meta::remove_cvref_t<Ty>, std::uint16_t>::value
    or std::is_same<meta::remove_cvref_t<Ty>, std::uint32_t>::value
    or std::is_same<meta::remove_cvref_t<Ty>, std::uint64_t>::value
    or std::is_same<meta::remove_cvref_t<Ty>, std::int8_t>::value
    or std::is_same<meta::remove_cvref_t<Ty>, std::int16_t>::value
    or std::is_same<meta::remove_cvref_t<Ty>, std::int32_t>::value
    or std::is_same<meta::remove_cvref_t<Ty>, std::int64_t>::value
    or std::is_same<meta::remove_cvref_t<Ty>, char>::value
    or std::is_same<meta::remove_cvref_t<Ty>, unsigned char>::value
    or std::is_same<meta::remove_cvref_t<Ty>, signed char>::value,
  Ty>
{
  return ::pl::detail::bswap_impl(ty);
}
} // namespace pl
#endif // INCG_PL_BSWAP_HPP
