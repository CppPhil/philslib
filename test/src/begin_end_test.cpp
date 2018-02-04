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
#include "../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include "../../include/pl/begin_end.hpp" // pl::begin, pl::cbegin, pl::end, pl::cend, pl::rbegin, pl::crbegin, pl::rend, pl::crend
#include "../../include/pl/cont/make_array.hpp" // pl::cont::makeArray
#include "../../include/pl/cont/size.hpp" // pl::cont::size
#include <cstddef> // std::size_t
#include <list> // std::list
#include <initializer_list> // std::initializer_list
#include <array> // std::array
#include <iterator> // std::reverse_iterator, std::make_reverse_iterator
#include <algorithm> // std::equal
#include <type_traits> // std::is_equal

namespace pl
{
namespace test
{
namespace
{
template <typename InputIterator>
bool isEqualToExpected(InputIterator first, InputIterator last)
{
    static constexpr auto expected = ::pl::cont::makeArray(1, 2, 3, 4, 5);

    return std::equal(first, last, ::pl::begin(expected), ::pl::end(expected));
}
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("begin_end_c_array_test")
{
    static constexpr int ary[]{ 1, 2, 3, 4, 5 };
    static constexpr int revAry[]{ 5, 4, 3, 2, 1 };
    int nonConst[]{ 1, 2, 3, 4, 5 };

    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::begin(ary)),
        const int *>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cbegin(ary)),
        const int *>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::end(ary)),
        const int *>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cend(ary)),
        const int *>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rbegin(ary)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crbegin(ary)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rend(ary)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crend(ary)),
        std::reverse_iterator<const int *>>::value);

    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::begin(nonConst)),
        int *>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cbegin(nonConst)),
        const int *>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::end(nonConst)),
        int *>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cend(nonConst)),
        const int *>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rbegin(nonConst)),
        std::reverse_iterator<int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crbegin(nonConst)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rend(nonConst)),
        std::reverse_iterator<int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crend(nonConst)),
        std::reverse_iterator<const int *>>::value);

    CHECK(pl::begin(ary) == &ary[0U]);
    CHECK(pl::end(ary) == &ary[pl::cont::size(ary)]);
    CHECK(pl::rbegin(ary).base() == &ary[pl::cont::size(ary)]);
    CHECK(pl::rend(ary).base() == &ary[0U]);

    CHECK_UNARY(pl::test::isEqualToExpected(PL_CBEGIN_CEND(ary)));
    CHECK_UNARY(pl::test::isEqualToExpected(PL_CRBEGIN_CREND(revAry)));
}

TEST_CASE("begin_end_list_test")
{
    const std::list<int> l{ 1, 2, 3, 4, 5 };
    std::list<int> nonConst{ 1, 2, 3, 4, 5 };
    const std::list<int> reverse{ 5, 4, 3, 2, 1 };

    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::begin(l)),
        std::list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cbegin(l)),
        std::list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::end(l)),
        std::list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cend(l)),
        std::list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rbegin(l)),
        std::list<int>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crbegin(l)),
        std::list<int>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rend(l)),
        std::list<int>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crend(l)),
        std::list<int>::const_reverse_iterator>::value);

    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::begin(nonConst)),
        std::list<int>::iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cbegin(nonConst)),
        std::list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::end(nonConst)),
        std::list<int>::iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cend(nonConst)),
        std::list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rbegin(nonConst)),
        std::list<int>::reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crbegin(nonConst)),
        std::list<int>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rend(nonConst)),
        std::list<int>::reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crend(nonConst)),
        std::list<int>::const_reverse_iterator>::value);

    CHECK(pl::begin(l) == l.begin());
    CHECK(pl::end(l) == l.end());
    CHECK(pl::rbegin(l) == l.rbegin());
    CHECK(pl::rend(l) == l.rend());

    CHECK_UNARY(pl::test::isEqualToExpected(PL_CBEGIN_CEND(l)));
    CHECK_UNARY(pl::test::isEqualToExpected(PL_CRBEGIN_CREND(reverse)));
}

TEST_CASE("begin_end_init_list_test")
{
    const std::initializer_list<int> il{ 1, 2, 3, 4, 5 };
    std::initializer_list<int> nonConst{ 1, 2, 3, 4, 5 };
    const std::initializer_list<int> reverse{ 5, 4, 3, 2, 1 };

    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::begin(il)),
        std::initializer_list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cbegin(il)),
        std::initializer_list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::end(il)),
        std::initializer_list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cend(il)),
        std::initializer_list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rbegin(il)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crbegin(il)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rend(il)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crend(il)),
        std::reverse_iterator<const int *>>::value);

    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::begin(nonConst)),
        std::initializer_list<int>::iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cbegin(nonConst)),
        std::initializer_list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::end(nonConst)),
        std::initializer_list<int>::iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cend(nonConst)),
        std::initializer_list<int>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rbegin(nonConst)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crbegin(nonConst)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rend(nonConst)),
        std::reverse_iterator<const int *>>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crend(nonConst)),
        std::reverse_iterator<const int *>>::value);

    CHECK(pl::begin(il) == il.begin());
    CHECK(pl::end(il) == il.end());
    CHECK(pl::rbegin(il) == std::make_reverse_iterator(il.end()));
    CHECK(pl::rend(il) == std::make_reverse_iterator(il.begin()));

    CHECK_UNARY(pl::test::isEqualToExpected(PL_CBEGIN_CEND(il)));
    CHECK_UNARY(pl::test::isEqualToExpected(PL_CRBEGIN_CREND(reverse)));
}

TEST_CASE("begin_end_std_array_test")
{
    static constexpr std::size_t arySiz{ 5U };

    const std::array<int, arySiz> ary{ { 1, 2, 3, 4, 5 } };
    std::array<int, arySiz> nonConst{ { 1, 2, 3, 4, 5 } };
    const std::array<int, arySiz> reverse{ { 5, 4, 3, 2, 1 } };

    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::begin(ary)),
        std::array<int, arySiz>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cbegin(ary)),
        std::array<int, arySiz>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::end(ary)),
        std::array<int, arySiz>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cend(ary)),
        std::array<int, arySiz>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rbegin(ary)),
        std::array<int, arySiz>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crbegin(ary)),
        std::array<int, arySiz>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rend(ary)),
        std::array<int, arySiz>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crend(ary)),
        std::array<int, arySiz>::const_reverse_iterator>::value);

    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::begin(nonConst)),
        std::array<int, arySiz>::iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cbegin(nonConst)),
        std::array<int, arySiz>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::end(nonConst)),
        std::array<int, arySiz>::iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::cend(nonConst)),
        std::array<int, arySiz>::const_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rbegin(nonConst)),
        std::array<int, arySiz>::reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crbegin(nonConst)),
        std::array<int, arySiz>::const_reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::rend(nonConst)),
        std::array<int, arySiz>::reverse_iterator>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<
        decltype(pl::crend(nonConst)),
        std::array<int, arySiz>::const_reverse_iterator>::value);

    CHECK(pl::begin(ary) == ary.begin());
    CHECK(pl::end(ary) == ary.end());
    CHECK(pl::rbegin(ary) == ary.rbegin());
    CHECK(pl::rend(ary) == ary.rend());

    CHECK_UNARY(pl::test::isEqualToExpected(PL_CBEGIN_CEND(ary)));
    CHECK_UNARY(pl::test::isEqualToExpected(PL_CRBEGIN_CREND(reverse)));
}
