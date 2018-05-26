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
#include "../../../include/pl/cont/front.hpp" // pl::cont::front
#include "../../include/static_assert.hpp"    // PL_TEST_STATIC_ASSERT
#include <array>                              // std::array
#include <cstddef>                            // std::size_t
#include <deque>                              // std::deque
#include <forward_list>                       // std::forward_list
#include <initializer_list>                   // std::initializer_list
#include <list>                               // std::list
#include <queue>                              // std::queue
#include <string>                             // std::string
#include <type_traits>                        // std::is_same
#include <vector>                             // std::vector

TEST_CASE("list_front_test")
{
    std::list<int>       list1{1, 2, 3, 4, 5};
    const std::list<int> list2{3, 4, 5};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(list1)), int&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(list2)), const int&>::value);

    CHECK(pl::cont::front(list1) == 1);
    CHECK(pl::cont::front(list2) == 3);
}

#if (PL_COMPILER != PL_COMPILER_GCC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(6, 4, 0))
TEST_CASE("std_array_front_test")
{
    static constexpr std::size_t size{3U};
    std::array<unsigned, size>       array1{{1U, 2U, 3U}};
    const std::array<unsigned, size> array2{{4U, 5U, 6U}};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(array1)), unsigned&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(array2)),
                     const unsigned&>::value);

    CHECK(pl::cont::front(array1) == 1U);
    CHECK(pl::cont::front(array2) == 4U);
}
#endif

TEST_CASE("deque_front_test")
{
    std::deque<long>       deque1{1L, 2L, 3L};
    const std::deque<long> deque2{4L, 5L, 6L};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(deque1)), long&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(deque2)), const long&>::value);

    CHECK(pl::cont::front(deque1) == 1L);
    CHECK(pl::cont::front(deque2) == 4L);
}

TEST_CASE("queue_front_test")
{
    std::queue<int> queue1{};
    queue1.push(1);
    queue1.push(2);
    queue1.push(3);

    const std::queue<int> queue2{queue1};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(queue1)), int&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(queue2)), const int&>::value);

    CHECK(pl::cont::front(queue1) == 1);
    CHECK(pl::cont::front(queue2) == 1);
}

TEST_CASE("string_front_test")
{
    std::string       string1{"Test"};
    const std::string string2{"Hello World"};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(string1)), char&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(string2)), const char&>::value);

    CHECK(pl::cont::front(string1) == 'T');
    CHECK(pl::cont::front(string2) == 'H');
}

TEST_CASE("vector_front_test")
{
    std::vector<int>       vector1{0, 1, 2, 3, 4, 5, 6, 7, 8};
    const std::vector<int> vector2{10, 11, 11, 11, 22, 22, 22, 10};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(vector1)), int&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(vector2)), const int&>::value);

    CHECK(pl::cont::front(vector1) == 0);
    CHECK(pl::cont::front(vector2) == 10);
}

TEST_CASE("forward_list_front_test")
{
    std::forward_list<int>       forward_list1{0, 1, 2, 3, 4};
    const std::forward_list<int> forward_list2{5, 6, 7, 8, 9, 10, 11};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(forward_list1)), int&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(forward_list2)),
                     const int&>::value);

    CHECK(pl::cont::front(forward_list1) == 0);
    CHECK(pl::cont::front(forward_list2) == 5);
}

TEST_CASE("c_array_front_test")
{
    std::size_t       array1[]{1U, 2U, 3U, 4U};
    const std::size_t array2[]{7U, 8U, 9U};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(array1)), std::size_t&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(array2)),
                     const std::size_t&>::value);

    CHECK(pl::cont::front(array1) == 1U);
    CHECK(pl::cont::front(array2) == 7U);
}

TEST_CASE("initializer_list_front_test")
{
    using namespace std::literals::string_literals;

    std::initializer_list<int>               il{1, 2, 3, 4, 5};
    const std::initializer_list<std::string> il2{"text"s};

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(il)), const int&>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::cont::front(il2)),
                     const std::string&>::value);

    CHECK(pl::cont::front(il) == 1);
    CHECK(pl::cont::front(il2) == "text"s);
}

TEST_CASE("front_constexpr_array_test")
{
    static constexpr int a[]{1, 2, 3, 4};
    PL_TEST_STATIC_ASSERT(pl::cont::front(a) == 1);

    CHECK_UNARY(true);
}

TEST_CASE("front_constexpr_std_array_test")
{
    static constexpr std::array<int, 3U> a{{1, 2, 3}};
    PL_TEST_STATIC_ASSERT(pl::cont::front(a) == 1);

    CHECK_UNARY(true);
}

TEST_CASE("front_constexpr_initializer_list_test")
{
    static constexpr std::initializer_list<int> il{1, 2, 3, 4, 5, 6};
    PL_TEST_STATIC_ASSERT(pl::cont::front(il) == 1);

    CHECK_UNARY(true);
}
