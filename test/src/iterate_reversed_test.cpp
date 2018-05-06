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
#include "../../include/pl/iterate_reversed.hpp" // pl::iterateReversed
#include "../include/static_assert.hpp"          // PL_TEST_STATIC_ASSERT
#include <cstddef>                               // std::size_t
#include <iterator>                              // std::iterator_traits
#include <type_traits>                           // std::is_same
#include <utility>                               // std::declval
#include <vector>                                // std::vector

TEST_CASE("iterate_reversed_type_test")
{
    std::vector<int>       nonConst{1, 2, 3, 4, 5};
    const std::vector<int> constVector{1, 2, 3};

    using NonConst        = decltype(pl::iterateReversed(nonConst));
    using NonConstBeginIt = decltype(std::declval<NonConst>().begin());
    using NonConstEndIt   = decltype(std::declval<NonConst>().end());

    using Const        = decltype(pl::iterateReversed(constVector));
    using ConstBeginIt = decltype(std::declval<Const>().begin());
    using ConstEndIt   = decltype(std::declval<Const>().end());

    PL_TEST_STATIC_ASSERT(
        std::is_same<NonConstBeginIt,
                     std::vector<int>::reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<NonConstEndIt, std::vector<int>::reverse_iterator>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<ConstBeginIt,
                     std::vector<int>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<ConstEndIt,
                     std::vector<int>::const_reverse_iterator>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<std::iterator_traits<NonConstBeginIt>::reference,
                     int&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<std::iterator_traits<NonConstEndIt>::reference,
                     int&>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<std::iterator_traits<ConstBeginIt>::reference,
                     const int&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<std::iterator_traits<ConstEndIt>::reference,
                     const int&>::value);

    CHECK_UNARY(true);
}

TEST_CASE("iterate_reversed_test")
{
    const unsigned expected[]{1, 2, 3, 4, 5};
    unsigned       a1[]{5, 4, 3, 2, 1};
    const unsigned a2[]{5, 4, 3, 2, 1};

    std::vector<int>       vec1(std::cbegin(a2), std::cend(a2));
    const std::vector<int> vec2(std::cbegin(vec1), std::cend(vec1));

    std::size_t i{0U};

    SUBCASE("non_const_array")
    {
        for (auto& e : pl::iterateReversed(a1)) {
            CHECK(e == expected[i]);
            ++i;
        }
    }

    SUBCASE("const_array")
    {
        for (const auto& e : pl::iterateReversed(a2)) {
            CHECK(e == expected[i]);
            ++i;
        }
    }

    SUBCASE("non_const_vector")
    {
        for (auto& e : pl::iterateReversed(vec1)) {
            CHECK(e == expected[i]);
            ++i;
        }
    }

    SUBCASE("const_vector")
    {
        for (const auto& e : pl::iterateReversed(vec2)) {
            CHECK(e == expected[i]);
            ++i;
        }
    }
}
