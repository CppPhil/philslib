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
#endif                               // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/byte.hpp" // pl::byte
#include "../../include/pl/cont/make_array.hpp" // pl::make_array
#include "../../include/pl/memxor.hpp"          // pl::memxor
#include <cstddef>                              // std::size_t
#include <cstring>                              // std::memcmp

TEST_CASE("memxor_test")
{
    constexpr auto expected_array = pl::cont::make_array(
        static_cast<pl::byte>('\x17'),
        static_cast<pl::byte>('\x0A'),
        static_cast<pl::byte>('\x1C'),
        static_cast<pl::byte>('\x1F'),
        static_cast<pl::byte>('\x49'),
        static_cast<pl::byte>('\x11'),
        static_cast<pl::byte>('\x16'),
        static_cast<pl::byte>('\x59'),
        static_cast<pl::byte>('\x55'),
        static_cast<pl::byte>('\x00'));

    constexpr auto src_array = pl::cont::make_array(
        static_cast<pl::byte>('\x63'),
        static_cast<pl::byte>('\x6F'),
        static_cast<pl::byte>('\x6F'),
        static_cast<pl::byte>('\x6B'),
        static_cast<pl::byte>('\x69'),
        static_cast<pl::byte>('\x65'),
        static_cast<pl::byte>('\x73'),
        static_cast<pl::byte>('\x21'),
        static_cast<pl::byte>('\x21'),
        static_cast<pl::byte>('\x00'));

    auto dest_array = pl::cont::make_array(
        static_cast<pl::byte>('\x74'),
        static_cast<pl::byte>('\x65'),
        static_cast<pl::byte>('\x73'),
        static_cast<pl::byte>('\x74'),
        static_cast<pl::byte>('\x20'),
        static_cast<pl::byte>('\x74'),
        static_cast<pl::byte>('\x65'),
        static_cast<pl::byte>('\x78'),
        static_cast<pl::byte>('\x74'),
        static_cast<pl::byte>('\x00'));

    REQUIRE(dest_array.size() == src_array.size());
    REQUIRE(dest_array.size() == expected_array.size());

    void* const       dest{dest_array.data()};
    const void* const src{src_array.data()};
    const void* const expected{expected_array.data()};

    const std::size_t size{dest_array.size()};

    void* const ret_val{pl::memxor(dest, src, size)};

    CHECK(ret_val == dest);

    CHECK(std::memcmp(dest, expected, size) == 0);
}
