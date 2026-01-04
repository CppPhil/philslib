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
#include "../../include/pl/for_each_argument.hpp" // pl::for_each_argument

namespace pl {
namespace test {
namespace {
int g_int_val{0};

void f(int v)
{
  g_int_val += v;
}
struct structure {
  void mem_fun() const
  {
    ++g_int_val;
  }
  void operator()(int v)
  {
    g_int_val += v;
    m_val = g_int_val;
  }

  int m_val = 0;
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("for_each_argument_test")
{
  void (*fp)(int){&pl::test::f};

  void (pl::test::structure::*mem_fun_ptr)()
    const {&pl::test::structure::mem_fun};

  int pl::test::structure::* mem_obj_ptr{&pl::test::structure::m_val};

  pl::test::structure functor{};

  auto lambda = [](int value) { pl::test::g_int_val += value; };

  pl::test::g_int_val = 0;

  SUBCASE("function_pointer_test")
  {
    const auto ret_val = pl::for_each_argument(fp, 1, 2, 3, 4, 5);
    CHECK(pl::test::g_int_val == 15);
    CHECK(ret_val == fp);
  }

  SUBCASE("member_function_pointer_test")
  {
    const auto ret_val = pl::for_each_argument(
      mem_fun_ptr, functor, &functor, pl::test::structure{});
    CHECK(pl::test::g_int_val == 3);
    CHECK(ret_val == mem_fun_ptr);
  }

  SUBCASE("member_object_pointer_test")
  {
    const auto ret_val = pl::for_each_argument(
      mem_obj_ptr, functor, &functor, pl::test::structure{});
    CHECK(pl::test::g_int_val == 0);
    CHECK(ret_val == mem_obj_ptr);
  }

  SUBCASE("functor_test")
  {
    const auto ret_val = pl::for_each_argument(functor, 1, 2, 3);
    CHECK(pl::test::g_int_val == 6);
    CHECK(ret_val.m_val == 6);
  }

  SUBCASE("lambda_test")
  {
    pl::for_each_argument(lambda, 4, 5, 6);
    CHECK(pl::test::g_int_val == 15);
  }
}
