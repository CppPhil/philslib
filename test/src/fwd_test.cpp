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
#endif                              // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/fwd.hpp" // PL_FWD
#include <utility>                  // std::move

namespace pl {
namespace test {
namespace {
int f(const int&&) { return 0; }

int f(const int&) { return 1; }

template<typename Ty>
int g(Ty&& ty)
{
    return f(PL_FWD(ty));
}
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("fwd_test")
{
    int       i{};
    const int j{};

    const int res1{pl::test::g(i)};
    const int res2{pl::test::g(j)};
    const int res3{pl::test::g(std::move(i))};
    const int res4{pl::test::g(std::move(j))};
    const int res5{pl::test::g(1)};

    CHECK(res1 == 1);
    CHECK(res2 == 1);
    CHECK(res3 == 0);
    CHECK(res4 == 0);
    CHECK(res5 == 0);
}
