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
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/bit.hpp" // pl::set_bit, pl::clear_bit, pl::toggle_bit, pl::is_bit_set, pl::bit_cast
#include <climits> // CHAR_BIT
#include <cstdint> // std::uint8_t

TEST_CASE("bits_test")
{
    static constexpr std::uint8_t low_bit{0U};

    static constexpr std::uint8_t high_bit{(sizeof(std::uint8_t) * CHAR_BIT)
                                           - 1U};

    std::uint8_t val{0U};

    for (std::uint8_t i{low_bit}; i <= high_bit; ++i) {
        CHECK_UNARY_FALSE(pl::is_bit_set(val, i));
    }

    CHECK(pl::set_bit(val, low_bit) == 0b0000'0001);
    CHECK_UNARY(pl::is_bit_set(val, low_bit));
    CHECK(pl::set_bit(val, low_bit) == 0b0000'0001);
    CHECK_UNARY(pl::is_bit_set(val, low_bit));
    CHECK(pl::clear_bit(val, low_bit) == 0b0000'0000);
    CHECK_UNARY_FALSE(pl::is_bit_set(val, low_bit));
    CHECK(pl::clear_bit(val, low_bit) == 0b0000'0000);
    CHECK_UNARY_FALSE(pl::is_bit_set(val, low_bit));
    CHECK(pl::toggle_bit(val, low_bit) == 0b000'0001);
    CHECK_UNARY(pl::is_bit_set(val, low_bit));
    CHECK(pl::toggle_bit(val, low_bit) == 0b000'0000);
    CHECK_UNARY_FALSE(pl::is_bit_set(val, low_bit));
}

TEST_CASE("bit_cast")
{
    const std::uint32_t v{pl::bit_cast<std::uint32_t>(2.0F)};
    CHECK(v == UINT32_C(0x40000000));
}
