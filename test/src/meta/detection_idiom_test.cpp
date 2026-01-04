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
#include "../../../include/pl/meta/detection_idiom.hpp" // pl::meta::nonesuch, pl::meta::is_detected, pl::meta::detected_t, pl::meta::detected_or, pl::meta::detected_or_t, pl::meta::is_detected_exact, pl::meta::is_detected_convertible
#include "../../include/static_assert.hpp"              // PL_TEST_STATIC_ASSERT
#include <cstddef>                                      // std::ptrdiff_t
#include <string>                                       // std::string
#include <type_traits> // std::is_same, std::true_type, std::false_type
#include <utility>     // std::declval
#include <vector>      // std::vector

namespace pl {
namespace test {
namespace {
template<typename Ty>
using copy_assign = decltype(std::declval<Ty&>() = std::declval<const Ty&>());

struct copy_assignable {
};

struct copy_assignable_weird_return_type {
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif // PL_COMPILER == PL_COMPILER_GCC
  void operator=(const copy_assignable_weird_return_type&)
  {
  }
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
};

struct not_copy_assignable {
  not_copy_assignable& operator=(const not_copy_assignable&) = delete;
};

template<typename Ty>
using nested_size_type = typename Ty::size_type;

template<typename Ty>
using nested_difference_type = typename Ty::difference_type;

struct has_diff_type {
  using difference_type = int;
};

struct has_no_diff_type {
};

template<typename Ty>
using difference_type
  = pl::meta::detected_or_t<std::ptrdiff_t, nested_difference_type, Ty>;
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("is_detected_test")
{
  PL_TEST_STATIC_ASSERT(
    pl::meta::is_detected<pl::test::copy_assign, pl::test::copy_assignable>::
      value);

  PL_TEST_STATIC_ASSERT(pl::meta::is_detected<
                        pl::test::copy_assign,
                        pl::test::copy_assignable_weird_return_type>::value);

  PL_TEST_STATIC_ASSERT(
    ! pl::meta::
      is_detected<pl::test::copy_assign, pl::test::not_copy_assignable>::value);

  PL_TEST_STATIC_ASSERT(
    pl::meta::is_detected<pl::test::nested_size_type, std::vector<double>>::
      value);

  PL_TEST_STATIC_ASSERT(! pl::meta::is_detected<
                        pl::test::nested_size_type,
                        pl::test::copy_assignable>::value);

  CHECK_UNARY(true);
}

TEST_CASE("detected_t_test")
{
  PL_TEST_STATIC_ASSERT(
    std::is_same<
      pl::meta::detected_t<pl::test::copy_assign, pl::test::copy_assignable>,
      pl::test::copy_assign<pl::test::copy_assignable>>::value);

  PL_TEST_STATIC_ASSERT(
    std::is_same<
      pl::meta::detected_t<
        pl::test::copy_assign,
        pl::test::copy_assignable_weird_return_type>,
      pl::test::copy_assign<pl::test::copy_assignable_weird_return_type>>::
      value);

  PL_TEST_STATIC_ASSERT(
    std::is_same<
      pl::meta::
        detected_t<pl::test::copy_assign, pl::test::not_copy_assignable>,
      pl::meta::nonesuch>::value);

  PL_TEST_STATIC_ASSERT(
    std::is_same<
      pl::meta::detected_t<pl::test::nested_size_type, std::vector<double>>,
      pl::test::nested_size_type<std::vector<double>>>::value);

  PL_TEST_STATIC_ASSERT(
    std::is_same<
      pl::meta::
        detected_t<pl::test::nested_size_type, pl::test::copy_assignable>,
      pl::meta::nonesuch>::value);

  CHECK_UNARY(true);
}

TEST_CASE("detected_or_test")
{
  PL_TEST_STATIC_ASSERT(std::is_same<
                        pl::meta::detected_or<
                          std::ptrdiff_t,
                          pl::test::nested_difference_type,
                          pl::test::has_diff_type>::value_t,
                        std::true_type>::value);

  PL_TEST_STATIC_ASSERT(
    std::is_same<
      pl::meta::detected_or<
        std::ptrdiff_t,
        pl::test::nested_difference_type,
        pl::test::has_diff_type>::type,
      pl::test::nested_difference_type<pl::test::has_diff_type>>::value);

  PL_TEST_STATIC_ASSERT(std::is_same<
                        pl::meta::detected_or<
                          std::ptrdiff_t,
                          pl::test::nested_difference_type,
                          pl::test::has_no_diff_type>::value_t,
                        std::false_type>::value);

  PL_TEST_STATIC_ASSERT(std::is_same<
                        pl::meta::detected_or<
                          std::ptrdiff_t,
                          pl::test::nested_difference_type,
                          pl::test::has_no_diff_type>::type,
                        std::ptrdiff_t>::value);

  CHECK_UNARY(true);
}

TEST_CASE("detected_or_t_test")
{
  PL_TEST_STATIC_ASSERT(
    std::is_same<pl::test::difference_type<pl::test::has_diff_type>, int>::
      value);

  PL_TEST_STATIC_ASSERT(std::is_same<
                        pl::test::difference_type<pl::test::has_no_diff_type>,
                        std::ptrdiff_t>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_detected_exact_test")
{
  PL_TEST_STATIC_ASSERT(pl::meta::is_detected_exact<
                        pl::test::copy_assignable&,
                        pl::test::copy_assign,
                        pl::test::copy_assignable>::value);

  PL_TEST_STATIC_ASSERT(! pl::meta::is_detected_exact<
                        pl::test::copy_assignable_weird_return_type&,
                        pl::test::copy_assign,
                        pl::test::copy_assignable_weird_return_type>::value);

  PL_TEST_STATIC_ASSERT(! pl::meta::is_detected_exact<
                        pl::test::not_copy_assignable&,
                        pl::test::copy_assign,
                        pl::test::not_copy_assignable>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_detected_convertible")
{
  struct DiffTypeConvertible {
    using difference_type = short;
  };

  struct DiffTypeNonConvertible {
    using difference_type = std::string;
  };

  PL_TEST_STATIC_ASSERT(pl::meta::is_detected_convertible<
                        int,
                        pl::test::nested_difference_type,
                        pl::test::has_diff_type>::value);

  PL_TEST_STATIC_ASSERT(pl::meta::is_detected_convertible<
                        int,
                        pl::test::nested_difference_type,
                        DiffTypeConvertible>::value);

  PL_TEST_STATIC_ASSERT(! pl::meta::is_detected_convertible<
                        int,
                        pl::test::nested_difference_type,
                        DiffTypeNonConvertible>::value);

  CHECK_UNARY(true);
}
