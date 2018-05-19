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
#include "../../include/pl/negate_predicate.hpp"       // pl::negate_predicate
#include <cstring>                                     // std::strchr
#include <vector>                                      // std::vector

namespace pl {
namespace test {
namespace {
bool is_5(int i) { return i == 5; }
class type {
public:
    explicit type(bool v) : m_v{v} {}
    bool mem_fun(const char* s) const { return std::strchr(s, 'a') != nullptr; }
    bool                     m_v;
};

class functor {
public:
    bool operator()(int a, int b) const { return a != b; }
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("negate_predicate_function_pointer_test")
{
    auto        fp = &pl::test::is_5;
    auto&       r  = fp;
    const auto& cr = fp;

    CHECK_UNARY_FALSE(pl::negate_predicate(r)(5));
    CHECK_UNARY(pl::negate_predicate(r)(4));

    CHECK_UNARY_FALSE(pl::negate_predicate(cr)(5));
    CHECK_UNARY(pl::negate_predicate(cr)(4));
}

TEST_CASE("negate_predicate_member_function_pointer_test")
{
    auto        mem_fun_ptr = &pl::test::type::mem_fun;
    auto&       r           = mem_fun_ptr;
    const auto& cr          = mem_fun_ptr;

    pl::test::type  obj{true};
    pl::test::type* p_obj{&obj};

    CHECK_UNARY(pl::negate_predicate(r)(obj, "bcdef"));
    CHECK_UNARY_FALSE(pl::negate_predicate(r)(obj, "thoetnineuaieui"));
    CHECK_UNARY(pl::negate_predicate(cr)(obj, "bcdef"));
    CHECK_UNARY_FALSE(pl::negate_predicate(cr)(obj, "ueoutihaiii"));

    CHECK_UNARY(pl::negate_predicate(r)(p_obj, "bcdef"));
    CHECK_UNARY_FALSE(pl::negate_predicate(r)(p_obj, "thoetnineuaieui"));
    CHECK_UNARY(pl::negate_predicate(cr)(p_obj, "bcdef"));
    CHECK_UNARY_FALSE(pl::negate_predicate(cr)(p_obj, "ueoutihaiii"));
}

TEST_CASE("negate_predicate_member_object_pointer_test")
{
    auto        mem_obj_ptr = &pl::test::type::m_v;
    auto&       r           = mem_obj_ptr;
    const auto& cr          = mem_obj_ptr;

    pl::test::type  obj1{false};
    pl::test::type* p_obj1{&obj1};

    pl::test::type  obj2{true};
    pl::test::type* p_obj2{&obj2};

    CHECK_UNARY(pl::negate_predicate(r)(obj1));
    CHECK_UNARY_FALSE(pl::negate_predicate(r)(obj2));
    CHECK_UNARY(pl::negate_predicate(cr)(obj1));
    CHECK_UNARY_FALSE(pl::negate_predicate(cr)(obj2));

    CHECK_UNARY(pl::negate_predicate(r)(p_obj1));
    CHECK_UNARY_FALSE(pl::negate_predicate(r)(p_obj2));
    CHECK_UNARY(pl::negate_predicate(cr)(p_obj1));
    CHECK_UNARY_FALSE(pl::negate_predicate(cr)(p_obj2));
}

TEST_CASE("negate_predicate_functor_test")
{
    pl::test::functor        functor{};
    pl::test::functor&       r{functor};
    const pl::test::functor& cr{functor};

    CHECK_UNARY(pl::negate_predicate(r)(5, 5));
    CHECK_UNARY_FALSE(pl::negate_predicate(r)(5, 6));

    CHECK_UNARY(pl::negate_predicate(cr)(5, 5));
    CHECK_UNARY_FALSE(pl::negate_predicate(cr)(5, 6));
}

TEST_CASE("negate_predicate_lambda_test")
{
    auto l             = [](int i) { return i > 5; };
    auto&           r  = l;
    const auto&     cr = l;

    const std::vector<int> vec1{1, 2, 3, 4, 5};
    const std::vector<int> vec2{2, 3, 4, 5, 6};

    CHECK_UNARY(pl::algo::all_of(vec1, pl::negate_predicate(r)));
    CHECK_UNARY_FALSE(pl::algo::all_of(vec2, pl::negate_predicate(r)));

    CHECK_UNARY(pl::algo::all_of(vec1, pl::negate_predicate(cr)));
    CHECK_UNARY_FALSE(pl::algo::all_of(vec2, pl::negate_predicate(cr)));
}
