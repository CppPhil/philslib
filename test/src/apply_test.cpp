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
#endif                                // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/apply.hpp" // pl::apply
#include <string>                     // std::string
#include <tuple>                      // std::make_tuple

namespace pl {
namespace test {
namespace {
int nullary_function() noexcept { return 5; }
int unary_function(int i) noexcept { return i * 2; }
template <typename Ty>
Ty unary_function_template(Ty ty)
{
    return ty;
}

class type {
public:
    explicit type(int i) noexcept : data{i} {}
    int               nullary_mem_fun() const noexcept { return 5; }
    int unary_mem_fun(int i) const noexcept { return 7 + i; }
    template <typename Ty>
    Ty unary_mem_fun_template(Ty ty) const
    {
        return ty;
    }

    int data;
};

struct nullary_functor {
    int operator()() const noexcept { return 27; }
};

struct unary_functor {
    int operator()(int i) const noexcept { return i / 2; }
};

struct generic_functor {
    template <typename Ty>
    Ty operator()(Ty ty) const
    {
        return ty;
    }
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("apply_test")
{
    const pl::test::type        obj{20};
    const pl::test::type* const ptr{&obj};

    const auto nullary_lambda = [] { return 50; };
    const auto unary_lambda   = [](int i) { return i * i; };
    const auto generic_lambda = [](auto val) { return val * 5; };

    SUBCASE("function_pointers")
    {
        CHECK(pl::apply(&pl::test::nullary_function, std::make_tuple()) == 5);
        CHECK(pl::apply(&pl::test::unary_function, std::make_tuple(3)) == 6);
        CHECK(
            pl::apply(
                &pl::test::unary_function_template<int>, std::make_tuple(4))
            == 4);
    }

    SUBCASE("member_function_pointers")
    {
        CHECK(
            pl::apply(&pl::test::type::nullary_mem_fun, std::make_tuple(obj))
            == 5);
        CHECK(
            pl::apply(&pl::test::type::nullary_mem_fun, std::make_tuple(ptr))
            == 5);
        CHECK(
            pl::apply(&pl::test::type::unary_mem_fun, std::make_tuple(obj, 3))
            == 10);
        CHECK(
            pl::apply(&pl::test::type::unary_mem_fun, std::make_tuple(ptr, 3))
            == 10);
        CHECK(
            pl::apply(
                &pl::test::type::unary_mem_fun_template<int>,
                std::make_tuple(obj, 4))
            == 4);
        CHECK(
            pl::apply(
                &pl::test::type::unary_mem_fun_template<int>,
                std::make_tuple(ptr, 4))
            == 4);
    }

    SUBCASE("member_object_pointer")
    {
        CHECK(pl::apply(&pl::test::type::data, std::make_tuple(obj)) == 20);
        CHECK(pl::apply(&pl::test::type::data, std::make_tuple(ptr)) == 20);
    }

    SUBCASE("functors")
    {
        CHECK(pl::apply(pl::test::nullary_functor{}, std::make_tuple()) == 27);
        CHECK(pl::apply(pl::test::unary_functor{}, std::make_tuple(4)) == 2);
        CHECK(
            pl::apply(
                pl::test::generic_functor{},
                std::make_tuple(std::string{"text"}))
            == "text");
    }

    SUBCASE("lambdas")
    {
        CHECK(pl::apply(nullary_lambda, std::make_tuple()) == 50);
        CHECK(pl::apply(unary_lambda, std::make_tuple(5)) == 25);
        CHECK(pl::apply(generic_lambda, std::make_tuple(20)) == 100);
    }
}
