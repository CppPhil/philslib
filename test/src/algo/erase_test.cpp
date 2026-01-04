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
#include "../../../include/pl/algo/erase.hpp"
#include <algorithm> // std::all_of
#include <deque>
#include <forward_list>
#include <iterator> // std::begin, std::end
#include <list>
#include <map> // std::map, std::multimap
#include <set> // std::set, std::multiset
#include <string>
#include <unordered_map> // std::unordered_map, std::unordered_multimap
#include <unordered_set> // std::unordered_set, std::unordered_multiset
#include <vector>

TEST_CASE("erase_element_from_vector")
{
  std::vector<int> v{1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

  pl::algo::erase(v, 3);
  CHECK(v == std::vector<int>{1, 2, 4, 5, 1, 2, 4, 5});

  pl::algo::erase(v, 3);
  CHECK(v == std::vector<int>{1, 2, 4, 5, 1, 2, 4, 5});
}

TEST_CASE("erase_if_from_vector")
{
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7};

  pl::algo::erase_if(v, [](int i) { return (i & 1) == 1; });
  CHECK(v == std::vector<int>{2, 4, 6});

  pl::algo::erase_if(v, [](int i) { return (i & 1) == 1; });
  CHECK(v == std::vector<int>{2, 4, 6});
}

TEST_CASE("erase_element_from_deque")
{
  std::deque<int> dq{1, 2, 3, 1, 2, 3, 1, 2, 3};

  pl::algo::erase(dq, 2);
  CHECK(dq == std::deque<int>{1, 3, 1, 3, 1, 3});

  pl::algo::erase(dq, 2);
  CHECK(dq == std::deque<int>{1, 3, 1, 3, 1, 3});
}

TEST_CASE("erase_if_from_deque")
{
  std::deque<int> dq{1, 2, 3, 4};

  pl::algo::erase_if(dq, [](int i) { return (i >= 2) && (i <= 3); });
  CHECK(dq == std::deque<int>{1, 4});

  pl::algo::erase_if(dq, [](int i) { return (i >= 2) && (i <= 3); });
  CHECK(dq == std::deque<int>{1, 4});
}

TEST_CASE("erase_element_from_list")
{
  std::list<int> list{0, 11, 22, 33, 44, 55, 66};

  pl::algo::erase(list, 11);
  CHECK(list == std::list<int>{0, 22, 33, 44, 55, 66});

  pl::algo::erase(list, 11);
  CHECK(list == std::list<int>{0, 22, 33, 44, 55, 66});
}

TEST_CASE("erase_if_from_list")
{
  std::list<int> list{0, 10, 11, 20, 22, 30, 33};

  pl::algo::erase_if(list, [](int i) { return ((i % 100) / 10) == (i % 10); });
  CHECK(list == std::list<int>{10, 20, 30});

  pl::algo::erase_if(list, [](int i) { return ((i % 100) / 10) == (i % 10); });
  CHECK(list == std::list<int>{10, 20, 30});
}

TEST_CASE("erase_element_from_forward_list")
{
  std::forward_list<int> list{1, 2, 3, 4, 4, 3, 2, 1};

  pl::algo::erase(list, 1);
  CHECK(list == std::forward_list<int>{2, 3, 4, 4, 3, 2});

  pl::algo::erase(list, 1);
  CHECK(list == std::forward_list<int>{2, 3, 4, 4, 3, 2});
}

TEST_CASE("erase_if_from_forward_list")
{
  std::forward_list<int> list{0, 1, 2, 2, 1, 0, 0, 1, 2};

  pl::algo::erase_if(list, [](int i) { return i > 0; });
  CHECK(list == std::forward_list<int>{0, 0, 0});

  pl::algo::erase_if(list, [](int i) { return i > 0; });
  CHECK(list == std::forward_list<int>{0, 0, 0});
}

TEST_CASE("erase_element_from_set")
{
  std::set<int> set{1, 2, 3, 4, 5};

  pl::algo::erase(set, 4);
  CHECK(set == std::set<int>{1, 2, 3, 5});

  pl::algo::erase(set, 4);
  CHECK(set == std::set<int>{1, 2, 3, 5});
}

