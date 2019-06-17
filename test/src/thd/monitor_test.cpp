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
#endif                                         // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/thd/monitor.hpp" // pl::thd::monitor
#include <cstring>                             // std::strcmp
#include <string>                              // std::string
#include <utility>                             // std::move

namespace pl {
namespace test {
namespace {
class monitor_test_type {
public:
    using this_type = monitor_test_type;

    monitor_test_type(int i, double d, std::string s)
        : m_i{i}, m_d{d}, m_s{std::move(s)}
    {
    }

    double      d() const noexcept { return m_d; }
    void        d(double d) noexcept { m_d = d; }
    void        set_d_to_25() noexcept { d(25.0); }
    const char* str() const noexcept { return m_s.data(); }
    int         m_i;

private:
    double      m_d;
    std::string m_s;
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("monitor_test")
{
    pl::thd::monitor<pl::test::monitor_test_type> monitor{
        pl::test::monitor_test_type{1, 2.0, "text"}};

    CHECK(
        monitor([](pl::test::monitor_test_type& o) { return o.d(); })
        == doctest::Approx{2.0});

    monitor(&pl::test::monitor_test_type::set_d_to_25);

    CHECK(
        monitor(static_cast<double (pl::test::monitor_test_type::*)() const>(
            &pl::test::monitor_test_type::d))
        == doctest::Approx{25.0});

    CHECK(std::strcmp(monitor(&pl::test::monitor_test_type::str), "text") == 0);

    CHECK(monitor(&pl::test::monitor_test_type::m_i) == 1);
}
