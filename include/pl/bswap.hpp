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
#include <algorithm>    // std::reverse

namespace pl {
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
template <typename Type>
inline Type bswap(Type ty) noexcept
{
    auto       begin = ::pl::as_bytes(ty);
    const auto end   = begin + sizeof(Type);

    std::reverse(begin, end);

    return ty;
}
} // namespace pl
#endif // INCG_PL_BSWAP_HPP
