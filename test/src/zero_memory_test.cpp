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
#endif                               // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/byte.hpp" // pl::Byte
#include "../../include/pl/cont/make_array.hpp" // pl::makeArray
#include "../../include/pl/zero_memory.hpp" // pl::zeroMemory, pl::secureZeroMemory
#include <cstdint>                          // std::uint64_t, UINT64_C

TEST_CASE("zero_memory_test")
{
    auto ary = pl::cont::make_array(
        static_cast<pl::byte>(0xAB),
        static_cast<pl::byte>(0xCD),
        static_cast<pl::byte>(0xEF),
        static_cast<pl::byte>(0x10));

    std::uint64_t i{UINT64_C(0x1A1BAABBCCDDEEFF)};

    for (pl::byte byte : ary) {
        REQUIRE(byte != static_cast<pl::byte>(0x00));
    }

    REQUIRE(i != UINT64_C(0));

    SUBCASE("zero_memory")
    {
        pl::zeroMemory(ary.data(), ary.size());

        for (pl::byte byte : ary) {
            CHECK(byte == static_cast<pl::byte>(0x00));
        }

        pl::zeroMemory(&i, sizeof(i));
        CHECK(i == UINT64_C(0));
    }

    SUBCASE("secure_zero_memory")
    {
        pl::secureZeroMemory(ary.data(), ary.size());

        for (pl::byte byte : ary) {
            CHECK(byte == static_cast<pl::byte>(0x00));
        }

        pl::secureZeroMemory(&i, sizeof(i));
        CHECK(i == UINT64_C(0));
    }
}
