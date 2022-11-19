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
#endif                                  // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/numeric.hpp" // pl::is_even, pl::is_odd, pl::is_between
#include "../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include <ciso646>                      // not

TEST_CASE("is_even_test")
{
  CHECK_UNARY(pl::is_even(-2));
  CHECK_UNARY_FALSE(pl::is_even(-1));
  CHECK_UNARY(pl::is_even(0));
  CHECK_UNARY_FALSE(pl::is_even(1));

  PL_TEST_STATIC_ASSERT(pl::is_even(-2));
  PL_TEST_STATIC_ASSERT(not pl::is_even(-1));
  PL_TEST_STATIC_ASSERT(pl::is_even(0));
  PL_TEST_STATIC_ASSERT(not pl::is_even(1));
}

TEST_CASE("is_odd_test")
{
  CHECK_UNARY_FALSE(pl::is_odd(-2));
  CHECK_UNARY(pl::is_odd(-1));
  CHECK_UNARY_FALSE(pl::is_odd(0));
  CHECK_UNARY(pl::is_odd(1));

  PL_TEST_STATIC_ASSERT(not pl::is_odd(-2));
  PL_TEST_STATIC_ASSERT(pl::is_odd(-1));
  PL_TEST_STATIC_ASSERT(not pl::is_odd(0));
  PL_TEST_STATIC_ASSERT(pl::is_odd(1));
}

TEST_CASE("is_between_test")
{
  CHECK_UNARY(pl::is_between(5, 5, 5));
  CHECK_UNARY(pl::is_between(5, 4, 5));
  CHECK_UNARY(pl::is_between(5, 5, 6));
  CHECK_UNARY(pl::is_between(5, 4, 6));

  CHECK_UNARY(pl::is_between(0, 0, 0));
  CHECK_UNARY(pl::is_between(0, -1, 0));
  CHECK_UNARY(pl::is_between(0, 0, 1));
  CHECK_UNARY(pl::is_between(0, -1, 1));

  CHECK_UNARY_FALSE(pl::is_between(5, 6, 6));

  PL_TEST_STATIC_ASSERT(pl::is_between(5, 5, 5));
  PL_TEST_STATIC_ASSERT(pl::is_between(5, 4, 5));
  PL_TEST_STATIC_ASSERT(pl::is_between(5, 5, 6));
  PL_TEST_STATIC_ASSERT(pl::is_between(5, 4, 6));

  PL_TEST_STATIC_ASSERT(pl::is_between(0, 0, 0));
  PL_TEST_STATIC_ASSERT(pl::is_between(0, -1, 0));
  PL_TEST_STATIC_ASSERT(pl::is_between(0, 0, 1));
  PL_TEST_STATIC_ASSERT(pl::is_between(0, -1, 1));

  PL_TEST_STATIC_ASSERT(not pl::is_between(5, 6, 6));
}
