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
