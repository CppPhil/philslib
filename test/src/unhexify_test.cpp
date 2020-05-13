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
#include "../../include/pl/unhexify.hpp"

TEST_CASE("unhexify_no_delimiter")
{
    const std::vector<pl::byte> expected{0xAB, 0xBC, 0xCD, 0xAA, 0x01};

    CHECK(expected == pl::unhexify("ABBCCDAA01", 0));
}

TEST_CASE("unhexify_delimiter")
{
    const std::vector<pl::byte> expected{0x7E, 0x00, 0x00, 0x1E, 0x54, 0x7E};

    CHECK(expected == pl::unhexify("7E:00:00:1E:54:7E", 1));
}

TEST_CASE("unhexify_long_delimiter")
{
    const std::vector<pl::byte> expected{0xDE, 0xAD, 0xC0, 0xDE};

    constexpr char ary[] = "DE ?????????? AD ?????????? C0 ?????????? DE";

    CHECK(expected == pl::unhexify(ary, 12));
}

TEST_CASE("unhexify_one_byte")
{
    const std::vector<pl::byte> expected{0xAB};

    CHECK(expected == pl::unhexify("AB", 0));
    CHECK(expected == pl::unhexify("AB", 1));
}

TEST_CASE("unhexify_too_short_strings_should_throw")
{
    const auto do_it = [](const char* str) { return pl::unhexify(str, 0); };

    CHECK_THROWS_AS(do_it(""), pl::invalid_size_exception);
    CHECK_THROWS_AS(do_it("A"), pl::invalid_size_exception);
}

TEST_CASE("unhexify_too_short_delimiter_size")
{
    constexpr char    ary1[] = "AB   CD   02   00";
    const std::size_t incorrect_delimiter_size1{2U};

    CHECK_THROWS_AS(
        pl::unhexify(ary1, incorrect_delimiter_size1), std::out_of_range);

    const std::vector<pl::byte> expected2{
        0x00,
        0x00,
        0x00,
        0x00,
        0x10,
        0x00,
        0x00,
        0x02,
        0x00,
        0x00,
        0x00,
        0x30,
        0x00,
        0x00,
        0x04};
    constexpr char    ary2[] = "00     01     02     03     04";
    const std::size_t incorrect_delimiter_size2{0U};
    CHECK(expected2 == pl::unhexify(ary2, incorrect_delimiter_size2));
}

TEST_CASE("unhexify_too_long_delimiter_size")
{
    const std::vector<pl::byte> expected1{0xFF, 0xE0, 0xAB};
    constexpr char              ary1[] = "FFEE00AB";
    CHECK(expected1 == pl::unhexify(ary1, 1));

    const std::vector<pl::byte> expected2{0x7E, 0x30};
    constexpr char              ary2[] = "7E010203047F";
    CHECK(expected2 == pl::unhexify(ary2, 5));
}

TEST_CASE("unhexify_map_ascii")
{
    using bytes = std::vector<pl::byte>;

    const auto byte = [](pl::byte b) { return bytes{b}; };

    std::vector<char> v{'\0', '\0', '\0'};
    char*             buf{v.data()};

    for (std::uint16_t i{}; i <= 0xFF; ++i) {
        buf[1] = static_cast<char>(static_cast<unsigned char>(i));

        const bytes result{
            pl::unhexify(pl::string_view{buf, v.size() - 1U}, 0)};

        switch (i) {
        case 0x30: CHECK(result == byte(0x00)); break;
        case 0x31: CHECK(result == byte(0x01)); break;
        case 0x32: CHECK(result == byte(0x02)); break;
        case 0x33: CHECK(result == byte(0x03)); break;
        case 0x34: CHECK(result == byte(0x04)); break;
        case 0x35: CHECK(result == byte(0x05)); break;
        case 0x36: CHECK(result == byte(0x06)); break;
        case 0x37: CHECK(result == byte(0x07)); break;
        case 0x38: CHECK(result == byte(0x08)); break;
        case 0x39: CHECK(result == byte(0x09)); break;
        case 0x41: PL_FALLTHROUGH
        case 0x61: CHECK(result == byte(0x0A)); break;
        case 0x42: PL_FALLTHROUGH
        case 0x62: CHECK(result == byte(0x0B)); break;
        case 0x43: PL_FALLTHROUGH
        case 0x63: CHECK(result == byte(0x0C)); break;
        case 0x44: PL_FALLTHROUGH
        case 0x64: CHECK(result == byte(0x0D)); break;
        case 0x45: PL_FALLTHROUGH
        case 0x65: CHECK(result == byte(0x0E)); break;
        case 0x46: PL_FALLTHROUGH
        case 0x66: CHECK(result == byte(0x0F)); break;
        }
    }
}
