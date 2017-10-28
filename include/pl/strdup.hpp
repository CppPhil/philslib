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
 * \file strdup.hpp
 * \brief Exports the strdup and strndup functions, which are similar
 *        to those specified by POSIX.
**/
#ifndef INCG_PL_STRDUP_HPP
#define INCG_PL_STRDUP_HPP
#include "annotations.hpp" // PL_NODISCARD, PL_IN, PL_NULL_TERMINATED
#include <cstddef> // std::size_t
#include <memory> // std::unique_ptr

namespace pl
{
/*!
 * \brief Creates a copy of a null-terminated string.
 * \param str Pointer to the null-terminated byte string to duplicate.
 *            May not be nullptr!
 * \return The copy.
**/
PL_NODISCARD std::unique_ptr<char[]> strdup(
    PL_IN PL_NULL_TERMINATED(const char *)str) noexcept;

/*!
 * \brief Creates a unique_ptr that holds a null-terminated byte string.
 * \param str Pointer to the null-terminated byte string to duplicate.
 *            May not be nullptr!
 * \param size Maximum number of bytes to copy from 'str'.
 * \return The duplicated string.
 *
 * Creates a unique_ptr that holds a null-terminated byte string,
 * which contains copies of at most 'size' bytes from the string pointed
 * to by 'str'. If the null terminator is not encountered in the first
 * 'size' bytes, it is added to the duplicated string.
**/
PL_NODISCARD std::unique_ptr<char[]> strndup(
    PL_IN PL_NULL_TERMINATED(const char *)str,
    std::size_t size) noexcept;
} // namespace pl
#endif // INCG_PL_STRDUP_HPP
