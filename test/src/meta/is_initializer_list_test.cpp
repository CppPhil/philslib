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
#include "../../../include/pl/meta/is_initializer_list.hpp" // pl::meta::is_initializer_list
#include "../../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include <initializer_list>                // std::initializer_list
#include <string>                          // std::string
#include <vector>                          // std::vector

namespace pl {
namespace test {
namespace {
using ty1 = std::initializer_list<int>;
using ty2 = std::initializer_list<double>;
using ty3 = std::initializer_list<std::string>;
using ty4 = std::string;
using ty5 = int;
using ty6 = std::vector<std::string>;
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("is_initializer_list_positive_tests")
{
  PL_TEST_STATIC_ASSERT(pl::meta::is_initializer_list<pl::test::ty1>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_initializer_list<pl::test::ty2>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_initializer_list<pl::test::ty3>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_initializer_list_negative_tests")
{
  PL_TEST_STATIC_ASSERT(!pl::meta::is_initializer_list<pl::test::ty4>::value);
  PL_TEST_STATIC_ASSERT(!pl::meta::is_initializer_list<pl::test::ty5>::value);
  PL_TEST_STATIC_ASSERT(!pl::meta::is_initializer_list<pl::test::ty6>::value);

  CHECK_UNARY(true);
}
