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
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/algo/ranged_algorithms.hpp" // pl::algo::transform
#include "../../include/pl/char_to_int.hpp"            // pl::char_to_int
#include "../include/static_assert.hpp"                // PL_TEST_STATIC_ASSERT
#include <array>                                       // std::array
#include <cstddef>                                     // std::size_t
#include <cstdint>                                     // std::uint8_t
#include <iterator>                                    // std::begin

TEST_CASE("char_to_int_test")
{
  static constexpr std::size_t digits{10U};

  const std::array<unsigned char, digits> characters{
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'}};

  const std::array<std::uint8_t, digits> integers{
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}};

  std::array<std::uint8_t, digits> result{{0U}};

  pl::algo::transform(characters, std::begin(result), &pl::char_to_int);

  CHECK(result == integers);
}

TEST_CASE("char_to_int_constexpr_test")
{
  PL_TEST_STATIC_ASSERT(pl::char_to_int('1') == 1);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('2') == 2);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('3') == 3);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('4') == 4);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('5') == 5);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('6') == 6);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('7') == 7);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('8') == 8);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('9') == 9);
  PL_TEST_STATIC_ASSERT(pl::char_to_int('0') == 0);

  CHECK_UNARY(true);
}
