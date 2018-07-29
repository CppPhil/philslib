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
#endif                                       // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/cheshire_cat.hpp" // pl::cheshire_cat
#include "../include/cheshire_cat_impl_type.hpp" // pl::test::cheshire_cat_impl_type
#include "../include/cheshire_cat_test_type.hpp" // pl::test::cheshire_cat_test_type
#include <cstdint>                               // std::uint32_t, UINT32_C
#include <utility>                               // std::move

using test_cheshire_cat
    = pl::cheshire_cat<pl::test::cheshire_cat_impl_type,
                       sizeof(pl::test::cheshire_cat_impl_type)>;

TEST_CASE("cheshire_cat_impl_type_default_construct_test")
{
    const test_cheshire_cat a{};
    CHECK(a->value() == 0);
}

TEST_CASE("cheshire_cat_impl_type_lvalue_construct_test")
{
    const pl::test::cheshire_cat_impl_type lvalue{20};
    const test_cheshire_cat                cc{lvalue};
    CHECK(cc->value() == 20);
}

TEST_CASE("cheshire_cat_impl_type_rvalue_construct_test")
{
    const test_cheshire_cat cc{pl::test::cheshire_cat_impl_type{55}};
    CHECK(cc->value() == 55);
}

TEST_CASE("cheshire_cat_impl_type_copy_construct_test")
{
    const test_cheshire_cat cc1{pl::test::cheshire_cat_impl_type{30}};
    const test_cheshire_cat cc2{cc1};
    CHECK(cc1->value() == 30);
    CHECK(cc2->value() == 30);
    CHECK(cc1->value() == cc2->value());
}

TEST_CASE("cheshire_cat_impl_type_move_construct_test")
{
    const test_cheshire_cat cc1{
        test_cheshire_cat{pl::test::cheshire_cat_impl_type{500}}};
    CHECK(cc1->value() == 500);

    test_cheshire_cat       cc2{pl::test::cheshire_cat_impl_type{6000}};
    const test_cheshire_cat cc3{std::move(cc2)};
    CHECK(cc3->value() == 6000);
}

TEST_CASE("cheshire_cat_impl_type_in_place_construct_test")
{
    const test_cheshire_cat cc{pl::in_place_t{}, 12};
    CHECK(cc->value() == 12);
}

TEST_CASE("cheshire_cat_impl_type_in_place_initializer_list_construct_test")
{
    const test_cheshire_cat cc{pl::in_place_t{}, {1}};
    CHECK(cc->value() == 1);
}

TEST_CASE("cheshire_cat_impl_type_lvalue_assign_test")
{
    test_cheshire_cat cc{pl::in_place_t{}, 1};
    CHECK(cc->value() == 1);
    const pl::test::cheshire_cat_impl_type a{2};
    cc = a;
    CHECK(cc->value() == 2);
}

TEST_CASE("cheshire_cat_impl_type_rvalue_assign_test")
{
    test_cheshire_cat cc{pl::in_place_t{}, 450};
    CHECK(cc->value() == 450);
    cc = pl::test::cheshire_cat_impl_type{37};
    CHECK(cc->value() == 37);

    pl::test::cheshire_cat_impl_type a{15};
    cc = std::move(a);
    CHECK(cc->value() == 15);
}

TEST_CASE("cheshire_cat_impl_type_copy_assignment_test")
{
    const test_cheshire_cat cc1{pl::in_place_t{}, 870};
    test_cheshire_cat       cc2{pl::in_place_t{}, 12};
    CHECK(cc2->value() == 12);
    cc2 = cc1;
    CHECK(cc2->value() == 870);
}

TEST_CASE("cheshire_cat_impl_type_move_assignment_test")
{
    test_cheshire_cat cc1{pl::in_place_t{}, 30};
    CHECK(cc1->value() == 30);
    cc1 = test_cheshire_cat{pl::in_place_t{}, 12};
    CHECK(cc1->value() == 12);

    test_cheshire_cat cc2{pl::in_place_t{}, 49};
    cc1 = std::move(cc2);
    CHECK(cc1->value() == 49);
}