TEST_CASE("erase_if_from_set")
{
  std::set<int> set{5, 8, 9, 32, 1, 2, 14, 5, 1, 6, 5, 4, 1, 36, 40};

  pl::algo::erase_if(set, [](int i) { return (i % 3) != 0; });
  CHECK(set == std::set<int>{9, 6, 36});

  pl::algo::erase_if(set, [](int i) { return (i % 3) != 0; });
  CHECK(set == std::set<int>{9, 6, 36});
}

TEST_CASE("erase_element_from_multiset")
{
  std::multiset<int> set{1, 1, 2, 2, 5, 6, 7, 8, 1, 1, 2, 2, 5, 6, 7, 8};

  pl::algo::erase(set, 5);
  CHECK(set == std::multiset<int>{1, 1, 2, 2, 6, 7, 8, 1, 1, 2, 2, 6, 7, 8});

  pl::algo::erase(set, 5);
  CHECK(set == std::multiset<int>{1, 1, 2, 2, 6, 7, 8, 1, 1, 2, 2, 6, 7, 8});
}

TEST_CASE("erase_if_from_multiset")
{
  std::multiset<int> set{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  pl::algo::erase_if(set, [](int i) { return (i == 0) || (i == 4); });
  CHECK(set == std::multiset<int>{1, 2, 3, 5, 6, 7, 8, 9});

  pl::algo::erase_if(set, [](int i) { return (i == 0) || (i == 4); });
  CHECK(set == std::multiset<int>{1, 2, 3, 5, 6, 7, 8, 9});
}

TEST_CASE("erase_from_map")
{
  std::map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};

  SUBCASE("erase_element_from_map")
  {
    pl::algo::erase(map, 2);
    CHECK(map == std::map<int, std::string>{{1, "one"}, {3, "three"}});

    pl::algo::erase(map, 2);
    CHECK(map == std::map<int, std::string>{{1, "one"}, {3, "three"}});
  }

  SUBCASE("erase_if_from_map")
  {
    pl::algo::erase_if(map, [](const auto& p) { return (p.first & 1) == 1; });
    CHECK(map == std::map<int, std::string>{{2, "two"}});

    pl::algo::erase_if(map, [](const auto& p) { return (p.first & 1) == 1; });
    CHECK(map == std::map<int, std::string>{{2, "two"}});
  }
}

TEST_CASE("erase_from_multimap")
{
  std::multimap<int, std::string> map{
    {0, "void"}, {1, "std::nullptr_t"}, {2, "bool"}};

  SUBCASE("erase_element_from_multimap")
  {
    const std::multimap<int, std::string> expected{
      {1, "std::nullptr_t"}, {2, "bool"}};

    pl::algo::erase(map, 0);
    CHECK(map == expected);

    pl::algo::erase(map, 0);
    CHECK(map == expected);
  }

  SUBCASE("erase_if_from_multimap")
  {
    const std::multimap<int, std::string> expected{{1, "std::nullptr_t"}};

    pl::algo::erase_if(map, [](const auto& p) {
      return (p.second.front() == 'v') || (p.second.front() == 'b');
    });
    CHECK(map == expected);

    pl::algo::erase_if(map, [](const auto& p) {
      return (p.second.front() == 'v') || (p.second.front() == 'b');
    });
    CHECK(map == expected);
  }
}

TEST_CASE("erase_from_unordered_set")
{
  std::unordered_set<int> set{0, 1, 2, 3, 4, 5, 6};

  SUBCASE("erase_element_from_unordered_set")
  {
    pl::algo::erase(set, 0);
    CHECK(set == std::unordered_set<int>{1, 2, 3, 4, 5, 6});

    pl::algo::erase(set, 0);
    CHECK(set == std::unordered_set<int>{1, 2, 3, 4, 5, 6});
  }

  SUBCASE("erase_if_from_unordered_set")
  {
    pl::algo::erase_if(
      set, [](int i) { return ((i & 1) == 0) || ((i % 3) == 0); });
    CHECK(set == std::unordered_set<int>{1, 5});

    pl::algo::erase_if(
      set, [](int i) { return ((i & 1) == 0) || ((i % 3) == 0); });
    CHECK(set == std::unordered_set<int>{1, 5});
  }
}

