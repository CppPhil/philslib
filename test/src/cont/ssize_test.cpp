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
#include "../../../include/pl/cont/ssize.hpp" // pl::cont::ssize
#include "../../include/static_assert.hpp"    // PL_TEST_STATIC_ASSERT
#include <array>                              // std::array
#include <bitset>                             // std::bitset
#include <cstddef>                            // std::size_t
#include <cstdint>                            // std::uint8_t
#include <deque>                              // std::deque
#include <initializer_list>                   // std::initializer_list
#include <list>                               // std::list
#include <map>                                // std::map, std::multimap
#include <queue>                              // std::queue
#include <regex>                              // std::smatch
#include <set>                                // std::set, std::multiset
#include <stack>                              // std::stack
#include <string>                             // std::string, std::wstring
#include <unordered_map> // std::unordered_map, std::unordered_multimap
#include <unordered_set> // std::unordered_set, std::unordered_multiset
#include <valarray>      // std::valarray
#include <vector>        // std::vector

TEST_CASE("c_array_ssize_test")
{
    int          arr1[]{1, 2, 3, 4, 5};
    const double arr2[]{0.0, 1.1};

    CHECK(pl::cont::ssize(arr1) == 5);
    CHECK(pl::cont::ssize(arr2) == 2);
}

TEST_CASE("map_ssize_test")
{
    std::map<int, float>                map{{5, 1.1F}, {7, 5.9F}};
    const std::map<std::string, double> map2{
        {"Text", 5.5}, {"More Text", 7.7}, {"Your Text Here", 9.9}, {"0", 0.0}};

    CHECK(pl::cont::ssize(map) == 2);
    CHECK(pl::cont::ssize(map2) == 4);
}

TEST_CASE("multimap_ssize_test")
{
    std::multimap<int, int>                 multimap1{{1, 2}, {1, 9}, {1, 20}};
    const std::multimap<std::string, float> multimap2{{"A", 5.5F},
                                                      {"B", 6.6F},
                                                      {"C", 7.7F},
                                                      {"C", 8.8F},
                                                      {"D", 9.9F},
                                                      {"?", 0.0F}};

    CHECK(pl::cont::ssize(multimap1) == 3);
    CHECK(pl::cont::ssize(multimap2) == 6);
}

TEST_CASE("string_ssize_test")
{
    std::string       string1{"Hello World!"};
    const std::string string2{"Sample text"};

    CHECK(pl::cont::ssize(string1) == 12);
    CHECK(pl::cont::ssize(string2) == 11);
}

TEST_CASE("wstring_ssize_test")
{
    std::wstring       wstring1{L"ABCDEFG"};
    const std::wstring wstring2{L"Text"};

    CHECK(pl::cont::ssize(wstring1) == 7);
    CHECK(pl::cont::ssize(wstring2) == 4);
}

TEST_CASE("set_ssize_test")
{
    std::set<int>        set1{1, 2, 3, 4, 5, 6};
    const std::set<long> set2{3L, 5L, 9L};

    CHECK(pl::cont::ssize(set1) == 6);
    CHECK(pl::cont::ssize(set2) == 3);
}

TEST_CASE("multiset_ssize_test")
{
    std::multiset<int>          multiset1{1, 1, 1, 1, 1, 1, 1};
    const std::multiset<double> multiset2{1.1, 2.2, 3.3, 3.3, 2.2, 1.1};

    CHECK(pl::cont::ssize(multiset1) == 7);
    CHECK(pl::cont::ssize(multiset2) == 6);
}

TEST_CASE("list_ssize_test")
{
    std::list<std::string>  list1{"Hello World", "This is a text."};
    const std::list<double> list2{1.1, 2.2, 33.33, 44.44};

    CHECK(pl::cont::ssize(list1) == 2);
    CHECK(pl::cont::ssize(list2) == 4);
}

TEST_CASE("std_array_ssize_test")
{
    static constexpr std::size_t               size{3U};
    std::array<int, size>                      array1{{1, 2, 3}};
    const std::array<unsigned long long, size> array2{{5ULL, 10ULL, 20ULL}};

    CHECK(pl::cont::ssize(array1) == 3);
    CHECK(pl::cont::ssize(array2) == 3);
}

TEST_CASE("deque_ssize_test")
{
    std::deque<int>                deque1{1, 2, 3, 4, 5};
    const std::deque<std::uint8_t> deque2{0xAA, 0xBB, 0xCC, 0xDD};

    CHECK(pl::cont::ssize(deque1) == 5);
    CHECK(pl::cont::ssize(deque2) == 4);
}

TEST_CASE("queue_ssize_test")
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

    CHECK(pl::cont::ssize(queue1) == 7);
    CHECK(pl::cont::ssize(queue2) == 7);
}

