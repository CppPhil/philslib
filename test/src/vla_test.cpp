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
#endif                              // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/vla.hpp" // PL_VLA
#include <ciso646>                  // and, not
#include <cstddef>                  // std::size_t
#include <string>  // std::string, std::literals::string_literals::operator""s
#include <utility> // std::move

namespace pl {
namespace test {
namespace {
class vla_test_type {
public:
    vla_test_type(std::string s, int i) : m_s{std::move(s)}, m_i{i} {}
    const std::string& s() const noexcept { return m_s; }
    int                i() const noexcept { return m_i; }
private:
    std::string m_s;
    int         m_i;
};

bool operator==(const vla_test_type& a, const vla_test_type& b)
{
    return (a.s() == b.s()) and (a.i() == b.i());
}
} // anonymous namespace
} // namespace test
} // namespace pl

#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstack-protector"
#endif // PL_COMPILER == PL_COMPILER_GCC
TEST_CASE("vla_test")
{
    using namespace std::literals::string_literals;

    static constexpr std::size_t amount{5U};

    PL_VLA(
        pl::test::vla_test_type,
        vla,
        amount,
        pl::test::vla_test_type{"Text"s, 5});

    for (const pl::test::vla_test_type& e : vla) {
        CHECK(e == pl::test::vla_test_type{"Text"s, 5});
    }

    vla.at(0U) = pl::test::vla_test_type{"Test"s, 5};
    CHECK(vla.at(0U) == pl::test::vla_test_type{"Test"s, 5});

    vla.at(1U) = pl::test::vla_test_type{"Test"s, 6};
    CHECK(vla.at(1U) == pl::test::vla_test_type{"Test"s, 6});

    vla.at(2U) = pl::test::vla_test_type{"Test"s, 7};
    CHECK(vla.at(2U) == pl::test::vla_test_type{"Test"s, 7});

    vla.at(3U) = pl::test::vla_test_type{"Test"s, 8};
    CHECK(vla.at(3U) == pl::test::vla_test_type{"Test"s, 8});

    vla.at(4U) = pl::test::vla_test_type{"Test"s, 9};
    CHECK(vla.at(4U) == pl::test::vla_test_type{"Test"s, 9});
}
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
