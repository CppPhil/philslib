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
#endif                                 // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/assert.hpp" // PL_CHECK_PRE, PL_CHECK_POST, PL_ASSERT, PL_ASSERT_MSG
#include <cstring>                     // std::strstr
#include <string>                      // std::string

TEST_CASE("assert_test")
{
  static constexpr char str1[]{"test"};
  const char* const     str2{"test"};
  const std::string     str3{"test"};

  CHECK_THROWS_AS(PL_CHECK_PRE(false), pl::precondition_violation_exception);
  CHECK_THROWS_AS(PL_CHECK_POST(false), pl::postcondition_violation_exception);
  CHECK_THROWS_AS(PL_ASSERT(false), pl::assertion_violation_exception);
  CHECK_THROWS_AS(
    PL_ASSERT_MSG(false, "test"), pl::assertion_violation_exception);
  CHECK_THROWS_AS(
    PL_ASSERT_MSG(false, str1), pl::assertion_violation_exception);
  CHECK_THROWS_AS(
    PL_ASSERT_MSG(false, str2), pl::assertion_violation_exception);
  CHECK_THROWS_AS(
    PL_ASSERT_MSG(false, str3), pl::assertion_violation_exception);

  try {
    PL_ASSERT_MSG(false, "test");
  }
  catch (const pl::assertion_violation_exception& ex) {
    CHECK(std::strstr(ex.what(), "assertion message: test") != nullptr);
  }

  try {
    PL_ASSERT_MSG(false, str1);
  }
  catch (const pl::assertion_violation_exception& ex) {
    CHECK(std::strstr(ex.what(), "assertion message: test") != nullptr);
  }

  try {
    PL_ASSERT_MSG(false, str2);
  }
  catch (const pl::assertion_violation_exception& ex) {
    CHECK(std::strstr(ex.what(), "assertion message: test") != nullptr);
  }

  try {
    PL_ASSERT_MSG(false, str3);
  }
  catch (const pl::assertion_violation_exception& ex) {
    CHECK(std::strstr(ex.what(), "assertion message: test") != nullptr);
  }
}
