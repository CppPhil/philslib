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
#endif                                        // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/algo/slide.hpp" // pl::algo::slide
#include <array>                              // std::array
#include <cstddef>                            // std::size_t
#include <iterator>                           // std::distance

TEST_CASE("slide_test")
{
    static constexpr std::size_t size{7U};

    std::array<int, size> array{{1, 2, 3, 4, 5, 6, 7}};

    const auto begin = std::begin(array);
    const auto end   = std::end(array);

    SUBCASE("slide_3_last_to_front")
    {
        const auto slide_from_begin = end - 3;
        const auto slide_from_end   = end;
        const auto slide_to         = begin;

        REQUIRE(slide_from_begin >= begin);
        REQUIRE(slide_from_begin <= end);
        REQUIRE(slide_from_end >= begin);
        REQUIRE(slide_from_end <= end);
        REQUIRE(slide_from_begin <= slide_from_end);
        REQUIRE(slide_to >= begin);
        REQUIRE(slide_to <= end);

        const auto pair
            = pl::algo::slide(slide_from_begin, slide_from_end, slide_to);

        CHECK(array.at(0U) == 5);
        CHECK(array.at(1U) == 6);
        CHECK(array.at(2U) == 7);
        CHECK(array.at(3U) == 1);
        CHECK(array.at(4U) == 2);
        CHECK(array.at(5U) == 3);
        CHECK(array.at(6U) == 4);

        CHECK(pair.first == slide_to);
        CHECK(pair.second == (slide_to + 3));
    }

    SUBCASE("slide_2_first_to_back")
    {
        const auto slide_from_begin = begin;
        const auto slide_from_end   = begin + 2;
        const auto slide_to         = end;

        REQUIRE(slide_from_begin >= begin);
        REQUIRE(slide_from_begin <= end);
        REQUIRE(slide_from_end >= begin);
        REQUIRE(slide_from_end <= end);
        REQUIRE(slide_from_begin <= slide_from_end);
        REQUIRE(slide_to >= begin);
        REQUIRE(slide_to <= end);

        const auto pair
            = pl::algo::slide(slide_from_begin, slide_from_end, slide_to);

        CHECK(array.at(0U) == 3);
        CHECK(array.at(1U) == 4);
        CHECK(array.at(2U) == 5);
        CHECK(array.at(3U) == 6);
        CHECK(array.at(4U) == 7);
        CHECK(array.at(5U) == 1);
        CHECK(array.at(6U) == 2);

        CHECK(
            pair.first
            == (slide_to - (std::distance(slide_from_begin, slide_from_end))));
        CHECK(pair.second == slide_to);
    }

    SUBCASE("slide_to_center")
    {
        const auto slide_from_begin = begin;
        const auto slide_from_end   = slide_from_begin + 2;
        const auto slide_to         = begin + (size / 2U);

        REQUIRE(slide_from_begin >= begin);
        REQUIRE(slide_from_begin <= end);
        REQUIRE(slide_from_end >= begin);
        REQUIRE(slide_from_end <= end);
        REQUIRE(slide_from_begin <= slide_from_end);
        REQUIRE(slide_to >= begin);
        REQUIRE(slide_to <= end);

        const auto pair
            = pl::algo::slide(slide_from_begin, slide_from_end, slide_to);

        CHECK(array.at(0U) == 3);
        CHECK(array.at(1U) == 1);
        CHECK(array.at(2U) == 2);
        CHECK(array.at(3U) == 4);
        CHECK(array.at(4U) == 5);
        CHECK(array.at(5U) == 6);
        CHECK(array.at(6U) == 7);

        CHECK(
            pair.first
            == (slide_to - (std::distance(slide_from_begin, slide_from_end))));
        CHECK(pair.second == slide_to);
    }

    SUBCASE("slide_empty_range")
    {
        const auto slide_from_begin = begin + 1;
        const auto slide_from_end   = slide_from_begin;
        const auto slide_to         = end;

        REQUIRE(slide_from_begin >= begin);
        REQUIRE(slide_from_begin <= end);
        REQUIRE(slide_from_end >= begin);
        REQUIRE(slide_from_end <= end);
        REQUIRE(slide_from_begin <= slide_from_end);
        REQUIRE(slide_to >= begin);
        REQUIRE(slide_to <= end);

        const auto pair
            = pl::algo::slide(slide_from_begin, slide_from_end, slide_to);

        CHECK(array.at(0U) == 1);
        CHECK(array.at(1U) == 2);
        CHECK(array.at(2U) == 3);
        CHECK(array.at(3U) == 4);
        CHECK(array.at(4U) == 5);
        CHECK(array.at(5U) == 6);
        CHECK(array.at(6U) == 7);

        CHECK(pair.first == end);
        CHECK(pair.second == end);
    }

    SUBCASE("slide_entire_range")
    {
        const auto slide_from_begin = begin;
        const auto slide_from_end   = end;
        const auto slide_to         = begin + 3;

        REQUIRE(slide_from_begin >= begin);
        REQUIRE(slide_from_begin <= end);
        REQUIRE(slide_from_end >= begin);
        REQUIRE(slide_from_end <= end);
        REQUIRE(slide_from_begin <= slide_from_end);
        REQUIRE(slide_to >= begin);
        REQUIRE(slide_to <= end);

        const auto pair
            = pl::algo::slide(slide_from_begin, slide_from_end, slide_to);

        CHECK(array.at(0U) == 1);
        CHECK(array.at(1U) == 2);
        CHECK(array.at(2U) == 3);
        CHECK(array.at(3U) == 4);
        CHECK(array.at(4U) == 5);
        CHECK(array.at(5U) == 6);
        CHECK(array.at(6U) == 7);

        CHECK(pair.first == begin);
        CHECK(pair.second == end);
    }
}
