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
#include "../../include/pl/bitmask.hpp" // PL_ENABLE_BITMASK_OPERATORS
#include <cstdint>                      // std::uint8_t

namespace pl {
namespace test {
namespace {
enum class Flag : std::uint8_t {
    a = 0b0000'0000,
    b = 0b0000'0001,
    c = 0b0000'0010,
    d = 0b0000'0011,
    e = 0b1111'1111
};
PL_ENABLE_BITMASK_OPERATORS(Flag)
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("bit_or_test")
{
    CHECK((pl::test::Flag::a | pl::test::Flag::b) == pl::test::Flag::b);
    CHECK((pl::test::Flag::a | pl::test::Flag::c) == pl::test::Flag::c);
    CHECK((pl::test::Flag::b | pl::test::Flag::c) == pl::test::Flag::d);
    CHECK((pl::test::Flag::d | pl::test::Flag::b) == pl::test::Flag::d);
    CHECK((pl::test::Flag::d | pl::test::Flag::c) == pl::test::Flag::d);

    pl::test::Flag flag{pl::test::Flag::b};
    flag |= pl::test::Flag::c;

    CHECK(flag == pl::test::Flag::d);
}

TEST_CASE("bit_and_test")
{
    CHECK((pl::test::Flag::d & pl::test::Flag::c) == pl::test::Flag::c);
    CHECK((pl::test::Flag::d & pl::test::Flag::b) == pl::test::Flag::b);
    CHECK((pl::test::Flag::a & pl::test::Flag::b) == pl::test::Flag::a);
    CHECK((pl::test::Flag::a & pl::test::Flag::c) == pl::test::Flag::a);
    CHECK((pl::test::Flag::a & pl::test::Flag::d) == pl::test::Flag::a);
    CHECK((pl::test::Flag::a & pl::test::Flag::e) == pl::test::Flag::a);

    pl::test::Flag flag{pl::test::Flag::d};
    flag &= pl::test::Flag::b;

    CHECK(flag == pl::test::Flag::b);
}

TEST_CASE("xor_test")
{
    CHECK((pl::test::Flag::b ^ pl::test::Flag::c) == pl::test::Flag::d);
    CHECK((pl::test::Flag::c ^ pl::test::Flag::d) == pl::test::Flag::b);
    CHECK((pl::test::Flag::b ^ pl::test::Flag::d) == pl::test::Flag::c);

    pl::test::Flag flag{pl::test::Flag::b};
    flag ^= pl::test::Flag::c;

    CHECK(flag == pl::test::Flag::d);
}

TEST_CASE("bit_complement_test")
{
    CHECK(~pl::test::Flag::a == pl::test::Flag::e);
    CHECK(~pl::test::Flag::e == pl::test::Flag::a);
}
