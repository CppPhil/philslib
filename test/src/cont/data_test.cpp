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
#endif                                       // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/cont/data.hpp" // pl::cont::data
#include "../../include/static_assert.hpp"   // PL_TEST_STATIC_ASSERT
#include <array>                             // std::array
#include <cstddef>                           // std::size_t
#include <initializer_list>                  // std::initializer_list
#include <string>                            // std::string
#include <type_traits>                       // std::is_same
#include <vector>                            // std::vector

TEST_CASE("std_array_data_test")
{
    static constexpr std::size_t size{10U};

    std::array<int, size>       array1{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    const std::array<int, size> array2{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(array1)), int*>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(array2)), const int*>::value);

    CHECK(pl::cont::data(array1) == array1.data());
    CHECK(pl::cont::data(array2) == array2.data());
}

TEST_CASE("string_data_test")
{
    std::string       string1{"Hello"};
    const std::string string2{"World"};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(string1)), char*>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(string2)), const char*>::value);

    CHECK(pl::cont::data(string1) == &string1[0]);
    CHECK(pl::cont::data(string2) == string2.data());
}

TEST_CASE("wstring_data_test")
{
    std::wstring       wstring1{L"Test"};
    const std::wstring wstring2{L"another test"};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(wstring1)), wchar_t*>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(wstring2)),
                     const wchar_t*>::value);

    CHECK(pl::cont::data(wstring1) == &wstring1[0]);
    CHECK(pl::cont::data(wstring2) == wstring2.data());
}

TEST_CASE("vector_data_test")
{
    std::vector<double>       vector1{1.1, 1.2, 1.3};
    const std::vector<double> vector2{5.4, 5.3};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(vector1)), double*>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(vector2)), const double*>::value);

    CHECK(pl::cont::data(vector1) == vector1.data());
    CHECK(pl::cont::data(vector2) == vector2.data());
}

TEST_CASE("initializer_list_data_test")
{
    std::initializer_list<int>       il1{1, 2, 3};
    const std::initializer_list<int> il2{1, 2, 3};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(il1)), const int*>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(il2)), const int*>::value);

    CHECK(pl::cont::data(il1) == &*il1.begin());
    CHECK(pl::cont::data(il2) == &*il2.begin());
}

TEST_CASE("c_array_data_test")
{
    char       c_array1[] = "Test";
    const char c_array2[]
        = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(c_array1)), char*>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::data(c_array2)), const char*>::value);

    CHECK(pl::cont::data(c_array1) == &c_array1[0U]);
    CHECK(pl::cont::data(c_array2) == &c_array2[0U]);

    CHECK(pl::cont::data(c_array1) == static_cast<char*>(c_array1));
    CHECK(pl::cont::data(c_array2) == static_cast<const char*>(c_array2));
}

TEST_CASE("data_constexpr_array_test")
{
    static constexpr int a[]{1, 2, 3, 4, 5};
    PL_TEST_STATIC_ASSERT(pl::cont::data(a) == a);

    CHECK_UNARY(true);
}

TEST_CASE("data_constexpr_initializer_list_test")
{
    static constexpr std::initializer_list<int> il{1, 2, 3};
    PL_TEST_STATIC_ASSERT(pl::cont::data(il) == il.begin());

    CHECK_UNARY(true);
}