TEST_CASE("stack_ssize_test")
{
    std::stack<int> stack1{};
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    const std::stack<int> stack2{stack1};

    CHECK(pl::cont::ssize(stack1) == 3);
    CHECK(pl::cont::ssize(stack2) == 3);
}

TEST_CASE("bitset_ssize_test")
{
    static constexpr std::size_t bits{16U};
    std::bitset<bits>            bitset1{0b1111'0000'1111'1010ULL};
    const std::bitset<bits>      bitset2{0b1010'1010'0101'0101ULL};

    CHECK(pl::cont::ssize(bitset1) == 16);
    CHECK(pl::cont::ssize(bitset2) == 16);
}

TEST_CASE("smatch_ssize_test")
{
    const std::regex  regex{R"(TEXT(\d+)TEXT)"};
    const std::string string{"TEXT112451641TEXT"};

    std::smatch smatch{};

    CHECK(pl::cont::ssize(smatch) == 0);

    std::regex_match(string, smatch, regex);

    CHECK(pl::cont::ssize(smatch) == 2);
}

TEST_CASE("vector_ssize_test")
{
    std::vector<int>       vector1{1, 2, 3, 4};
    const std::vector<int> vector2{7, 8, 9, 10, 11};

    CHECK(pl::cont::ssize(vector1) == 4);
    CHECK(pl::cont::ssize(vector2) == 5);
}

TEST_CASE("valarray_ssize_test")
{
    std::valarray<double>       valarray1{1.1, 2.2, 3.3};
    const std::valarray<double> valarray2{5.5, 6.6, 7.7, 8.8};

    CHECK(pl::cont::ssize(valarray1) == 3);
    CHECK(pl::cont::ssize(valarray2) == 4);
}

TEST_CASE("unordered_map_ssize_test")
{
    std::unordered_map<int, int> unordered_map1{{1, 1}, {1, 1}, {2, 2}, {2, 2}};
    const std::unordered_map<int, int> unordered_map2{
        {1, 1}, {1, 1}, {2, 2}, {2, 2}, {5, 5}};

    CHECK(pl::cont::ssize(unordered_map1) == 2);
    CHECK(pl::cont::ssize(unordered_map2) == 3);
}

TEST_CASE("unordered_multimap_ssize_test")
{
    std::unordered_multimap<int, int> unordered_multimap1{
        {1, 1}, {1, 1}, {2, 2}, {2, 2}};
    const std::unordered_multimap<int, int> unordered_multimap2{
        {1, 1}, {1, 1}, {2, 2}, {2, 2}, {5, 5}};

    CHECK(pl::cont::ssize(unordered_multimap1) == 4);
    CHECK(pl::cont::ssize(unordered_multimap2) == 5);
}

TEST_CASE("unordered_set_ssize_test")
{
    std::unordered_set<int>       unordered_set1{1, 1, 2};
    const std::unordered_set<int> unordered_set2{1, 1, 2};

    CHECK(pl::cont::ssize(unordered_set1) == 2);
    CHECK(pl::cont::ssize(unordered_set2) == 2);
}

TEST_CASE("unordered_multiset_ssize_test")
{
    std::unordered_multiset<int>       unordered_multiset1{1, 1, 2};
    const std::unordered_multiset<int> unordered_multiset2{1, 1, 2};

    CHECK(pl::cont::ssize(unordered_multiset1) == 3);
    CHECK(pl::cont::ssize(unordered_multiset2) == 3);
}

TEST_CASE("initializer_list_ssize_test")
{
    std::initializer_list<const char*>       init_list1{"Hello", "World"};
    const std::initializer_list<const char*> init_list2{
        "This", "is", "some", "text."};
    const std::initializer_list<void*> init_list3{};

    CHECK(pl::cont::ssize(init_list1) == 2);
    CHECK(pl::cont::ssize(init_list2) == 4);
    CHECK(pl::cont::ssize(init_list3) == 0);
}

TEST_CASE("ssize_constexpr_array_test")
{
    static constexpr int a[]{1, 2, 3, 4, 5};
    PL_TEST_STATIC_ASSERT(pl::cont::ssize(a) == 5);

    CHECK_UNARY(true);
}

TEST_CASE("ssize_constexpr_std_array_test")
{
    static constexpr std::array<int, 3U> a{{1, 2, 3}};
    PL_TEST_STATIC_ASSERT(pl::cont::ssize(a) == 3);

    CHECK_UNARY(true);
}

#if PL_COMPILER != PL_COMPILER_MSVC
TEST_CASE("ssize_constexpr_initializer_list_test")
{
    static constexpr std::initializer_list<int> il{};
    static constexpr std::initializer_list<int> il2{1, 2, 3, 4};
    PL_TEST_STATIC_ASSERT(pl::cont::ssize(il) == 0);
    PL_TEST_STATIC_ASSERT(pl::cont::ssize(il2) == 4);

    CHECK_UNARY(true);
}
#endif
