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
#include "../../../include/pl/cont/to_array.hpp" // pl::cont::toArray
#include "../../include/static_assert.hpp"       // PL_TEST_STATIC_ASSERT
#include <string>                                // std::string
#include <type_traits>                           // std::is_same

TEST_CASE("to_array_general_test")
{
    int          cArray1[]{1, 2, 3, 4, 5};
    const double cArray2[]{1.1, 2.2, 3.3};

    auto       array1 = pl::cont::toArray(cArray1);
    const auto array2 = pl::cont::toArray(cArray2);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(array1), std::array<int, 5U>>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(array2), const std::array<double, 3U>>::value);

    REQUIRE(array1.size() == 5U);
    CHECK(array1[0U] == 1);
    CHECK(array1[1U] == 2);
    CHECK(array1[2U] == 3);
    CHECK(array1[3U] == 4);
    CHECK(array1[4U] == 5);

    REQUIRE(array2.size() == 3U);
    CHECK(array2[0U] == doctest::Approx(1.1));
    CHECK(array2[1U] == doctest::Approx(2.2));
    CHECK(array2[2U] == doctest::Approx(3.3));
}

TEST_CASE("to_array_one_element_test")
{
    const std::string cArray[]{std::string{"Hello World"}};

    const auto array = pl::cont::toArray(cArray);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(array),
                     const std::array<std::string, 1U>>::value);

    REQUIRE(array.size() == 1U);
    CHECK(array[0U] == std::string{"Hello World"});
}
