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
#endif                                     // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/cont/at.hpp" // pl::cont::at
#include "../../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include <initializer_list>                // std::intializer_list
#include <string>                          // std::string
#include <type_traits>                     // std::is_same
#include <vector>                          // std::vector

TEST_CASE("at_test")
{
    int       a1[]{1, 2, 3};
    const int a2[]{4, 5, 6};

    std::vector<int>       vec1{1, 2, 3, 4};
    const std::vector<int> vec2{5, 6, 7, 8};
    const std::vector<int> empty_vector{};

    std::initializer_list<std::string>       il1{"test", "text"};
    const std::initializer_list<std::string> il2{"Hello", "World"};
    std::initializer_list<std::string>       empty_init_list{};

    SUBCASE("type_test")
    {
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(pl::cont::at(a1, 0U)), int&>::value);

        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(pl::cont::at(a2, 0U)), const int&>::value);

        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(pl::cont::at(vec1, 0U)), int&>::value);

        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(pl::cont::at(vec2, 0U)), const int&>::value);

        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(pl::cont::at(il1, 0U)), std::string>::value);

        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(pl::cont::at(il2, 0U)), std::string>::value);

        CHECK_UNARY(true);
    }

    SUBCASE("positive_tests")
    {
        CHECK(pl::cont::at(a1, 0U) == 1);
        CHECK(pl::cont::at(a1, 1U) == 2);
        CHECK(pl::cont::at(a1, 2U) == 3);

        CHECK(pl::cont::at(a2, 0U) == 4);
        CHECK(pl::cont::at(a2, 1U) == 5);
        CHECK(pl::cont::at(a2, 2U) == 6);

        CHECK(pl::cont::at(vec1, 0U) == 1);
        CHECK(pl::cont::at(vec1, 1U) == 2);
        CHECK(pl::cont::at(vec1, 2U) == 3);
        CHECK(pl::cont::at(vec1, 3U) == 4);

        CHECK(pl::cont::at(vec2, 0U) == 5);
        CHECK(pl::cont::at(vec2, 1U) == 6);
        CHECK(pl::cont::at(vec2, 2U) == 7);
        CHECK(pl::cont::at(vec2, 3U) == 8);

        CHECK(pl::cont::at(il1, 0U) == "test");
        CHECK(pl::cont::at(il1, 1U) == "text");

        CHECK(pl::cont::at(il2, 0U) == "Hello");
        CHECK(pl::cont::at(il2, 1U) == "World");
    }

    SUBCASE("negative_tests")
    {
        CHECK_THROWS_AS(pl::cont::at(a1, 3U), std::out_of_range);
        CHECK_THROWS_AS(pl::cont::at(a2, 3U), std::out_of_range);

        CHECK_THROWS_AS(pl::cont::at(vec1, 4U), std::out_of_range);
        CHECK_THROWS_AS(pl::cont::at(vec2, 4U), std::out_of_range);
        CHECK_THROWS_AS(pl::cont::at(empty_vector, 0U), std::out_of_range);

        CHECK_THROWS_AS(pl::cont::at(il1, 2U), std::out_of_range);
        CHECK_THROWS_AS(pl::cont::at(il2, 2U), std::out_of_range);
        CHECK_THROWS_AS(pl::cont::at(empty_init_list, 0U), std::out_of_range);

        CHECK_THROWS_AS(
            pl::cont::at(a1, static_cast<std::size_t>(-1)), std::out_of_range);
        CHECK_THROWS_AS(
            pl::cont::at(a2, static_cast<std::size_t>(-1)), std::out_of_range);
        CHECK_THROWS_AS(
            pl::cont::at(vec1, static_cast<std::size_t>(-1)),
            std::out_of_range);
        CHECK_THROWS_AS(
            pl::cont::at(vec2, static_cast<std::size_t>(-1)),
            std::out_of_range);
        CHECK_THROWS_AS(
            pl::cont::at(empty_vector, static_cast<std::size_t>(-1)),
            std::out_of_range);
        CHECK_THROWS_AS(
            pl::cont::at(il1, static_cast<std::size_t>(-1)), std::out_of_range);
        CHECK_THROWS_AS(
            pl::cont::at(il2, static_cast<std::size_t>(-1)), std::out_of_range);
        CHECK_THROWS_AS(
            pl::cont::at(empty_init_list, static_cast<std::size_t>(-1)),
            std::out_of_range);
    }
}
