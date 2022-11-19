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
#include "../../../include/pl/cont/to_array.hpp" // pl::cont::to_array
#include "../../include/static_assert.hpp"       // PL_TEST_STATIC_ASSERT
#include <cstring>                               // std::strcmp
#include <memory>                                // std::make_unique
#include <string>                                // std::string
#include <type_traits>                           // std::is_same

TEST_CASE("to_array_general_test")
{
  int          c_array1[]{1, 2, 3, 4, 5};
  const double c_array2[]{1.1, 2.2, 3.3};

  auto       array1 = pl::cont::to_array(c_array1);
  const auto array2 = pl::cont::to_array(c_array2);

  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(array1), std::array<int, 5U>>::value);
  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(array2), const std::array<double, 3U>>::value);

  REQUIRE(array1.size() == 5U);
  CHECK(array1[0U] == 1);
  CHECK(array1[1U] == 2);
  CHECK(array1[2U] == 3);
  CHECK(array1[3U] == 4);
  CHECK(array1[4U] == 5);

  REQUIRE(array2.size() == 3U);
  CHECK(array2[0U] == doctest::Approx(1.1));
  CHECK(array2[1U] == doctest::Approx(2.2));
  CHECK(array2[2U] == doctest::Approx(3.3));
}

TEST_CASE("to_array_one_element_test")
{
  const std::string c_array[]{std::string{"Hello World"}};

  const auto array = pl::cont::to_array(c_array);

  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(array), const std::array<std::string, 1U>>::value);

  REQUIRE(array.size() == 1U);
  CHECK(array[0U] == std::string{"Hello World"});
}

TEST_CASE("to_array_constexpr_test")
{
  static constexpr int  a[]{1, 2, 3, 4, 5};
  static constexpr auto std_array = pl::cont::to_array(a);
  PL_TEST_STATIC_ASSERT(std_array[0U] == 1);
  PL_TEST_STATIC_ASSERT(std_array[1U] == 2);
  PL_TEST_STATIC_ASSERT(std_array[2U] == 3);
  PL_TEST_STATIC_ASSERT(std_array[3U] == 4);
  PL_TEST_STATIC_ASSERT(std_array[4U] == 5);

  CHECK_UNARY(true);
}

TEST_CASE("to_array_c_string_literal_test")
{
  const auto stdArray1 = pl::cont::to_array("test");
  const auto stdArray2 = pl::cont::to_array("");

  REQUIRE(stdArray1.size() == 5U);
  CHECK(std::strcmp(stdArray1.data(), "test") == 0);

  REQUIRE(stdArray2.size() == 1U);
  CHECK(stdArray2.front() == '\0');
}

#if PL_COMPILER != PL_COMPILER_MSVC
TEST_CASE("to_array_rvalue_test")
{
  const auto stdArray1 = pl::cont::to_array({1, 2, 3});
  const auto stdArray2 = pl::cont::to_array({std::make_unique<int>(20)});

  REQUIRE(stdArray1.size() == 3U);
  CHECK(stdArray1[0U] == 1);
  CHECK(stdArray1[1U] == 2);
  CHECK(stdArray1[2U] == 3);

  REQUIRE(stdArray2.size() == 1U);
  CHECK(*(stdArray2.front()) == 20);
}
#endif // PL_COMPILER != PL_COMPILER_MSVC
