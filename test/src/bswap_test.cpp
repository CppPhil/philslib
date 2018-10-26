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
#endif                                // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/bswap.hpp" // pl::bswap
#include "../../include/pl/byte.hpp"  // pl::byte
#include "../../include/pl/cont/make_array.hpp" // pl::cont::make_array
#include "../../include/pl/packed.hpp"  // PL_PACKED_START, PL_PACKED_END
#include "../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include <array>                        // std::array
#include <cstddef>                      // std::size_t
#include <cstdint>                      // std::uint32_t
#include <cstring>                      // std::memcpy, std::memcmp

TEST_CASE("bswap_basic_test")
{
    static constexpr std::size_t byte_size{4U};

    PL_TEST_STATIC_ASSERT(sizeof(std::uint32_t) == byte_size);

    const std::array<pl::byte, byte_size> le{{static_cast<pl::byte>(0xDD),
                                              static_cast<pl::byte>(0xCC),
                                              static_cast<pl::byte>(0xBB),
                                              static_cast<pl::byte>(0xAA)}};
    const std::array<pl::byte, byte_size> be{{static_cast<pl::byte>(0xAA),
                                              static_cast<pl::byte>(0xBB),
                                              static_cast<pl::byte>(0xCC),
                                              static_cast<pl::byte>(0xDD)}};

    std::uint32_t val{};

    std::memcpy(&val, le.data(), byte_size);
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, be.data(), byte_size) == 0);
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, le.data(), byte_size) == 0);

    std::memcpy(&val, be.data(), byte_size);
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, le.data(), byte_size) == 0);
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, be.data(), byte_size) == 0);
}

TEST_CASE("bswap_uchar_test")
{
    static constexpr unsigned char val{static_cast<unsigned char>('\x7E')};
    static constexpr unsigned char expected{static_cast<unsigned char>('\x7E')};
    CHECK(pl::bswap(val) == expected);
}

TEST_CASE("bswap_schar_test")
{
    static constexpr signed char val{static_cast<signed char>('\x7E')};
    static constexpr signed char expected{static_cast<signed char>('\x7E')};
    CHECK(pl::bswap(val) == expected);
}

TEST_CASE("bswap_char_test")
{
    static constexpr char val{'\x7E'};
    static constexpr char expected{'\x7E'};
    CHECK(pl::bswap(val) == expected);
}

TEST_CASE("bswap_u8_test")
{
    static constexpr std::uint8_t val{UINT8_C(0x7E)};
    CHECK(pl::bswap(val) == UINT8_C(0x7E));
}

using namespace pl::literals::integer_literals;

TEST_CASE("bswap_u16_test")
{
    static constexpr auto data     = pl::cont::make_array(0x7E_byte, 0x90_byte);
    static constexpr auto expected = pl::cont::make_array(0x90_byte, 0x7E_byte);

    std::uint16_t val;
    std::memcpy(&val, data.data(), sizeof(val));
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, expected.data(), sizeof(val)) == 0);
}

TEST_CASE("bswap_u32_test")
{
    static constexpr auto data
        = pl::cont::make_array(0x7E_byte, 0x90_byte, 0x5A_byte, 0xF7_byte);
    static constexpr auto expected
        = pl::cont::make_array(0xF7_byte, 0x5A_byte, 0x90_byte, 0x7E_byte);

    std::uint32_t val;
    std::memcpy(&val, data.data(), sizeof(val));
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, expected.data(), sizeof(val)) == 0);
}

TEST_CASE("bswap_u64_test")
{
    static constexpr auto data = pl::cont::make_array(
        0x7E_byte,
        0x90_byte,
        0x5A_byte,
        0xF7_byte,
        0xDE_byte,
        0xAD_byte,
        0xC0_byte,
        0xDE_byte);
    static constexpr auto expected = pl::cont::make_array(
        0xDE_byte,
        0xC0_byte,
        0xAD_byte,
        0xDE_byte,
        0xF7_byte,
        0x5A_byte,
        0x90_byte,
        0x7E_byte);

    std::uint64_t val;
    std::memcpy(&val, data.data(), sizeof(val));
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, expected.data(), sizeof(val)) == 0);
}

TEST_CASE("bswap_i8_test")
{
    static constexpr std::int8_t val{INT8_C(0x7E)};
    CHECK(pl::bswap(val) == INT8_C(0x7E));
}

using namespace pl::literals::integer_literals;

TEST_CASE("bswap_i16_test")
{
    static constexpr auto data     = pl::cont::make_array(0x7E_byte, 0x90_byte);
    static constexpr auto expected = pl::cont::make_array(0x90_byte, 0x7E_byte);

    std::int16_t val;
    std::memcpy(&val, data.data(), sizeof(val));
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, expected.data(), sizeof(val)) == 0);
}

TEST_CASE("bswap_i32_test")
{
    static constexpr auto data
        = pl::cont::make_array(0x7E_byte, 0x90_byte, 0x5A_byte, 0xF7_byte);
    static constexpr auto expected
        = pl::cont::make_array(0xF7_byte, 0x5A_byte, 0x90_byte, 0x7E_byte);

    std::int32_t val;
    std::memcpy(&val, data.data(), sizeof(val));
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, expected.data(), sizeof(val)) == 0);
}

TEST_CASE("bswap_64_test")
{
    static constexpr auto data = pl::cont::make_array(
        0x7E_byte,
        0x90_byte,
        0x5A_byte,
        0xF7_byte,
        0xDE_byte,
        0xAD_byte,
        0xC0_byte,
        0xDE_byte);
    static constexpr auto expected = pl::cont::make_array(
        0xDE_byte,
        0xC0_byte,
        0xAD_byte,
        0xDE_byte,
        0xF7_byte,
        0x5A_byte,
        0x90_byte,
        0x7E_byte);

    std::int64_t val;
    std::memcpy(&val, data.data(), sizeof(val));
    val = pl::bswap(val);
    CHECK(std::memcmp(&val, expected.data(), sizeof(val)) == 0);
}

namespace {
PL_PACKED_START
struct buf {
    char text[20];
};
PL_PACKED_END
} // anonymous namespace

TEST_CASE("bswap_struct")
{
    static constexpr char expected[20]
        = {'\0', '\0', '\0', '\0', '\0', '\0', 't', 's', 'e', 't',
           ' ',  'a',  ' ',  's',  'i',  ' ',  's', 'i', 'h', 't'};
    static constexpr buf a{"this is a test"};

    const buf res{pl::bswap(a)};
    CHECK(std::memcmp(&res, expected, 20) == 0);
}
