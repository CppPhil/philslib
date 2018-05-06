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

#include "../../include/pl/compiler.hpp"
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic pop
#endif                                  // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/bswap.hpp"   // pl::bswap
#include "../../include/pl/byte.hpp"    // pl::Byte
#include "../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include <array>                        // std::array
#include <cstddef>                      // std::size_t
#include <cstdint>                      // std::uint32_t
#include <cstring>                      // std::memcpy, std::memcmp

TEST_CASE("bswap_test")
{
    static constexpr std::size_t byteSize{4U};

    PL_TEST_STATIC_ASSERT(sizeof(std::uint32_t) == byteSize);

    const std::array<pl::Byte, byteSize> le{{static_cast<pl::Byte>(0xDD),
                                             static_cast<pl::Byte>(0xCC),
                                             static_cast<pl::Byte>(0xBB),
                                             static_cast<pl::Byte>(0xAA)}};
    const std::array<pl::Byte, byteSize> be{{static_cast<pl::Byte>(0xAA),
                                             static_cast<pl::Byte>(0xBB),
                                             static_cast<pl::Byte>(0xCC),
                                             static_cast<pl::Byte>(0xDD)}};

    std::uint32_t val{};

    std::memcpy(&val, le.data(), byteSize);
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, be.data(), byteSize) == 0);
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, le.data(), byteSize) == 0);

    std::memcpy(&val, be.data(), byteSize);
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, le.data(), byteSize) == 0);
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, be.data(), byteSize) == 0);
}
