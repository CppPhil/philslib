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
#endif                               // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/hash.hpp" // pl::hash
#include <cstddef>                   // std::size_t
#include <functional>                // std::hash
#include <iterator>                  // std::end
#include <string>                    // std::string
#include <unordered_set>             // std::unordered_set
#include <utility>                   // std::move

namespace pl {
namespace test {
namespace {
class hashable;
} // anonymous namespace
} // namespace test
} // namespace pl

namespace std {
template<>
struct hash<::pl::test::hashable>;
} // namespace std

namespace pl {
namespace test {
namespace {
class hashable {
public:
  hashable(std::string string, int integer)
    : m_string{std::move(string)}, m_integer{integer}
  {
  }

  friend ::std::hash<hashable>;

  friend bool operator==(const hashable& a, const hashable& b)
  {
    return (a.m_string == b.m_string) && (a.m_integer == b.m_integer);
  }

private:
  std::string m_string;
  int         m_integer;
};
} // anonymous namespace
} // namespace test
} // namespace pl

namespace std {
template<>
struct hash<::pl::test::hashable> {
  size_t operator()(const ::pl::test::hashable& hashable) const
  {
    return ::pl::hash(hashable.m_string, hashable.m_integer);
  }
};
} // namespace std

TEST_CASE("hash_positive_test")
{
  static const std::string str{"Test"};
  constexpr int            integer{5};

  std::size_t hash_seed{0U};
  pl::detail::add_hash(hash_seed, str);
  pl::detail::add_hash(hash_seed, integer);

  pl::test::hashable obj{str, integer};
  pl::test::hashable copy{obj};

  std::hash<pl::test::hashable> hasher{};

  CHECK(hasher(obj) == hash_seed);
  CHECK(hasher(copy) == hash_seed);
  CHECK(hasher(obj) == hasher(copy));
}

TEST_CASE("hash_negative_test")
{
  pl::test::hashable a{"text", 5};
  pl::test::hashable b{
    "text",
    6,
  };

  CHECK(
    std::hash<pl::test::hashable>{}(a) != std::hash<pl::test::hashable>{}(b));
}

TEST_CASE("hash_unordered_set_test")
{
  std::unordered_set<pl::test::hashable> set{pl::test::hashable{"test", 25}};

  CHECK(set.find(pl::test::hashable{"test", 25}) != std::end(set));
  CHECK(set.find(pl::test::hashable{"text", 25}) == std::end(set));

  set.emplace("hash_test", 50);
  CHECK(set.find(pl::test::hashable{"hash_test", 50}) != std::end(set));
}
