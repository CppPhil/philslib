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
#endif                                 // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/strdup.hpp" // pl::strdup, pl::strndup
#include <cstddef>                     // std::size_t
#include <cstring>                     // std::strlen, std::strcmp

TEST_CASE("strdup_test")
{
    static constexpr char   str[]{"Text"};
    std::unique_ptr<char[]> up{pl::strdup(str)};

    REQUIRE(up != nullptr);
    CHECK(std::strlen(up.get()) == 4U);
    CHECK(std::strcmp(up.get(), str) == 0);

    up = pl::strdup("");
    REQUIRE(up != nullptr);
    CHECK(std::strlen(up.get()) == 0U);
    CHECK(up[0U] == '\0');
}

TEST_CASE("strndup_test")
{
    static constexpr char        str[]{"Sample text"};
    static constexpr std::size_t strLen{(sizeof(str) / sizeof(str[0U]))
                                        - sizeof(str[0U])};
    std::unique_ptr<char[]> up{nullptr};

    up = pl::strndup(str, 0U);
    REQUIRE(up != nullptr);
    REQUIRE(std::strlen(up.get()) == 0U);
    CHECK(up[0U] == '\0');

    up = pl::strndup(str, 1U);
    REQUIRE(up != nullptr);
    REQUIRE(std::strlen(up.get()) == 1U);
    CHECK(up[0U] == 'S');
    CHECK(up[1U] == '\0');

    up = pl::strndup(str, 3U);
    REQUIRE(up != nullptr);
    REQUIRE(std::strlen(up.get()) == 3U);
    CHECK(std::strcmp(up.get(), "Sam") == 0);
    CHECK(up[3U] == '\0');

    up = pl::strndup(str, strLen);
    REQUIRE(up != nullptr);
    REQUIRE(std::strlen(up.get()) == strLen);
    CHECK(std::strcmp(up.get(), str) == 0);
    CHECK(up[strLen] == '\0');

    up = pl::strndup(str, strLen + 1U);
    REQUIRE(up != nullptr);
    REQUIRE(std::strlen(up.get()) == strLen);
    CHECK(std::strcmp(up.get(), str) == 0);
    CHECK(up[strLen] == '\0');

    up = pl::strndup(str, 500U);
    REQUIRE(up != nullptr);
    REQUIRE(std::strlen(up.get()) == strLen);
    CHECK(std::strcmp(up.get(), str) == 0);
    CHECK(up[strLen] == '\0');
}
