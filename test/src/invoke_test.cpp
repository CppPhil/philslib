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
#include "../../include/pl/invoke.hpp" // pl::invoke
#include <cstdint>                     // std::uint64_t
#include <functional>                  // std::bind

namespace pl {
namespace test {
namespace {
std::uint64_t f(std::uint64_t v, std::uint64_t multiplier)
{
    return v * multiplier;
}

std::uint64_t f(std::uint64_t v) { return f(v, 2U); }
class test_class {
public:
    explicit test_class(std::uint64_t v) : m_v{v} {}
    std::uint64_t mem_fun(std::uint64_t v) const { return f(v, m_v); }
    std::uint64_t m_v;
};

class functor {
public:
    std::uint64_t operator()(std::uint64_t v) const { return f(v); }
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("invoke_test_function_pointer")
{
    static constexpr std::uint64_t arg{5U};
    static constexpr std::uint64_t expected{10U};

    std::uint64_t (*fp)(std::uint64_t){&pl::test::f};

    CHECK(pl::invoke(fp, arg) == expected);
}

TEST_CASE("invoke_test_member_function_pointer")
{
    static constexpr std::uint64_t arg{7U};
    static constexpr std::uint64_t multiplier{3U};
    static constexpr std::uint64_t expected{21U};

    std::uint64_t (pl::test::test_class::*member_function_pointer)(
        std::uint64_t) const {&pl::test::test_class::mem_fun};

    pl::test::test_class  object{multiplier};
    pl::test::test_class* p_object{&object};

    CHECK(pl::invoke(member_function_pointer, object, arg) == expected);
    CHECK(pl::invoke(member_function_pointer, p_object, arg) == expected);
}

TEST_CASE("invoke_test_member_object_pointer")
{
    static constexpr std::uint64_t v{5U};

    std::uint64_t pl::test::test_class::*member_object_pointer{
        &pl::test::test_class::m_v};

    pl::test::test_class  object{v};
    pl::test::test_class* p_object{&object};

    CHECK(pl::invoke(member_object_pointer, object) == v);
    CHECK(pl::invoke(member_object_pointer, p_object) == v);
}

TEST_CASE("invoke_test_functor")
{
    using binary_function_pointer
        = std::uint64_t (*)(std::uint64_t, std::uint64_t);

    pl::test::functor functor{};
    const auto        lambda = [](std::uint64_t v) { return v * 5U; };
    const auto        bind   = std::bind(
        static_cast<binary_function_pointer>(&pl::test::f),
        std::placeholders::_1,
        25U);

    CHECK(pl::invoke(functor, 7U) == 14U);
    CHECK(pl::invoke(lambda, 50U) == 250U);
    CHECK(pl::invoke(bind, 3U) == 75U);
}
