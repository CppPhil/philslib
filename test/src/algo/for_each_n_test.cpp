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
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // CR_COMPILER == CR_COMPILER_GCC
#include "../../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // CR_COMPILER == CR_COMPILER_GCC
#include "../../../include/pl/algo/for_each_n.hpp" // pl::algo::for_each_n
#include <iterator> // std::begin, std::end
#include <vector> // std::vector

TEST_CASE("for_each_n_test")
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };

    SUBCASE("entire_range_squared") {
        const auto it = pl::algo::for_each_n(
            std::begin(v),
            v.size(),
            [](int &e) { e *= e; });

        REQUIRE(v.size() == 6U);
        CHECK(v[0U] ==  1);
        CHECK(v[1U] ==  4);
        CHECK(v[2U] ==  9);
        CHECK(v[3U] == 16);
        CHECK(v[4U] == 25);
        CHECK(v[5U] == 36);

        CHECK(it == std::end(v));
    }

    SUBCASE("three_first_elements_doubled") {
        static constexpr std::vector<int>::size_type count{ 3U };

        REQUIRE(count <= v.size());

        const auto it = pl::algo::for_each_n(
            std::begin(v),
            count,
            [](int &e) { e *= 2; });

        REQUIRE(v.size() == 6U);
        CHECK(v[0U] == 2);
        CHECK(v[1U] == 4);
        CHECK(v[2U] == 6);
        CHECK(v[3U] == 4);
        CHECK(v[4U] == 5);
        CHECK(v[5U] == 6);

        CHECK(it == (std::begin(v) + count));
    }
}
