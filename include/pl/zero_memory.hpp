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
 * \file zero_memory.hpp
 * \brief Exports the pl::zero_memory and the pl::secure_zero_memory functions.
 **/
#ifndef INCG_PL_ZERO_MEMORY_HPP
#define INCG_PL_ZERO_MEMORY_HPP
#include "annotations.hpp" // PL_OUT
#include "byte.hpp"        // pl::byte
#include "inline.hpp"      // PL_ALWAYS_INLINE
#include <cstddef>         // std::size_t

namespace pl {
/*!
 * \brief Copies a zero byte into each of the first count_bytes
 *        characters of the object pointed to by dest.
 * \param dest Pointer to the object to fill with zero bytes.
 *        (May never be a null pointer!)
 * \param count_bytes number of bytes to fill with zeroes.
 * \return dest (a copy of the first parameter as it was passed in)
 * \warning pl::zero_memory may be optimized away if the object modified
 *          by this function is not accessed again for the rest of its lifetime.
 *          For that reason, this function cannot be used
 *          to scrub memory (e.g. to fill an array that stored a password
 *          with zeroes). Use secure_zero_memory in those cases as it will
 *          not be optimized.
 * \warning If the object pointed to by dest is not trivially-copyable
 *          (e.g., scalar, array, or a C-compatible struct),
 *          the behavior is undefined.
 * \warning If count_bytes is greater than the size of the object pointed
 *          to by dest, the behavior is undefined.
 * \warning dest may not be a null pointer.
 * \see secure_zero_memory
 **/
PL_ALWAYS_INLINE void* zero_memory(
  PL_OUT void* dest,
  std::size_t  count_bytes) noexcept
{
  byte* ptr{static_cast<byte*>(dest)};

  for (; count_bytes != 0U; ++ptr, --count_bytes) {
    *ptr = 0U;
  }

  return dest;
}

/*!
 * \brief Copies a zero byte into each of the first count_bytes characters
 *        of the object pointed to by dest.
 * \param dest Pointer to the object to fill with zero bytes.
 *        (May never be a null pointer!)
 * \param count_bytes number of bytes to fill with zeroes.
 * \return dest (a copy of the first parameter as it was passed in)
 * \note Unlike pl::zero_memory a call to this function will never be
 *       optimized away.
 * \warning If the object pointed to by dest is not trivially-copyable
 *          (e.g., scalar, array, or a C-compatible struct), the behavior is
 *          undefined.
 * \warning If count_bytes is greater than the size of the object pointed to by
 *          dest, the behavior is undefined.
 * \warning dest may not be a null pointer.
 * \see zero_memory
 *
 * Zeroes bytes just like pl::zero_memory, but ensures that the compiler
 * will not optimize the function call away. Use this function instead of
 * pl::zero_memory when you want to ensure that the data will be zeroed out
 * even if the object pointed to by dest will not be referenced after
 * a call to this function.
 **/
PL_ALWAYS_INLINE void* secure_zero_memory(
  PL_OUT void* dest,
  std::size_t  count_bytes) noexcept
{
  volatile byte* ptr{static_cast<volatile byte*>(dest)};

  for (; count_bytes != 0U; ++ptr, --count_bytes) {
    *ptr = 0U;
  }

  return dest;
}
} // namespace pl
#endif // INCG_PL_ZERO_MEMORY_HPP
