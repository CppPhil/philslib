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
#include "../../../include/pl/cont/make_array.hpp" // pl::cont::makeArray
#include "../../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include <type_traits> // std::is_same

TEST_CASE("test_make_array_basic")
{
    auto array1 = pl::cont::makeArray(1, 2, 3, 4, 5);
    const auto array2 = pl::cont::makeArray(5U, 6U, 7U);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(array1), std::array<int, 5>>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(array2), const std::array<unsigned, 3>>::value);

    REQUIRE(array1.size() == 5U);
    CHECK(array1[0U] == 1);
    CHECK(array1[1U] == 2);
    CHECK(array1[2U] == 3);
    CHECK(array1[3U] == 4);
    CHECK(array1[4U] == 5);

    REQUIRE(array2.size() == 3U);
    CHECK(array2[0U] == 5U);
    CHECK(array2[1U] == 6U);
    CHECK(array2[2U] == 7U);
}

TEST_CASE("test_make_array_common_type")
{
    const auto array = pl::cont::makeArray(1, 1L, 2LL);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(array)::value_type, long long>::value);

    REQUIRE(array.size() == 3U);
    CHECK(array[0U] == 1LL);
    CHECK(array[1U] == 1LL);
    CHECK(array[2U] == 2LL);

    const auto anotherArray = pl::cont::makeArray(1.1F, 2.2);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(anotherArray)::value_type, double>::value);

    REQUIRE(anotherArray.size() == 2U);
    CHECK(anotherArray[0U] == doctest::Approx(1.1));
    CHECK(anotherArray[1U] == doctest::Approx(2.2));
}

TEST_CASE("test_make_array_desired_type")
{
    const auto array1 = pl::cont::makeArray<double>(5.3F, 1.1F);
    const auto array2
        = pl::cont::makeArray<long long>(1, 2L, static_cast<short>(5));

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(array1)::value_type, double>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(array2)::value_type, long long>::value);

    REQUIRE(array1.size() == 2U);
    CHECK(array1[0U] == doctest::Approx(5.3));
    CHECK(array1[1U] == doctest::Approx(1.1));

    REQUIRE(array2.size() == 3U);
    CHECK(array2[0U] == 1LL);
    CHECK(array2[1U] == 2LL);
    CHECK(array2[2U] == 5LL);
}
