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
 * \file size_t.hpp
 * \brief Exports a user defined literal (UDL) to create an object of type
 *        std::size_t.
**/
#ifndef INCG_PL_SIZE_T_HPP
#define INCG_PL_SIZE_T_HPP
#include "no_macro_substitution.hpp" // PL_NO_MACRO_SUBSTITUTION
#include <ciso646> // and
#include <cassert> // assert
#include <cstddef> // std::size_t
#include <limits> // std::numeric_limits

namespace pl
{
inline namespace literals
{
inline namespace integer_literals
{
/*!
 * \brief User defined literal (UDL) to create an object of type std::size_t.
 * \param value The value to create the std::size_t object. Must be within
 *              the range [0,std::numeric_limits<std::size_t>::max()].
 * \return The resulting std::size_t object.
 * \warning If the value passed in is larger than
 *          std::numeric_limits<std::size_t>::max()
 *          the program is ill-formed.
**/
constexpr std::size_t operator""_zu(unsigned long long value)
{
    assert(
        (value <= std::numeric_limits<std::size_t>::max PL_NO_MACRO_SUBSTITUTION())
        and "value was too large in pl::literals::integer_literals::operator\"\"_zu");
    return static_cast<std::size_t>(value);
}
} // inline namespace integer_literals
} // inline namespace literals
} // namespace pl
#endif // INCG_PL_SIZE_T_HPP
