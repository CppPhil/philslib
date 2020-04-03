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
 * \file unhexify.hpp
 * \brief Exports the unhexify function.
 **/
#ifndef INCG_PL_UNHEXIFY_HPP
#define INCG_PL_UNHEXIFY_HPP
#include "byte.hpp"   // pl::byte
#include "except.hpp" // PL_THROW_WITH_SOURCE_INFO, pl::invalid_size_exception
#include "string_view.hpp" // pl::string_view
#include <array>           // std::array
#include <cstddef>         // std::size_t
#include <vector>          // std::vector

namespace pl {
/*!
 * \brief Converts a hex encoded string into bytes.
 * \param hex_string The hex encoded string to turn into bytes.
 * \param delimiter_size The size of the delimiter (in bytes) used to separate
 *                       the pairs of hexits from each other.
 *                       Shall be 0 if no delimiter is used.
 * \return The resulting bytes.
 * \throws invalid_size_exception if `hex_string` has fewer than 2 characters.
 *         std::out_of_range can be thrown if the delimiter_size given is
 *         incorrect.
 * \warning Assumes `hex_string` to be a valid hex encoded string.
 *          Invalid characters will be mapped to garbage bytes.
 **/
inline std::vector<byte> unhexify(
    string_view hex_string,
    std::size_t delimiter_size)
{
    constexpr std::size_t          nibbles_per_byte{2U};
    constexpr std::size_t          high_nibble_offset{0U};
    constexpr std::size_t          low_nibble_offset{1U};
    constexpr std::array<byte, 2U> offsets{{0U, 9U}};

    if (hex_string.size() < nibbles_per_byte) {
        PL_THROW_WITH_SOURCE_INFO(
            invalid_size_exception, "hex_string was smaller than 2!");
    }

    const std::size_t stride{nibbles_per_byte + delimiter_size};
    const std::size_t byte_count{(hex_string.size() + delimiter_size) / stride};

    std::vector<byte> buffer(byte_count);

    for (std::size_t i{0U}; i < hex_string.size(); i += stride) {
        const byte high_nibble{
            static_cast<byte>(hex_string[i + high_nibble_offset])};
        const byte low_nibble{
            static_cast<byte>(hex_string[i + low_nibble_offset])};

        using namespace pl::literals::integer_literals;

        buffer.at(i / stride) = static_cast<byte>(
            (((high_nibble & 0xF_byte)
              + offsets[(high_nibble & 0x40_byte) != 0_byte])
             << 4_byte)
            | ((low_nibble & 0xF_byte)
               + offsets[(low_nibble & 0x40_byte) != 0_byte]));
    }

    return buffer;
}
} // namespace pl
#endif // INCG_PL_UNHEXIFY_HPP
