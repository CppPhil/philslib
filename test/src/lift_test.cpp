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
#include "../../include/pl/compiler.hpp" // PL_COMPILER, PL_COMPILER_CLANG, PL_COMPILER_VERSION, PL_COMPILER_VERSION_CHECK
#include "../../include/pl/lift.hpp"     // PL_LIFT
#include <utility>                       // std::forward, std::move

namespace pl {
namespace test {
namespace {
int fun(const int&) { return 5; }

int fun(const int&&) { return 7; }

template<typename Callable, typename Arg>
int fun2(Callable&& callable, Arg&& arg)
{
    return std::forward<Callable>(callable)(std::forward<Arg>(arg));
}
} // anonymous namespace
} // namespace test
} // namespace pl

#if (PL_COMPILER != PL_COMPILER_CLANG) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(5, 0, 0))
TEST_CASE("lift_test")
{
    int       i{};
    const int j{};

    const int res1{pl::test::fun2(PL_LIFT(pl::test::fun), i)};
    const int res2{pl::test::fun2(PL_LIFT(pl::test::fun), j)};
    const int res3{pl::test::fun2(PL_LIFT(pl::test::fun), std::move(i))};
    const int res4{pl::test::fun2(PL_LIFT(pl::test::fun), std::move(j))};
    const int res5{pl::test::fun2(PL_LIFT(pl::test::fun), 8)};

    CHECK(res1 == 5);
    CHECK(res2 == 5);
    CHECK(res3 == 7);
    CHECK(res4 == 7);
    CHECK(res5 == 7);
}
#endif // (PL_COMPILER != PL_COMPILER_CLANG) || (PL_COMPILER_VERSION >=
       // PL_COMPILER_VERSION_CHECK(5, 0, 0))
