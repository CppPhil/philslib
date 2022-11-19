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
#include "../../../include/pl/meta/iterator_traits.hpp" // pl::meta::is_output_iterator, pl::meta::is_random_access_iterator, pl::meta::is_bidirectional_iterator, pl::meta::is_forward_iterator, pl::meta::is_input_iterator
#include "../../include/static_assert.hpp"              // PL_TEST_STATIC_ASSERT
#include <ciso646>                                      // not
#include <forward_list>                                 // std::forward_list
#include <iterator> // std::ostream_iterator, std::istream_iterator
#include <list>     // std::list
#include <vector>   // std::vector

namespace pl {
namespace test {
namespace {
using oi1    = std::ostream_iterator<int>;
using ra1    = unsigned char*;
using ra2    = std::vector<float>::const_iterator;
using bidi1  = std::list<int>::const_iterator;
using fw1    = std::forward_list<std::vector<double>>::iterator;
using in_it1 = std::istream_iterator<unsigned long>;
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("is_output_iterator_positive_test")
{
  PL_TEST_STATIC_ASSERT(pl::meta::is_output_iterator<pl::test::oi1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_output_iterator_negative_test")
{
  PL_TEST_STATIC_ASSERT(not pl::meta::is_output_iterator<pl::test::ra1>::value);
  PL_TEST_STATIC_ASSERT(not pl::meta::is_output_iterator<pl::test::ra2>::value);
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_output_iterator<pl::test::bidi1>::value);
  PL_TEST_STATIC_ASSERT(not pl::meta::is_output_iterator<pl::test::fw1>::value);
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_output_iterator<pl::test::in_it1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_random_access_iterator_positive_test")
{
  PL_TEST_STATIC_ASSERT(
    pl::meta::is_random_access_iterator<pl::test::ra1>::value);
  PL_TEST_STATIC_ASSERT(
    pl::meta::is_random_access_iterator<pl::test::ra1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_random_access_iterator_negative_test")
{
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_random_access_iterator<pl::test::oi1>::value);
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_random_access_iterator<pl::test::bidi1>::value);
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_random_access_iterator<pl::test::fw1>::value);
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_random_access_iterator<pl::test::in_it1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_bidirectional_iterator_positive_test")
{
  PL_TEST_STATIC_ASSERT(
    pl::meta::is_bidirectional_iterator<pl::test::ra1>::value);
  PL_TEST_STATIC_ASSERT(
    pl::meta::is_bidirectional_iterator<pl::test::ra2>::value);
  PL_TEST_STATIC_ASSERT(
    pl::meta::is_bidirectional_iterator<pl::test::bidi1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_bidirectional_iterator_negative_test")
{
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_bidirectional_iterator<pl::test::oi1>::value);
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_bidirectional_iterator<pl::test::fw1>::value);
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_bidirectional_iterator<pl::test::in_it1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_forward_iterator_positive_test")
{
  PL_TEST_STATIC_ASSERT(pl::meta::is_forward_iterator<pl::test::ra1>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_forward_iterator<pl::test::ra2>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_forward_iterator<pl::test::bidi1>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_forward_iterator<pl::test::fw1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_forward_iterator_negative_test")
{
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_forward_iterator<pl::test::oi1>::value);
  PL_TEST_STATIC_ASSERT(
    not pl::meta::is_forward_iterator<pl::test::in_it1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_input_iterator_positive_test")
{
  PL_TEST_STATIC_ASSERT(pl::meta::is_input_iterator<pl::test::ra1>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_input_iterator<pl::test::ra2>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_input_iterator<pl::test::bidi1>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_input_iterator<pl::test::fw1>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_input_iterator<pl::test::in_it1>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_input_iterator_negative_test")
{
  PL_TEST_STATIC_ASSERT(not pl::meta::is_input_iterator<pl::test::oi1>::value);

  CHECK_UNARY(true);
}
