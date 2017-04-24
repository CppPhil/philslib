#include "../../include/pl/lowlevel.hpp"
#include <cstring> // std::memset

namespace pl
{
void *zeroMemory(PL_OUT void *dest, std::size_t countBytes)
{
    return std::memset(dest, 0, countBytes);
}

void *secureZeroMemory(PL_OUT void *dest, std::size_t countBytes)
{
    volatile Byte *ptr = static_cast<volatile Byte *>(dest);

    for (; countBytes != 0U; ++ptr, --countBytes) {
        *ptr = 0U;
    }

    return dest;
}

} // namespace pl
