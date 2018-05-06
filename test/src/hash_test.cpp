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
#include <ciso646>                   // and
#include <cstddef>                   // std::size_t
#include <functional>                // std::hash
#include <iterator>                  // std::end
#include <string>                    // std::string
#include <unordered_set>             // std::unordered_set
#include <utility>                   // std::move

namespace pl {
namespace test {
namespace {
class Hashable;
} // anonymous namespace
} // namespace test
} // namespace pl

namespace std {
template <>
struct hash<::pl::test::Hashable>;
} // namespace std

namespace pl {
namespace test {
namespace {
class Hashable {
public:
    Hashable(std::string string, int integer)
        : m_string{std::move(string)}, m_integer{integer}
    {
    }

    friend ::std::hash<Hashable>;

    friend bool operator==(const Hashable& a, const Hashable& b)
    {
        return (a.m_string == b.m_string) and (a.m_integer == b.m_integer);
    }

private:
    std::string m_string;
    int         m_integer;
};
} // anonymous namespace
} // namespace test
} // namespace pl

namespace std {
template <>
struct hash<::pl::test::Hashable> {
    size_t operator()(const ::pl::test::Hashable& hashable) const
    {
        return ::pl::hash(hashable.m_string, hashable.m_integer);
    }
};
} // namespace std

TEST_CASE("hash_positive_test")
{
    static const std::string str{"Test"};
    constexpr int            integer{5};

    std::size_t hashSeed{0U};
    pl::detail::addHash(hashSeed, str);
    pl::detail::addHash(hashSeed, integer);

    pl::test::Hashable obj{str, integer};
    pl::test::Hashable copy{obj};

    std::hash<pl::test::Hashable> hasher{};

    CHECK(hasher(obj) == hashSeed);
    CHECK(hasher(copy) == hashSeed);
    CHECK(hasher(obj) == hasher(copy));
}

TEST_CASE("hash_negative_test")
{
    pl::test::Hashable a{"text", 5};
    pl::test::Hashable b{
        "text", 6,
    };

    CHECK(
        std::hash<pl::test::Hashable>{}(a)
        != std::hash<pl::test::Hashable>{}(b));
}

TEST_CASE("hash_unordered_set_test")
{
    std::unordered_set<pl::test::Hashable> set{pl::test::Hashable{"test", 25}};

    CHECK(set.find(pl::test::Hashable{"test", 25}) != std::end(set));
    CHECK(set.find(pl::test::Hashable{"text", 25}) == std::end(set));

    set.emplace("hashTest", 50);
    CHECK(set.find(pl::test::Hashable{"hashTest", 50}) != std::end(set));
}
