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
#include "../../../include/pl/meta/is_reference_wrapper.hpp" // pl::meta::is_reference_wrapper, pl::meta::is_not_reference_wrapper
#include "../../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include <unordered_map>                   // std::unordered_map

TEST_CASE("is_reference_wrapper_positive_test")
{
  using ty1 = std::reference_wrapper<int>;
  using ty2 = std::reference_wrapper<double>;
  using ty3 = std::reference_wrapper<float>;
  using ty4 = std::reference_wrapper<long long>;

  PL_TEST_STATIC_ASSERT(pl::meta::is_reference_wrapper<ty1>::value);
  PL_TEST_STATIC_ASSERT(!pl::meta::is_not_reference_wrapper<ty1>::value);

  PL_TEST_STATIC_ASSERT(pl::meta::is_reference_wrapper<ty2>::value);
  PL_TEST_STATIC_ASSERT(!pl::meta::is_not_reference_wrapper<ty2>::value);

  PL_TEST_STATIC_ASSERT(pl::meta::is_reference_wrapper<ty3>::value);
  PL_TEST_STATIC_ASSERT(!pl::meta::is_not_reference_wrapper<ty3>::value);

  PL_TEST_STATIC_ASSERT(pl::meta::is_reference_wrapper<ty4>::value);
  PL_TEST_STATIC_ASSERT(!pl::meta::is_not_reference_wrapper<ty4>::value);

  CHECK_UNARY(true);
}

TEST_CASE("is_reference_wrapper_negative_test")
{
  using ty1 = unsigned long long;
  using ty2 = wchar_t;
  using ty3 = short;
  using ty4 = std::unordered_map<int, const char*>;

  PL_TEST_STATIC_ASSERT(!pl::meta::is_reference_wrapper<ty1>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_not_reference_wrapper<ty1>::value);

  PL_TEST_STATIC_ASSERT(!pl::meta::is_reference_wrapper<ty2>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_not_reference_wrapper<ty2>::value);

  PL_TEST_STATIC_ASSERT(!pl::meta::is_reference_wrapper<ty3>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_not_reference_wrapper<ty3>::value);

  PL_TEST_STATIC_ASSERT(!pl::meta::is_reference_wrapper<ty4>::value);
  PL_TEST_STATIC_ASSERT(pl::meta::is_not_reference_wrapper<ty4>::value);

  CHECK_UNARY(true);
}
