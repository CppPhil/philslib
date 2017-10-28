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

#include "../../include/pl/print_bytes_as_hex.hpp"
#include "../../include/pl/byte.hpp" // pl::Byte
#include <cstdint> // std::uint16_t
#include <ios> // std::uppercase, std::hex
#include <iomanip> // std::setw, std::setfill
#include <ostream> // std::ostream
#include <utility> // std::move

namespace pl
{
PrintBytesAsHex::PrintBytesAsHex(
    PL_IN const void *dataToPrint,
    std::size_t countBytes,
    std::string delim)
    : m_dataToPrint{ dataToPrint },
      m_countBytes{ countBytes },
      m_delim{ std::move(delim) }
{
    PL_THROW_IF_NULL(m_dataToPrint);

    if (m_countBytes == 0U) {
        throw InvalidSizeException{
            "countBytes in pl::PrintBytesAsHex constructor was 0."
        };
    }
}

PrintBytesAsHex::PrintBytesAsHex(const this_type &) = default;

PrintBytesAsHex::PrintBytesAsHex(this_type &&) = default;

PrintBytesAsHex &PrintBytesAsHex::operator=(const this_type &) = default;

PrintBytesAsHex &PrintBytesAsHex::operator=(this_type &&) = default;

std::ostream &operator<<(
    PL_INOUT std::ostream &os,
    PL_IN const PrintBytesAsHex &toPrint)
{
    static constexpr auto nibblesPerByte = 2;
    static constexpr auto fillChar = '0';

    // save the format flags.
    const auto flags = os.flags();

    try {
        os << std::uppercase << std::hex;

        auto *dataToPrint = static_cast<const Byte *>(toPrint.m_dataToPrint);

        for (std::size_t i{ 0U }; i < toPrint.m_countBytes; ++i) {
            os << std::setw(nibblesPerByte) << std::setfill(fillChar)
               << static_cast<std::uint16_t>(dataToPrint[i]);

            if (i < (toPrint.m_countBytes - 1U)) {
                os << toPrint.m_delim;
            }
        }
    } catch (...) {
        // restore the format flags
        os.flags(flags);
        throw;
    }

    // restore the format flags
    os.flags(flags);
    return os;
}
} // namespace pl
