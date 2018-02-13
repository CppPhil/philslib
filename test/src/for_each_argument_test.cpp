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
#include "../../include/pl/for_each_argument.hpp" // pl::forEachArgument

namespace pl
{
namespace test
{
namespace
{
int g_intVal{ 0 };
} // anonymous namespace

void f(int v)
{
    g_intVal += v;
}

struct Struct
{
    void memFun() const
    {
        ++g_intVal;
    }

    void operator()(int v)
    {
        g_intVal += v;
        m_val = g_intVal;
    }

    int m_val = 0;
};
} // namespace test
} // namespace pl

TEST_CASE("for_each_argument_test")
{
    void (*fp)(int){ &pl::test::f };

    void (pl::test::Struct::*memFunPtr)() const{
        &pl::test::Struct::memFun
    };

    int pl::test::Struct::*memObjPtr{ &pl::test::Struct::m_val };

    pl::test::Struct functor{ };

    auto lambda = [](int value) {
        pl::test::g_intVal += value;
    };

    pl::test::g_intVal = 0;

    SUBCASE("function_pointer_test") {
        const auto retVal = pl::forEachArgument(fp, 1, 2, 3, 4, 5);
        CHECK(pl::test::g_intVal == 15);
        CHECK(retVal == fp);
    }

    SUBCASE("member_function_pointer_test") {
        const auto retVal = pl::forEachArgument(
            memFunPtr, functor, &functor, pl::test::Struct{ });
        CHECK(pl::test::g_intVal == 3);
        CHECK(retVal == memFunPtr);
    }

    SUBCASE("member_object_pointer_test") {
        const auto retVal = pl::forEachArgument(
            memObjPtr, functor, &functor, pl::test::Struct{ });
        CHECK(pl::test::g_intVal == 0);
        CHECK(retVal == memObjPtr);
    }

    SUBCASE("functor_test") {
        const auto retVal = pl::forEachArgument(
            functor, 1, 2, 3);
        CHECK(pl::test::g_intVal == 6);
        CHECK(retVal.m_val == 6);
    }

    SUBCASE("lambda_test") {
        pl::forEachArgument(lambda, 4, 5, 6);
        CHECK(pl::test::g_intVal == 15);
    }
}