TEST_CASE("erase_from_unordered_multiset")
{
  std::unordered_multiset<int> set{0xA, 0xB, 0xC, 0xA, 0xB, 0xC};

  SUBCASE("erase_element_from_unordered_multiset")
  {
    pl::algo::erase(set, 12);
    CHECK(set == std::unordered_multiset<int>{0xA, 0xB, 0xA, 0xB});

    pl::algo::erase(set, 12);
    CHECK(set == std::unordered_multiset<int>{0xA, 0xB, 0xA, 0xB});
  }

  SUBCASE("erase_if_from_unordered_multiset")
  {
    pl::algo::erase_if(set, [](int i) { return (i & 0b10) == 0b10; });
    CHECK(set == std::unordered_multiset<int>{0xC, 0xC});

    pl::algo::erase_if(set, [](int i) { return (i & 0b10) == 0b10; });
    CHECK(set == std::unordered_multiset<int>{0xC, 0xC});
  }
}

TEST_CASE("erase_from_unordered_map")
{
  std::unordered_map<int, std::string> map{{20, "test"}, {50, "text"}};

  SUBCASE("erase_element_from_unordered_map")
  {
    pl::algo::erase(map, 50);
    CHECK(map == std::unordered_map<int, std::string>{{20, "test"}});

    pl::algo::erase(map, 50);
    CHECK(map == std::unordered_map<int, std::string>{{20, "test"}});
  }

  SUBCASE("erase_if_from_unordered_map")
  {
    pl::algo::erase_if(map, [](const auto& p) {
      return p.second.find("s") != std::string::npos;
    });
    CHECK(map == std::unordered_map<int, std::string>{{50, "text"}});

    pl::algo::erase_if(map, [](const auto& p) {
      return p.second.find("s") != std::string::npos;
    });
    CHECK(map == std::unordered_map<int, std::string>{{50, "text"}});
  }
}

TEST_CASE("erase_from_unordered_multimap")
{
  std::unordered_multimap<int, std::string> map{
    {0, ""}, {0, "text"}, {1, " "}, {1, "text"}};

  SUBCASE("erase_element_from_unordered_multimap")
  {
    const std::unordered_multimap<int, std::string> expected{
      {0, ""}, {0, "text"}};

    pl::algo::erase(map, 1);
    CHECK(map == expected);

    pl::algo::erase(map, 1);
    CHECK(map == expected);
  }

  SUBCASE("erase_if_from_unordered_multimap")
  {
    const std::unordered_multimap<int, std::string> expected{
      {0, "text"}, {1, "text"}};

    pl::algo::erase_if(map, [](const auto& p) {
      return std::all_of(std::begin(p.second), std::end(p.second), [](char c) {
        return c == ' ';
      });
    });
    CHECK(map == expected);

    pl::algo::erase_if(map, [](const auto& p) {
      return std::all_of(std::begin(p.second), std::end(p.second), [](char c) {
        return c == ' ';
      });
    });
    CHECK(map == expected);
  }
}

TEST_CASE("erase_from_string")
{
  std::string string{"Hello World"};

  SUBCASE("erase_element_from_string")
  {
    pl::algo::erase(string, 'l');
    CHECK(string == "Heo Word");

    pl::algo::erase(string, 'l');
    CHECK(string == "Heo Word");
  }

  SUBCASE("erase_if_from_string")
  {
    pl::algo::erase_if(string, [](char c) { return (c >= 'A') && (c <= 'Z'); });
    CHECK(string == "ello orld");

    pl::algo::erase_if(string, [](char c) { return (c >= 'A') && (c <= 'Z'); });
    CHECK(string == "ello orld");
  }
}
