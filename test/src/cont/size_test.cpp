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
#include "../../../include/pl/cont/size.hpp" // pl::cont::size
#include "../../include/static_assert.hpp"   // PL_TEST_STATIC_ASSERT
#include <array>                             // std::array
#include <bitset>                            // std::bitset
#include <cstddef>                           // std::size_t
#include <cstdint>                           // std::uint8_t
#include <deque>                             // std::deque
#include <initializer_list>                  // std::initializer_list
#include <list>                              // std::list
#include <map>                               // std::map, std::multimap
#include <queue>                             // std::queue
#include <regex>                             // std::smatch
#include <set>                               // std::set, std::multiset
#include <stack>                             // std::stack
#include <string>                            // std::string, std::wstring
#include <unordered_map> // std::unordered_map, std::unordered_multimap
#include <unordered_set> // std::unordered_set, std::unordered_multiset
#include <valarray>      // std::valarray
#include <vector>        // std::vector

TEST_CASE("c_array_size_test")
{
    int          arr1[]{1, 2, 3, 4, 5};
    const double arr2[]{0.0, 1.1};

    CHECK(pl::cont::size(arr1) == 5U);
    CHECK(pl::cont::size(arr2) == 2U);
}

TEST_CASE("map_size_test")
{
    std::map<int, float>                map{{5, 1.1F}, {7, 5.9F}};
    const std::map<std::string, double> map2{
        {"Text", 5.5}, {"More Text", 7.7}, {"Your Text Here", 9.9}, {"0", 0.0}};

    CHECK(pl::cont::size(map) == 2U);
    CHECK(pl::cont::size(map2) == 4U);
}

TEST_CASE("multimap_size_test")
{
    std::multimap<int, int>                 multimap1{{1, 2}, {1, 9}, {1, 20}};
    const std::multimap<std::string, float> multimap2{{"A", 5.5F},
                                                      {"B", 6.6F},
                                                      {"C", 7.7F},
                                                      {"C", 8.8F},
                                                      {"D", 9.9F},
                                                      {"?", 0.0F}};

    CHECK(pl::cont::size(multimap1) == 3U);
    CHECK(pl::cont::size(multimap2) == 6U);
}

TEST_CASE("string_size_test")
{
    std::string       string1{"Hello World!"};
    const std::string string2{"Sample text"};

    CHECK(pl::cont::size(string1) == 12U);
    CHECK(pl::cont::size(string2) == 11U);
}

TEST_CASE("wstring_size_test")
{
    std::wstring       wstring1{L"ABCDEFG"};
    const std::wstring wstring2{L"Text"};

    CHECK(pl::cont::size(wstring1) == 7U);
    CHECK(pl::cont::size(wstring2) == 4U);
}

TEST_CASE("set_size_test")
{
    std::set<int>        set1{1, 2, 3, 4, 5, 6};
    const std::set<long> set2{3L, 5L, 9L};

    CHECK(pl::cont::size(set1) == 6U);
    CHECK(pl::cont::size(set2) == 3U);
}

TEST_CASE("multiset_size_test")
{
    std::multiset<int>          multiset1{1, 1, 1, 1, 1, 1, 1};
    const std::multiset<double> multiset2{1.1, 2.2, 3.3, 3.3, 2.2, 1.1};

    CHECK(pl::cont::size(multiset1) == 7U);
    CHECK(pl::cont::size(multiset2) == 6U);
}

TEST_CASE("list_size_test")
{
    std::list<std::string>  list1{"Hello World", "This is a text."};
    const std::list<double> list2{1.1, 2.2, 33.33, 44.44};

    CHECK(pl::cont::size(list1) == 2U);
    CHECK(pl::cont::size(list2) == 4U);
}

TEST_CASE("std_array_size_test")
{
    static constexpr std::size_t size{3U};
    std::array<int, size>                      array1{{1, 2, 3}};
    const std::array<unsigned long long, size> array2{{5ULL, 10ULL, 20ULL}};

    CHECK(pl::cont::size(array1) == 3U);
    CHECK(pl::cont::size(array2) == 3U);
}

TEST_CASE("deque_size_test")
{
    std::deque<int>                deque1{1, 2, 3, 4, 5};
    const std::deque<std::uint8_t> deque2{0xAA, 0xBB, 0xCC, 0xDD};

    CHECK(pl::cont::size(deque1) == 5U);
    CHECK(pl::cont::size(deque2) == 4U);
}

TEST_CASE("queue_size_test")
{
    std::queue<float> queue1{};
    queue1.push(0.1F);
    queue1.push(1.1F);
    queue1.push(2.1F);
    queue1.push(3.1F);
    queue1.push(4.1F);
    queue1.push(5.1F);
    queue1.push(6.1F);
    const std::queue<float> queue2{queue1};

    CHECK(pl::cont::size(queue1) == 7U);
    CHECK(pl::cont::size(queue2) == 7U);
}

