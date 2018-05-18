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
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/cont/make_array.hpp" // pl::cont::makeArray
#include "../../include/pl/make_from_tuple.hpp" // pl::makeFromTuple
#include <array>                                // std::array
#include <cstdint>                              // std::uint32_t, UINT32_C
#include <string> // std::string, std::to_string, std::literals::string_literals::operator""s
#include <tuple>   // std::tuple, std::make_tuple
#include <utility> // std::pair, std::make_pair, std::move

namespace pl {
namespace test {
namespace {
class test_type {
public:
    test_type(std::string s, std::uint32_t i, void* p)
        : m_s{std::move(s)}, m_i{i}, m_p{p}
    {
    }

    test_type(std::string s, std::uint32_t i)
        : test_type{std::move(s), i, nullptr}
    {
    }

    test_type(std::uint32_t a1, std::uint32_t a2)
        : test_type{std::to_string(a1), a2}
    {
    }

    test_type(const test_type&) = default;

    test_type& operator=(const test_type&) = default;

    const std::string& s() const noexcept { return m_s; }
    std::uint32_t      i() const noexcept { return m_i; }
    void*              p() const noexcept { return m_p; }
private:
    std::string   m_s;
    std::uint32_t m_i;
    void*         m_p;
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("make_from_tuple_test")
{
    using namespace std::literals::string_literals;

    const pl::test::test_type a{pl::makeFromTuple<pl::test::test_type>(
        std::make_tuple("test"s, UINT32_C(25), nullptr))};

    CHECK(a.s() == "test"s);
    CHECK(a.i() == UINT32_C(25));
    CHECK(a.p() == nullptr);

    const pl::test::test_type b{pl::makeFromTuple<pl::test::test_type>(
        std::make_pair("text"s, UINT32_C(50)))};

    CHECK(b.s() == "text"s);
    CHECK(b.i() == UINT32_C(50));
    CHECK(b.p() == nullptr);

    const pl::test::test_type c{pl::makeFromTuple<pl::test::test_type>(
        pl::cont::make_array(UINT32_C(7), UINT32_C(500)))};

    CHECK(c.s() == "7"s);
    CHECK(c.i() == UINT32_C(500));
    CHECK(c.p() == nullptr);
}
