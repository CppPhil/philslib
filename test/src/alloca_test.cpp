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
#include "../../include/pl/alloca.hpp" // PL_ALLOCA
#include "../../include/pl/byte.hpp"   // pl::byte
#include <algorithm>                   // std::fill, std::all_of
#include <cstddef>                     // std::size_t, std::ptrdiff_t
#include <iterator>                    // std::distance

#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstack-protector"
#endif // PL_COMPILER == PL_COMPILER_GCC
TEST_CASE("alloca_test")
{
    static constexpr std::size_t byte_count{20U};
    static constexpr pl::byte    fill_byte{0xAB};

    void* memory = PL_ALLOCA(byte_count);

    REQUIRE(memory != nullptr);

    auto* begin = static_cast<pl::byte*>(memory);
    auto* end   = begin + byte_count;

    REQUIRE(
        std::distance(begin, end) == static_cast<std::ptrdiff_t>(byte_count));

    std::fill(begin, end, fill_byte);

    CHECK_UNARY(std::all_of(begin, end, [](pl::byte byte) {
        return byte == fill_byte;
    }));
}
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
