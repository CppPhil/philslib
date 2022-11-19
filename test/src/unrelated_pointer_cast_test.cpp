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
#include "../../include/pl/unrelated_pointer_cast.hpp" // pl::unrelated_pointer_cast
#include "../include/static_assert.hpp"                // PL_TEST_STATIC_ASSERT
#include <array>                                       // std::array
#include <cstddef>                                     // std::size_t
#include <cstdint>                                     // std::uint32_t
#include <cstring>                                     // std::memcpy

TEST_CASE("unrelated_pointer_cast_test")
{
  static constexpr std::size_t             bytes{sizeof(std::uint32_t)};
  static constexpr std::array<char, bytes> ary{"\xAA\xBB\xCC"};

  std::uint32_t i{};

  PL_TEST_STATIC_ASSERT(sizeof(i) == ary.size());

  std::memcpy(&i, ary.data(), ary.size());

  SUBCASE("non_const")
  {
    char* const p{pl::unrelated_pointer_cast<char*>(&i)};

    CHECK(p[0U] == '\xAA');
    CHECK(p[1U] == '\xBB');
    CHECK(p[2U] == '\xCC');
    CHECK(p[3U] == '\0');

    p[0U] = '\xDE';
    p[1U] = '\xAD';
    p[2U] = '\xC0';
    p[3U] = '\xDE';

    CHECK(p[0U] == '\xDE');
    CHECK(p[1U] == '\xAD');
    CHECK(p[2U] == '\xC0');
    CHECK(p[3U] == '\xDE');
  }

  SUBCASE("const")
  {
    const std::uint32_t& r{i};
    const char* const    p{pl::unrelated_pointer_cast<const char*>(&r)};

    CHECK(p[0U] == '\xAA');
    CHECK(p[1U] == '\xBB');
    CHECK(p[2U] == '\xCC');
    CHECK(p[3U] == '\0');
  }
}
