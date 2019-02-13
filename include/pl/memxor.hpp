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
 * \file memxor.hpp
 * \brief Exports the memxor function.
**/
#ifndef INCG_PL_MEMXOR_HPP
#define INCG_PL_MEMXOR_HPP
#include "annotations.hpp" // PL_IN, PL_INOUT
#include "byte.hpp"        // pl::Byte
#include "restrict.hpp"    // PL_RESTRICT
#include <cstddef>         // std::size_t

namespace pl {
/*!
 * \brief Bytewise xor-assigns the memory pointed to by 'destination'
 *        with the memory pointed to by 'source'.
 * \param destination The buffer that will be xor-assigned to.
 *                    May not be nullptr!
 * \param source The buffer with which 'destination' shall be xored.
 *               May not be nullptr!
 * \param byte_count The size in bytes of the source buffer.
 *                  The destination buffer must be at least as large as
 *                  'byte_count'. You probably want to use buffers of equal
 *                  byte size for 'destination' and 'source'.
 * \return 'destination' is returned.
 * \warning Make sure 'byte_count' is correct!
**/
inline void* memxor(
    PL_INOUT void* PL_RESTRICT destination,
    PL_IN const void* PL_RESTRICT source,
    std::size_t                   byte_count) noexcept
{
    auto dest = static_cast<byte * PL_RESTRICT>(destination);
    auto src  = static_cast<const byte * PL_RESTRICT>(source);

    while (byte_count > 0) {
        *dest ^= *src;

        --byte_count;
        ++dest;
        ++src;
    }

    return destination;
}
} // namespace pl
#endif // INCG_PL_MEMXOR_HPP
