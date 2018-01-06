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
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // CR_COMPILER == CR_COMPILER_GCC
#include "../../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // CR_COMPILER == CR_COMPILER_GCC
#include "../../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include "../../../include/pl/meta/void_t.hpp" // pl::meta::void_t
#include <utility> // std::declval
#include <string> // std::string
#include <type_traits> // std::true_type, std::false_type, std::is_same

namespace test
{
namespace
{
template <typename, typename = pl::meta::void_t<>>
struct is_prefix_incrementable
    : public std::false_type
{
};

template <typename Ty>
struct is_prefix_incrementable<
    Ty,
    pl::meta::void_t<decltype(++std::declval<Ty &>())>>
    : public std::true_type
{
};

struct PrefixIncrementable
{
    PrefixIncrementable &operator++() noexcept
    {
        return *this;
    }
};

struct PostfixIncrementable
{
};

PostfixIncrementable operator++(PostfixIncrementable &a, int) noexcept
{
    return a;
}
} // anonymous namespace
} // namespace test

TEST_CASE("void_t_test")
{
    // avoid unused function warnings.
    test::PrefixIncrementable prefixIncrementable{ };
    test::PostfixIncrementable postfixIncrementable{ };
    ++prefixIncrementable;
    postfixIncrementable++;

    PL_TEST_STATIC_ASSERT(std::is_same<
        test::is_prefix_incrementable<int>::type,
        std::true_type>::value);

    PL_TEST_STATIC_ASSERT(std::is_same<
        test::is_prefix_incrementable<std::string>::type,
        std::false_type
    >::value);

    PL_TEST_STATIC_ASSERT(std::is_same<
        test::is_prefix_incrementable<test::PrefixIncrementable>::type,
        std::true_type
    >::value);

    PL_TEST_STATIC_ASSERT(std::is_same<
        test::is_prefix_incrementable<test::PostfixIncrementable>::type,
        std::false_type
    >::value);

    CHECK_UNARY(true);
}
