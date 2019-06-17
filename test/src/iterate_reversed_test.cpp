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
#include "../../include/pl/iterate_reversed.hpp" // pl::iterate_reversed
#include "../include/static_assert.hpp"          // PL_TEST_STATIC_ASSERT
#include <cstddef>                               // std::size_t
#include <iterator>                              // std::iterator_traits
#include <type_traits>                           // std::is_same
#include <utility>                               // std::declval
#include <vector>                                // std::vector

TEST_CASE("iterate_reversed_type_test")
{
    std::vector<int>       non_const_vec{1, 2, 3, 4, 5};
    const std::vector<int> const_vector{1, 2, 3};

    using non_const          = decltype(pl::iterate_reversed(non_const_vec));
    using non_const_begin_it = decltype(std::declval<non_const>().begin());
    using non_const_end_it   = decltype(std::declval<non_const>().end());

    using const_type     = decltype(pl::iterate_reversed(const_vector));
    using const_begin_it = decltype(std::declval<const_type>().begin());
    using const_end_it   = decltype(std::declval<const_type>().end());

    PL_TEST_STATIC_ASSERT(
        std::is_same<non_const_begin_it, std::vector<int>::reverse_iterator>::
            value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<non_const_end_it, std::vector<int>::reverse_iterator>::
            value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<const_begin_it, std::vector<int>::const_reverse_iterator>::
            value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<const_end_it, std::vector<int>::const_reverse_iterator>::
            value);

    PL_TEST_STATIC_ASSERT(std::is_same<
                          std::iterator_traits<non_const_begin_it>::reference,
                          int&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<std::iterator_traits<non_const_end_it>::reference, int&>::
            value);

    PL_TEST_STATIC_ASSERT(std::is_same<
                          std::iterator_traits<const_begin_it>::reference,
                          const int&>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
                          std::iterator_traits<const_end_it>::reference,
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
        for (auto& e : pl::iterate_reversed(a1)) {
            CHECK(e == expected[i]);
            ++i;
        }
    }

    SUBCASE("const_array")
    {
        for (const auto& e : pl::iterate_reversed(a2)) {
            CHECK(e == expected[i]);
            ++i;
        }
    }

    SUBCASE("non_const_vector")
    {
        for (auto& e : pl::iterate_reversed(vec1)) {
            CHECK(e == expected[i]);
            ++i;
        }
    }

    SUBCASE("const_vector")
    {
        for (const auto& e : pl::iterate_reversed(vec2)) {
            CHECK(e == expected[i]);
            ++i;
        }
    }
}