TEST_CASE("stack_size_test")
{
    std::stack<int> stack1{};
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    const std::stack<int> stack2{stack1};

    CHECK(pl::cont::size(stack1) == 3U);
    CHECK(pl::cont::size(stack2) == 3U);
}

TEST_CASE("bitset_size_test")
{
    static constexpr std::size_t bits{16U};
    std::bitset<bits>            bitset1{0b1111'0000'1111'1010ULL};
    const std::bitset<bits>      bitset2{0b1010'1010'0101'0101ULL};

    CHECK(pl::cont::size(bitset1) == 16U);
    CHECK(pl::cont::size(bitset2) == 16U);
}

TEST_CASE("smatch_size_test")
{
    const std::regex  regex{R"(TEXT(\d+)TEXT)"};
    const std::string string{"TEXT112451641TEXT"};

    std::smatch smatch{};

    CHECK(pl::cont::size(smatch) == 0U);

    std::regex_match(string, smatch, regex);

    CHECK(pl::cont::size(smatch) == 2U);
}

TEST_CASE("vector_size_test")
{
    std::vector<int>       vector1{1, 2, 3, 4};
    const std::vector<int> vector2{7, 8, 9, 10, 11};

    CHECK(pl::cont::size(vector1) == 4U);
    CHECK(pl::cont::size(vector2) == 5U);
}

TEST_CASE("valarray_size_test")
{
    std::valarray<double>       valarray1{1.1, 2.2, 3.3};
    const std::valarray<double> valarray2{5.5, 6.6, 7.7, 8.8};

    CHECK(pl::cont::size(valarray1) == 3U);
    CHECK(pl::cont::size(valarray2) == 4U);
}

TEST_CASE("unordered_map_size_test")
{
    std::unordered_map<int, int> unordered_map1{{1, 1}, {1, 1}, {2, 2}, {2, 2}};
    const std::unordered_map<int, int> unordered_map2{
        {1, 1}, {1, 1}, {2, 2}, {2, 2}, {5, 5}};

    CHECK(pl::cont::size(unordered_map1) == 2U);
    CHECK(pl::cont::size(unordered_map2) == 3U);
}

TEST_CASE("unordered_multimap_size_test")
{
    std::unordered_multimap<int, int> unordered_multimap1{
        {1, 1}, {1, 1}, {2, 2}, {2, 2}};
    const std::unordered_multimap<int, int> unordered_multimap2{
        {1, 1}, {1, 1}, {2, 2}, {2, 2}, {5, 5}};

    CHECK(pl::cont::size(unordered_multimap1) == 4U);
    CHECK(pl::cont::size(unordered_multimap2) == 5U);
}

TEST_CASE("unordered_set_size_test")
{
    std::unordered_set<int>       unordered_set1{1, 1, 2};
    const std::unordered_set<int> unordered_set2{1, 1, 2};

    CHECK(pl::cont::size(unordered_set1) == 2U);
    CHECK(pl::cont::size(unordered_set2) == 2U);
}

TEST_CASE("unordered_multiset_size_test")
{
    std::unordered_multiset<int>       unordered_multiset1{1, 1, 2};
    const std::unordered_multiset<int> unordered_multiset2{1, 1, 2};

    CHECK(pl::cont::size(unordered_multiset1) == 3U);
    CHECK(pl::cont::size(unordered_multiset2) == 3U);
}

TEST_CASE("initializer_list_size_test")
{
    std::initializer_list<const char*>       init_list1{"Hello", "World"};
    const std::initializer_list<const char*> init_list2{
        "This", "is", "some", "text."};
    const std::initializer_list<void*> init_list3{};

    CHECK(pl::cont::size(init_list1) == 2U);
    CHECK(pl::cont::size(init_list2) == 4U);
    CHECK(pl::cont::size(init_list3) == 0U);
}

TEST_CASE("size_constexpr_array_test")
{
    static constexpr int a[]{1, 2, 3, 4, 5};
    PL_TEST_STATIC_ASSERT(pl::cont::size(a) == 5U);

    CHECK_UNARY(true);
}

TEST_CASE("size_constexpr_std_array_test")
{
    static constexpr std::array<int, 3U> a{{1, 2, 3}};
    PL_TEST_STATIC_ASSERT(pl::cont::size(a) == 3U);

    CHECK_UNARY(true);
}

#if PL_COMPILER != PL_COMPILER_MSVC
TEST_CASE("size_constexpr_initializer_list_test")
{
    static constexpr std::initializer_list<int> il{};
    static constexpr std::initializer_list<int> il2{1, 2, 3, 4};
    PL_TEST_STATIC_ASSERT(pl::cont::size(il) == 0U);
    PL_TEST_STATIC_ASSERT(pl::cont::size(il2) == 4U);

    CHECK_UNARY(true);
}
#endif
