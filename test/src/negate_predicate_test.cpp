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
#include "../../include/pl/algo/ranged_algorithms.hpp" // pl::all_of
#include "../../include/pl/negate_predicate.hpp"       // pl::negatePredicate
#include <cstring>                                     // std::strchr
#include <vector>                                      // std::vector

namespace pl {
namespace test {
namespace {
bool is5(int i) { return i == 5; }
class type {
public:
    explicit type(bool v) : m_v{v} {}
    bool memFun(const char* s) const { return std::strchr(s, 'a') != nullptr; }
    bool                    m_v;
};

class Functor {
public:
    bool operator()(int a, int b) const { return a != b; }
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("negate_predicate_function_pointer_test")
{
    auto        fp = &pl::test::is5;
    auto&       r  = fp;
    const auto& cr = fp;

    CHECK_UNARY_FALSE(pl::negatePredicate(r)(5));
    CHECK_UNARY(pl::negatePredicate(r)(4));

    CHECK_UNARY_FALSE(pl::negatePredicate(cr)(5));
    CHECK_UNARY(pl::negatePredicate(cr)(4));
}

TEST_CASE("negate_predicate_member_function_pointer_test")
{
    auto        memFunPtr = &pl::test::type::memFun;
    auto&       r         = memFunPtr;
    const auto& cr        = memFunPtr;

    pl::test::type  obj{true};
    pl::test::type* pObj{&obj};

    CHECK_UNARY(pl::negatePredicate(r)(obj, "bcdef"));
    CHECK_UNARY_FALSE(pl::negatePredicate(r)(obj, "thoetnineuaieui"));
    CHECK_UNARY(pl::negatePredicate(cr)(obj, "bcdef"));
    CHECK_UNARY_FALSE(pl::negatePredicate(cr)(obj, "ueoutihaiii"));

    CHECK_UNARY(pl::negatePredicate(r)(pObj, "bcdef"));
    CHECK_UNARY_FALSE(pl::negatePredicate(r)(pObj, "thoetnineuaieui"));
    CHECK_UNARY(pl::negatePredicate(cr)(pObj, "bcdef"));
    CHECK_UNARY_FALSE(pl::negatePredicate(cr)(pObj, "ueoutihaiii"));
}

TEST_CASE("negate_predicate_member_object_pointer_test")
{
    auto        memObjPtr = &pl::test::type::m_v;
    auto&       r         = memObjPtr;
    const auto& cr        = memObjPtr;

    pl::test::type  obj1{false};
    pl::test::type* pObj1{&obj1};

    pl::test::type  obj2{true};
    pl::test::type* pObj2{&obj2};

    CHECK_UNARY(pl::negatePredicate(r)(obj1));
    CHECK_UNARY_FALSE(pl::negatePredicate(r)(obj2));
    CHECK_UNARY(pl::negatePredicate(cr)(obj1));
    CHECK_UNARY_FALSE(pl::negatePredicate(cr)(obj2));

    CHECK_UNARY(pl::negatePredicate(r)(pObj1));
    CHECK_UNARY_FALSE(pl::negatePredicate(r)(pObj2));
    CHECK_UNARY(pl::negatePredicate(cr)(pObj1));
    CHECK_UNARY_FALSE(pl::negatePredicate(cr)(pObj2));
}

TEST_CASE("negate_predicate_functor_test")
{
    pl::test::Functor        functor{};
    pl::test::Functor&       r{functor};
    const pl::test::Functor& cr{functor};

    CHECK_UNARY(pl::negatePredicate(r)(5, 5));
    CHECK_UNARY_FALSE(pl::negatePredicate(r)(5, 6));

    CHECK_UNARY(pl::negatePredicate(cr)(5, 5));
    CHECK_UNARY_FALSE(pl::negatePredicate(cr)(5, 6));
}

TEST_CASE("negate_predicate_lambda_test")
{
    auto l             = [](int i) { return i > 5; };
    auto&           r  = l;
    const auto&     cr = l;

    const std::vector<int> vec1{1, 2, 3, 4, 5};
    const std::vector<int> vec2{2, 3, 4, 5, 6};

    CHECK_UNARY(pl::algo::all_of(vec1, pl::negatePredicate(r)));
    CHECK_UNARY_FALSE(pl::algo::all_of(vec2, pl::negatePredicate(r)));

    CHECK_UNARY(pl::algo::all_of(vec1, pl::negatePredicate(cr)));
    CHECK_UNARY_FALSE(pl::algo::all_of(vec2, pl::negatePredicate(cr)));
}
