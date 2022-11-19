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
#endif                                       // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/as_ptr_const.hpp" // pl::as_ptr_const
#include "../include/static_assert.hpp"      // PL_TEST_STATIC_ASSERT
#include <ciso646>                           // not
#include <type_traits> // std::is_same, std::remove_pointer_t, std::is_const

namespace pl {
namespace test {
namespace {
class type {
public:
  int get() noexcept
  {
    return 1;
  }
  int get() const noexcept
  {
    return 2;
  }
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("as_ptr_const_with_nonconst_test")
{
  int        i{};
  int*       p1{&i};
  int* const p2{&i};

  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(pl::as_ptr_const(p1)), const int*>::value);
  PL_TEST_STATIC_ASSERT(
    not std::is_same<decltype(pl::as_ptr_const(p1)), int*>::value);
  CHECK(p1 == pl::as_ptr_const(p1));

  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(pl::as_ptr_const(p2)), const int*>::value);
  PL_TEST_STATIC_ASSERT(
    not std::is_same<decltype(pl::as_ptr_const(p2)), int* const>::value);
  CHECK(p2 == pl::as_ptr_const(p2));
}

TEST_CASE("as_ptr_const_with_const_test")
{
  int              i{};
  const int*       p1{&i};
  const int* const p2{&i};

  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(pl::as_ptr_const(p1)), const int*>::value);
  CHECK(p1 == pl::as_ptr_const(p1));

  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(pl::as_ptr_const(p2)), const int*>::value);
  PL_TEST_STATIC_ASSERT(
    not std::is_same<decltype(pl::as_ptr_const(p2)), const int* const>::value);
  CHECK(p2 == pl::as_ptr_const(p2));
}

TEST_CASE("as_ptr_const_is_low_level_const_qualified_test")
{
  int        i{};
  int*       p1{&i};
  const int* p2{&i};

  PL_TEST_STATIC_ASSERT(
    std::is_const<
      std::remove_pointer_t<decltype(pl::as_ptr_const(p1))>>::value);
  PL_TEST_STATIC_ASSERT(
    std::is_const<
      std::remove_pointer_t<decltype(pl::as_ptr_const(p2))>>::value);

  PL_TEST_STATIC_ASSERT(
    not std::is_const<decltype(pl::as_ptr_const(p1))>::value);
  PL_TEST_STATIC_ASSERT(
    not std::is_const<decltype(pl::as_ptr_const(p2))>::value);

  CHECK(&i == pl::as_ptr_const(p1));
  CHECK(&i == pl::as_ptr_const(p2));
}

TEST_CASE("as_ptr_const_overload_test")
{
  pl::test::type  obj{};
  pl::test::type* ptr{&obj};

  CHECK(ptr->get() == 1);
  CHECK(pl::as_ptr_const(ptr)->get() == 2);
  CHECK(pl::as_ptr_const(&obj)->get() == 2);
}

TEST_CASE("as_ptr_const_constexpr_test")
{
  static constexpr void* p{nullptr};
  PL_TEST_STATIC_ASSERT(pl::as_ptr_const(p) == nullptr);

  CHECK_UNARY(true);
}
