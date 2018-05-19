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
#endif                                   // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/asprintf.hpp" // pl::asprintf, pl::vasprintf
#include <cstddef>                       // std::size_t
#include <cstring>                       // std::strcmp, std::strlen
#include <memory>                        // std::unique_ptr
#include <string>                        // std::string

TEST_CASE("asprintf_unique_ptr_test")
{
    static constexpr int expected_bytes_written{7};

    std::unique_ptr<char[]> up{nullptr};

    const int ret{pl::asprintf(&up, "Text %02X", 0xF)};

    REQUIRE(ret >= 0);
    REQUIRE(up != nullptr);

    CHECK(ret == expected_bytes_written);
    CHECK(
        std::strlen(up.get())
        == static_cast<std::size_t>(expected_bytes_written));
    CHECK(std::strcmp(up.get(), "Text 0F") == 0);
}

TEST_CASE("asprintf_string_test")
{
    static constexpr int  expected_bytes_written{21};
    static constexpr char str[]{"Hello World"};

    std::string string{};

    int ret{pl::asprintf(&string, "String: \"%s\"", str)};

    REQUIRE(ret >= 0);
    REQUIRE_UNARY_FALSE(string.empty());

    CHECK(ret == expected_bytes_written);
    CHECK(
        string.size()
        == static_cast<std::string::size_type>(expected_bytes_written));
    CHECK(string == "String: \"Hello World\"");

    ret = pl::asprintf(&string, "%.*s", 6, "Sample Text");

    REQUIRE(ret >= 0);
    REQUIRE_UNARY_FALSE(string.empty());

    CHECK(ret == 6);
    CHECK(string.size() == 6U);
    CHECK(string == "Sample");
}
