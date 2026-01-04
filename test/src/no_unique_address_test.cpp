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
#include "../../include/pl/no_unique_address.hpp" // PL_NO_UNIQUE_ADDRESS
#include <cstdint>                                // std::int32_t

namespace test {
namespace {
struct Empty {};

struct Struct {
  std::int32_t               value;
  PL_NO_UNIQUE_ADDRESS Empty empty;
};
} // anonymous namespace
} // namespace test

TEST_CASE("no_unique_address_test")
{
#if PL_COMPILER == PL_COMPILER_MSVC
#if _MSC_FULL_VER >= 192829913
  CHECK(sizeof(test::Struct) == sizeof(std::int32_t));
#else
  CHECK(sizeof(test::Struct) > sizeof(std::int32_t));
#endif
#elif PL_COMPILER == PL_COMPILER_GCC
#if PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(9, 0, 0)
  CHECK(sizeof(test::Struct) == sizeof(std::int32_t));
#else
  CHECK(sizeof(test::Struct) > sizeof(std::int32_t));
#endif
#elif PL_COMPILER == PL_COMPILER_CLANG
#if PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(9, 0, 0)
  CHECK(sizeof(test::Struct) == sizeof(std::int32_t));
#else
  CHECK(sizeof(test::Struct) > sizeof(std::int32_t));
#endif
#else
  CHECK(sizeof(test::Struct) > sizeof(std::int32_t));
#endif
}
