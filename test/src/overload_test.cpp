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
#endif                                   // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/overload.hpp" // pl::overload
#include <string>                        // std::string

TEST_CASE("overload_simple_test")
{
  CHECK(pl::overload([](int i, int j) { return i * j; })(5, 8) == 40);
}

TEST_CASE("overload_advanced_test")
{
  const std::string string{"Text"};

  auto        l1 = [](int i) { return i * i; };
  const auto  l2 = [](double d1, double d2) { return d1 + d2; };
  auto        l3 = [](const std::string& s) { return s.front(); };
  const auto& r  = l3;

  const auto overload
    = pl::overload(l1, l2, r, [](float f) { return f * 2.0F; });

  CHECK(overload(5) == 25);
  CHECK(overload(1.1, 2.2) == doctest::Approx(3.3));
  CHECK(overload(string) == 'T');
  CHECK(static_cast<double>(overload(3.0F)) == doctest::Approx(6.0));
}
