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

#include "../../../include/pl/compiler.hpp"
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/meta/bool_constant.hpp" // pl::meta::bool_constant
#include "../../include/static_assert.hpp"            // PL_TEST_STATIC_ASSERT
#include <type_traits> // std::true_type, std::false_type, std::is_same

TEST_CASE("bool_constant_type_test")
{
  PL_TEST_STATIC_ASSERT(
    std::is_same<pl::meta::bool_constant<true>, std::true_type>::value);
  PL_TEST_STATIC_ASSERT(
    std::is_same<pl::meta::bool_constant<false>, std::false_type>::value);
  PL_TEST_STATIC_ASSERT(
    std::is_same<pl::meta::bool_constant<true>::type, std::true_type>::value);
  PL_TEST_STATIC_ASSERT(
    std::is_same<pl::meta::bool_constant<false>::type, std::false_type>::value);

  CHECK_UNARY(true);
}

TEST_CASE("bool_constant_value_type_test")
{
  PL_TEST_STATIC_ASSERT(
    std::is_same<pl::meta::bool_constant<true>::value_type, bool>::value);
  PL_TEST_STATIC_ASSERT(
    std::is_same<pl::meta::bool_constant<false>::value_type, bool>::value);

  CHECK_UNARY(true);
}

TEST_CASE("bool_constant_value_test")
{
  PL_TEST_STATIC_ASSERT(pl::meta::bool_constant<true>::value);
  PL_TEST_STATIC_ASSERT(not pl::meta::bool_constant<false>::value);

  CHECK_UNARY(true);
}

TEST_CASE("bool_constant_operator_test")
{
  PL_TEST_STATIC_ASSERT(static_cast<bool>(pl::meta::bool_constant<true>{}));
  PL_TEST_STATIC_ASSERT(
    not static_cast<bool>(pl::meta::bool_constant<false>{}));

  PL_TEST_STATIC_ASSERT(pl::meta::bool_constant<true>{}());
  PL_TEST_STATIC_ASSERT(not pl::meta::bool_constant<false>{}());

  CHECK_UNARY(true);
}
