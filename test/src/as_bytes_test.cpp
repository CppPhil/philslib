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
#include "../../include/pl/as_bytes.hpp" // pl::as_bytes
#include "../include/static_assert.hpp"  // PL_TEST_STATIC_ASSERT
#include <cstddef>                       // std::size_t
#include <cstdint>                       // std::uint32_t
#include <cstring>                       // std::memcpy
#include <type_traits>                   // std::is_same

TEST_CASE("as_bytes_buffer_test")
{
  static constexpr std::size_t byte_size{5U};
  static constexpr char        buf1[]{"\xAA\xBB\xCC\xDD"};
  char                         buf2[]{"\xDE\xAD\xC0\xDE"};

  PL_TEST_STATIC_ASSERT(sizeof(buf1) == byte_size);
  PL_TEST_STATIC_ASSERT(sizeof(buf2) == byte_size);

  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(pl::as_bytes(buf1)), const pl::byte*>::value);
  PL_TEST_STATIC_ASSERT(
    std::is_same<decltype(pl::as_bytes(buf2)), pl::byte*>::value);

  const pl::byte* p1{pl::as_bytes(buf1)};
  pl::byte*       p2{pl::as_bytes(buf2)};

  REQUIRE(p1 != nullptr);
  REQUIRE(p2 != nullptr);

  CHECK(p1[0U] == static_cast<pl::byte>(0xAA));
  CHECK(p1[1U] == static_cast<pl::byte>(0xBB));
  CHECK(p1[2U] == static_cast<pl::byte>(0xCC));
  CHECK(p1[3U] == static_cast<pl::byte>(0xDD));
  CHECK(p1[4U] == static_cast<pl::byte>(0x00));

  CHECK(p2[0U] == static_cast<pl::byte>(0xDE));
  CHECK(p2[1U] == static_cast<pl::byte>(0xAD));
  CHECK(p2[2U] == static_cast<pl::byte>(0xC0));
  CHECK(p2[3U] == static_cast<pl::byte>(0xDE));
  CHECK(p2[4U] == static_cast<pl::byte>(0x00));
}

TEST_CASE("as_bytes_int_test")
{
  static constexpr std::size_t byte_size{4U};

  std::uint32_t v{};
  PL_TEST_STATIC_ASSERT(sizeof(v) == byte_size);

  std::memcpy(&v, "\xDE\xAD\xC0\xDE", byte_size);

  const pl::byte* p{pl::as_bytes(v)};

  REQUIRE(p != nullptr);

  CHECK(p[0U] == static_cast<pl::byte>(0xDE));
  CHECK(p[1U] == static_cast<pl::byte>(0xAD));
  CHECK(p[2U] == static_cast<pl::byte>(0xC0));
  CHECK(p[3U] == static_cast<pl::byte>(0xDE));
}
