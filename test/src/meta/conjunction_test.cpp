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
#include "../../../include/pl/meta/conjunction.hpp" // pl::meta::conjunction
#include "../../include/static_assert.hpp"          // PL_TEST_STATIC_ASSERT
#include <ciso646>                                  // not
#include <string> // std::string, std::literals::string_literals::operator""s
#include <type_traits> // std::enable_if_t, std::is_same, std::true_type, std::false_type

namespace pl {
namespace test {
namespace {
template<typename Ty, typename... Args>
auto foo(Ty&&, Args&&...) -> std::enable_if_t<
    pl::meta::conjunction<std::is_same<Ty, Args>...>::value,
    std::true_type>;

template<typename Ty, typename... Args>
auto foo(Ty&&, Args&&...) -> std::enable_if_t<
    not pl::meta::conjunction<std::is_same<Ty, Args>...>::value,
    std::false_type>;
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("conjunction_positive_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::test::foo(5, 1, 2)), std::true_type>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::test::foo(5.5, 1.1, 3.3)), std::true_type>::
            value);

    PL_TEST_STATIC_ASSERT(pl::meta::conjunction<
                          std::is_same<int, int>,
                          std::is_pointer<double*>,
                          std::is_integral<short>>::value);

    CHECK_UNARY(true);
}

TEST_CASE("conjunction_negative_test")
{
    using namespace std::literals::string_literals;

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::test::foo(1, 2, 3, 4U)), std::false_type>::
            value);

    PL_TEST_STATIC_ASSERT(std::is_same<
                          decltype(pl::test::foo("a"s, "b"s, "c")),
                          std::false_type>::value);

    PL_TEST_STATIC_ASSERT(not pl::meta::conjunction<
                          std::is_floating_point<long double>,
                          std::is_const<int>>::value);

    CHECK_UNARY(true);
}
