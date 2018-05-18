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
#include "../../../include/pl/algo/destroy.hpp"
#include "../../../include/pl/algo/destroy_at.hpp"
#include "../../../include/pl/algo/destroy_n.hpp"
#include "../../include/destroy_test_type.hpp" // pl::test::destroy_test_type
#include "../../include/freeer.hpp"            // pl::test::freeer
#include <array>                               // std::array
#include <cstddef>                             // std::size_t
#include <cstdlib>                             // std::malloc, std::free
#include <memory>                              // std::unique_ptr
#include <new>                                 // ::operator new

TEST_CASE("test_destroy_algorithms")
{
    static constexpr std::size_t size = 10U;

    std::unique_ptr<unsigned char, pl::test::freeer> up{
        static_cast<unsigned char*>(
            std::malloc(size * sizeof(pl::test::destroy_test_type))),
        pl::test::freeer{}};

    auto* begin = reinterpret_cast<pl::test::destroy_test_type*>(up.get());
    auto* end   = begin + size;

    std::array<bool, size> ary{};
    ary.fill(false);

    for (std::size_t i{0U}; i < size; ++i) {
        ::new (static_cast<void*>(&begin[i]))
            pl::test::destroy_test_type{&ary[i]};
    }

    SUBCASE("test_destroy")
    {
        pl::algo::destroy(begin, end);

        for (bool b : ary) {
            CHECK_UNARY(b);
        }
    }

    SUBCASE("test_destroy_at")
    {
        for (std::size_t i{0U}; i < size; ++i) {
            pl::algo::destroy_at(&begin[i]);
        }

        for (bool b : ary) {
            CHECK_UNARY(b);
        }
    }

    SUBCASE("test_destroy_n")
    {
        pl::algo::destroy_n(begin, size);

        for (bool b : ary) {
            CHECK_UNARY(b);
        }
    }
}
