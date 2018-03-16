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
 * \file byte.hpp
 * \brief Exports the Byte type and an associated user defined literal.
**/
#ifndef INCG_PL_BYTE_HPP
#define INCG_PL_BYTE_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC, PL_COMPILER_VERSION, PL_COMPILER_VERSION_CHECK
#include <ciso646> // and
#include <cassert> // assert
#include <climits> // UCHAR_MAX

namespace pl
{
/*!
 * \brief The Byte type. To be used when viewing something as raw bytes.
 *        An alias for unsigned char. This type is effectively a 1 byte large
 *        unsigned integer.
**/
using Byte = unsigned char;

inline namespace literals
{
inline namespace integer_literals
{
/*!
 * \brief User defined literal (UDL) to create a pl::Byte object.
 * \param value The value to use to create the pl::Byte object,
 *              must be in the range [0,UCHAR_MAX].
 * \return The resulting pl::Byte object.
 * \warning If the value passed in is larger than UCHAR_MAX the program
 *          is ill-formed.
**/
constexpr ::pl::Byte operator""_byte(unsigned long long value)
{
#if (PL_COMPILER != PL_COMPILER_MSVC) || ((PL_COMPILER == PL_COMPILER_MSVC) && (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0)))
    assert(
        (value <= UCHAR_MAX)
        and "value was too large in "
        "pl::literals::integer_literals::operator\"\"_byte");
#endif // (PL_COMPILER != PL_COMPILER_MSVC) || ((PL_COMPILER == PL_COMPILER_MSVC) && (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0)))
    return static_cast<::pl::Byte>(value);
}
} // inline namespace integer_literals
} // inline namespace literals
} // namespace pl
#endif // INCG_PL_BYTE_HPP
