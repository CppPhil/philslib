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
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/memxor.hpp" // pl::memxor
#include "../../include/pl/byte.hpp" // pl::Byte
#include "../../include/pl/cont/make_array.hpp" // pl::makeArray
#include <cstddef> // std::size_t
#include <cstring> // std::memcmp

TEST_CASE("memxor_test")
{
    constexpr auto expectedArray = pl::cont::makeArray(
        static_cast<pl::Byte>('\x17'), static_cast<pl::Byte>('\x0A'),
        static_cast<pl::Byte>('\x1C'), static_cast<pl::Byte>('\x1F'),
        static_cast<pl::Byte>('\x49'), static_cast<pl::Byte>('\x11'),
        static_cast<pl::Byte>('\x16'), static_cast<pl::Byte>('\x59'),
        static_cast<pl::Byte>('\x55'), static_cast<pl::Byte>('\x00'));

    constexpr auto srcArray = pl::cont::makeArray(
        static_cast<pl::Byte>('\x63'), static_cast<pl::Byte>('\x6F'),
        static_cast<pl::Byte>('\x6F'), static_cast<pl::Byte>('\x6B'),
        static_cast<pl::Byte>('\x69'), static_cast<pl::Byte>('\x65'),
        static_cast<pl::Byte>('\x73'), static_cast<pl::Byte>('\x21'),
        static_cast<pl::Byte>('\x21'), static_cast<pl::Byte>('\x00'));

    auto destArray = pl::cont::makeArray(
        static_cast<pl::Byte>('\x74'), static_cast<pl::Byte>('\x65'),
        static_cast<pl::Byte>('\x73'), static_cast<pl::Byte>('\x74'),
        static_cast<pl::Byte>('\x20'), static_cast<pl::Byte>('\x74'),
        static_cast<pl::Byte>('\x65'), static_cast<pl::Byte>('\x78'),
        static_cast<pl::Byte>('\x74'), static_cast<pl::Byte>('\x00'));

    REQUIRE(destArray.size() == srcArray.size());
    REQUIRE(destArray.size() == expectedArray.size());

    void * const dest{ destArray.data() };
    const void * const src{ srcArray.data() };
    const void * const expected{ expectedArray.data() };

    const std::size_t size{ destArray.size() };

    void * const retVal{ pl::memxor(dest, src, size) };

    CHECK(retVal == dest);

    CHECK(std::memcmp(dest, expected, size) == 0);
}
