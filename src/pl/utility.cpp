#include "../../include/pl/utility.hpp"
#include <ciso646> // not
namespace pl
{
bool toggleBool(PL_INOUT bool &b)
{
    b = not b;
    return b;
}

std::uint8_t charToInt(unsigned char ch)
{
    static constexpr unsigned char subtractThis = '0';
    return static_cast<std::uint8_t>(ch - subtractThis);
}
} // namespace pl
