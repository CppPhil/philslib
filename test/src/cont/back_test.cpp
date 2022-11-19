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
#endif                                       // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/cont/back.hpp" // pl::cont::back
#include "../../include/static_assert.hpp"   // PL_TEST_STATIC_ASSERT
#include <array>                             // std::array
#include <cstddef>                           // std::size_t
#include <deque>                             // std::deque
#include <initializer_list>                  // std::initializer_list
#include <list>                              // std::list
#include <queue>                             // std::queue
#include <string> // std::string, std::literals::string_literals::operator""s
#include <type_traits> // std::is_same
#include <vector>      // std::vector

TEST_CASE("std_array_back_test")
{
  static constexpr std::size_t size{5U};
  const std::array<int, size>  array{{1, 2, 3, 4, 5}};
  CHECK(pl::cont::back(array) == 5);
}

TEST_CASE("std_vector_back_test")
{
  const std::vector<int> v{1, 2, 3};
  CHECK(pl::cont::back(v) == 3);
}

TEST_CASE("std_deque_back_test")
{
  const std::deque<int> deque{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  CHECK(pl::cont::back(deque) == 9);
}

TEST_CASE("std_list_back_test")
{
  const std::list<int> list{1, 2, 3, 4, 5};
  CHECK(pl::cont::back(list) == 5);
}

TEST_CASE("c_array_back_test")
{
  const int  c_array[]  = {1, 2, 3, 4, 5, 6, 7};
  const char c_string[] = "Text";
  CHECK(pl::cont::back(c_array) == 7);
  CHECK(pl::cont::back(c_string) == '\0');
}

TEST_CASE("std_queue_back_test")
{
  std::queue<int> queue{};
  queue.push(1);
  queue.push(2);
  queue.push(3);
  CHECK(pl::cont::back(queue) == 3);
}

TEST_CASE("std_string_back_test")
{
  const std::string string{"Hello World!"};
  CHECK(pl::cont::back(string) == '!');
}

TEST_CASE("initializer_list_test")
{
  using namespace std::literals::string_literals;

  std::initializer_list<int>               il{1, 2, 3, 4, 5};
  const std::initializer_list<std::string> il2{"text"s};

  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(pl::cont::back(il)), const int&>::value);
  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(pl::cont::back(il2)), const std::string&>::value);

  CHECK(pl::cont::back(il) == 5);
  CHECK(pl::cont::back(il2) == "text"s);
}

TEST_CASE("back_constexpr_array_test")
{
  static constexpr int a[]{1, 2, 3};
  PL_TEST_STATIC_ASSERT(pl::cont::back(a) == 3);

  CHECK_UNARY(true);
}

#if (PL_COMPILER != PL_COMPILER_GCC) \
  || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(6, 4, 0))
TEST_CASE("back_constexpr_std_array_test")
{
  static constexpr std::array<int, 5U> a{{1, 2, 3, 4, 5}};
  PL_TEST_STATIC_ASSERT(pl::cont::back(a) == 5);

  CHECK_UNARY(true);
}
#endif

#if PL_COMPILER == PL_COMPILER_GCC
TEST_CASE("back_constexpr_initializer_list_test")
{
  static constexpr std::initializer_list<int> il{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  PL_TEST_STATIC_ASSERT(pl::cont::back(il) == 10);

  CHECK_UNARY(true);
}
#endif
