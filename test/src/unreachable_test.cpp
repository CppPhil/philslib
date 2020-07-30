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
#endif                                      // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/string_view.hpp" // pl::string_view
#include "../../include/pl/unreachable.hpp" // PL_UNREACHABLE
#include "../include/static_assert.hpp"     // PL_TEST_STATIC_ASSERT

namespace pl {
namespace test {
namespace {
enum class test_enum { a, b, c };

constexpr string_view to_s(test_enum enm) noexcept
{
    using namespace pl::literals::string_view_literals;

    switch (enm) {
    case test_enum::a: return "a"_sv;
    case test_enum::b: return "b"_sv;
    case test_enum::c: return "c"_sv;
    }

    PL_UNREACHABLE();
}
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("unreachable_test")
{
    using namespace pl::literals::string_view_literals;

    PL_TEST_STATIC_ASSERT(
        pl::test::to_s(pl::test::test_enum::a).front() == 'a');
    PL_TEST_STATIC_ASSERT(
        pl::test::to_s(pl::test::test_enum::b).front() == 'b');
    PL_TEST_STATIC_ASSERT(
        pl::test::to_s(pl::test::test_enum::c).front() == 'c');

    CHECK(pl::test::to_s(pl::test::test_enum::a) == "a"_sv);
    CHECK(pl::test::to_s(pl::test::test_enum::b) == "b"_sv);
    CHECK(pl::test::to_s(pl::test::test_enum::c) == "c"_sv);
}
