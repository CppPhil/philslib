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
#include "../../include/pl/total_order.hpp" // PL_TOTAL_ORDER
#include "../include/static_assert.hpp"     // PL_TEST_STATIC_ASSERT

namespace pl {
namespace test {
namespace {
struct t1 {
  int i;

  constexpr friend bool operator<(t1 lhs, t1 rhs)
  {
    return lhs.i < rhs.i;
  }

  constexpr friend bool operator==(t1 lhs, t1 rhs)
  {
    return lhs.i == rhs.i;
  }
};

PL_TOTAL_ORDER_CONSTEXPR(t1)

struct t2 {
  int i;

  friend bool operator<(t2 lhs, t2 rhs)
  {
    return lhs.i < rhs.i;
  }

  friend bool operator==(t2 lhs, t2 rhs)
  {
    return lhs.i == rhs.i;
  }
};

PL_TOTAL_ORDER(t2)
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("total_order_test")
{
  constexpr pl::test::t1 a1{5};
  constexpr pl::test::t1 b1{6};

  PL_TEST_STATIC_ASSERT(a1 < b1);
  PL_TEST_STATIC_ASSERT(a1 == a1);
  PL_TEST_STATIC_ASSERT(a1 != b1);
  PL_TEST_STATIC_ASSERT(b1 > a1);
  PL_TEST_STATIC_ASSERT(a1 <= a1);
  PL_TEST_STATIC_ASSERT(a1 <= b1);
  PL_TEST_STATIC_ASSERT(b1 >= b1);
  PL_TEST_STATIC_ASSERT(b1 >= a1);

  const pl::test::t2 a2{5};
  const pl::test::t2 b2{6};

  CHECK_UNARY(a2 < b2);
  CHECK_UNARY(a2 == a2);
  CHECK_UNARY(a2 != b2);
  CHECK_UNARY(b2 > a2);
  CHECK_UNARY(a2 <= a2);
  CHECK_UNARY(a2 <= b2);
  CHECK_UNARY(b2 >= b2);
  CHECK_UNARY(b2 >= a2);
}
