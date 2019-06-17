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
#include "../../../include/pl/meta/disable_if.hpp" // pl::meta::disable_if_t
#include "../../include/static_assert.hpp"         // PL_TEST_STATIC_ASSERT
#include <ciso646>                                 // not
#include <type_traits> // std::true_type, std::false_type, std::is_same

namespace pl {
namespace test {
namespace {
template<typename Ty>
auto foo(Ty &&)
    -> pl::meta::disable_if_t<not std::is_same<Ty, int>::value, std::true_type>;

template<typename Ty>
auto foo(Ty &&)
    -> pl::meta::disable_if_t<std::is_same<Ty, int>::value, std::false_type>;
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("disable_if_positive_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::test::foo(true)), std::false_type>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::test::foo('a')), std::false_type>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::test::foo(4U)), std::false_type>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::test::foo("text")), std::false_type>::value);

    CHECK_UNARY(true);
}

TEST_CASE("disable_if_negative_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<decltype(pl::test::foo(1)), std::true_type>::value);

    CHECK_UNARY(true);
}
