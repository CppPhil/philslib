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
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include "../../include/pl/as_bytes.hpp" // pl::asBytes
#include "../../include/pl/print_bytes_as_hex.hpp" // pl::PrintBytesAsHex
#include <cstdint> // std::uint32_t
#include <cstring> // std::memcpy
#include <string> // std::string, std::literals::string_literals::operator""s
#include <sstream> // std::ostringstream
#include <iterator> // std::cbegin, std::cend
#include <algorithm> // std::reverse_copy

TEST_CASE("print_bytes_as_hex_test")
{
    using namespace std::literals::string_literals;

    const char array[] = "\xDE\xAD\xC0\xDE";
    std::ostringstream oss{ };

    SUBCASE("default_delimiter") {
        oss << pl::PrintBytesAsHex{ array, sizeof(array) };
        CHECK(oss.str() == "DE AD C0 DE 00"s);
    }

    SUBCASE("no_delimiter") {
        std::uint32_t i{ };
        PL_TEST_STATIC_ASSERT(sizeof(i) <= sizeof(array));
        std::memcpy(&i, array, sizeof(i));
        oss << pl::PrintBytesAsHex{ &i, sizeof(i), "" };
        CHECK(oss.str() == "DEADC0DE"s);
    }

    SUBCASE("custom_delimiter") {
        std::uint32_t i{ };
        PL_TEST_STATIC_ASSERT(sizeof(i) <= sizeof(array));
        std::reverse_copy(std::cbegin(array), std::cend(array) - 1, pl::asBytes(i));
        oss << pl::PrintBytesAsHex{ &i, sizeof(i), "-" };
        CHECK(oss.str() == "DE-C0-AD-DE");
    }
}