TEST_CASE("cheshire_cat_impl_type_access_test")
{
    const test_cheshire_cat                       cc{pl::in_place_t{}, 4};
    const pl::test::cheshire_cat_impl_type* const p1{cc.get()};
    const pl::test::cheshire_cat_impl_type* const p2{cc.operator->()};
    const pl::test::cheshire_cat_impl_type&       ref{*cc};

    CHECK(p1->value() == 4);
    CHECK(p2->value() == 4);
    CHECK(ref.value() == 4);

    CHECK(p1 == p2);
    CHECK(p1 == &ref);
    CHECK(p2 == p1);
    CHECK(p2 == &ref);
    CHECK(&ref == p1);
    CHECK(&ref == p2);
}

TEST_CASE("cheshire_cat_impl_type_swap_test")
{
    test_cheshire_cat cc1{pl::in_place_t{}, 3};
    test_cheshire_cat cc2{pl::in_place_t{}, 4};

    CHECK(cc1->value() == 3);
    CHECK(cc2->value() == 4);

    swap(cc1, cc2);
    CHECK(cc1->value() == 4);
    CHECK(cc2->value() == 3);
}

TEST_CASE("cheshire_cat_test_type_default_construct_test")
{
    const pl::test::cheshire_cat_test_type a{};
    CHECK(a.sum() == UINT32_C(0));
}

TEST_CASE("cheshire_cat_test_type_construct_test")
{
    const pl::test::cheshire_cat_test_type a{UINT32_C(12), "5"};
    CHECK(a.sum() == UINT32_C(17));
}

TEST_CASE("cheshire_cat_test_type_copy_construct_test")
{
    const pl::test::cheshire_cat_test_type a{UINT32_C(1), "30"};
    const pl::test::cheshire_cat_test_type b{a};

    CHECK(a.sum() == 31);
    CHECK(b.sum() == 31);
    CHECK(a == b);
}

TEST_CASE("cheshire_cat_test_type_move_construct_test")
{
    const pl::test::cheshire_cat_test_type a{
        pl::test::cheshire_cat_test_type{UINT32_C(30), "40"}};
    CHECK(a.sum() == UINT32_C(70));

    pl::test::cheshire_cat_test_type       b{UINT32_C(5), "4"};
    const pl::test::cheshire_cat_test_type c{std::move(b)};
    CHECK(c.sum() == UINT32_C(9));
}

TEST_CASE("cheshire_cat_test_type_copy_assignment_test")
{
    pl::test::cheshire_cat_test_type a{UINT32_C(3), "2"};
    CHECK(a.sum() == UINT32_C(5));

    const pl::test::cheshire_cat_test_type b{UINT32_C(5), "500"};
    a = b;
    CHECK(a == b);
    CHECK(a.sum() == UINT32_C(505));
    CHECK(b.sum() == UINT32_C(505));
}

TEST_CASE("cheshire_cat_test_type_move_assignment_test")
{
    pl::test::cheshire_cat_test_type a{UINT32_C(4), "7"};
    CHECK(a.sum() == UINT32_C(11));

    a = pl::test::cheshire_cat_test_type{UINT32_C(400), "1"};
    CHECK(a.sum() == UINT32_C(401));

    pl::test::cheshire_cat_test_type b{UINT32_C(12), "1000"};
    CHECK(b.sum() == UINT32_C(1012));

    a = std::move(b);
    CHECK(a.sum() == UINT32_C(1012));
}

TEST_CASE("cheshire_cat_test_type_swap_test")
{
    pl::test::cheshire_cat_test_type a{UINT32_C(3), "4"};
    pl::test::cheshire_cat_test_type b{UINT32_C(0), "2"};

    CHECK(a.sum() == UINT32_C(7));
    CHECK(b.sum() == UINT32_C(2));

    swap(a, b);

    CHECK(a.sum() == UINT32_C(2));
    CHECK(b.sum() == UINT32_C(7));
}

TEST_CASE("cheshire_cat_test_type_sum_test")
{
    const pl::test::cheshire_cat_test_type a{UINT32_C(0), "0"};
    const pl::test::cheshire_cat_test_type b{UINT32_C(500), "7000"};
    CHECK(a.sum() == UINT32_C(0));
    CHECK(b.sum() == UINT32_C(7500));
}

TEST_CASE("cheshire_cat_test_type_equality_comparison_test")
{
    const pl::test::cheshire_cat_test_type a{UINT32_C(5), "6"};
    const pl::test::cheshire_cat_test_type b{UINT32_C(5), "6"};
    const pl::test::cheshire_cat_test_type c{UINT32_C(6), "5"};

    CHECK(a == b);
    CHECK(a != c);
    CHECK(b == a);
    CHECK(b != c);
    CHECK(c != a);
    CHECK(c != b);
}
