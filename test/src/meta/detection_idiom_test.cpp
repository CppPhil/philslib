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
#include "../../../include/pl/meta/detection_idiom.hpp" // pl::meta::nonesuch, pl::meta::is_detected, pl::meta::detected_t, pl::meta::detected_or, pl::meta::detected_or_t, pl::meta::is_detected_exact, pl::meta::is_detected_convertible
#include <ciso646> // not
#include <cstddef> // std::ptrdiff_t
#include <utility> // std::declval
#include <string> // std::string
#include <vector> // std::vector
#include <type_traits> // std::is_same, std::true_type, std::false_type

namespace pl
{
namespace test
{
namespace
{
template <typename Ty>
using CopyAssign
    = decltype(std::declval<Ty &>() = std::declval<const Ty &>());

struct CopyAssignable
{
};

struct CopyAssignableWeirdReturnType
{
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Weffc++"
#endif // CR_COMPILER == CR_COMPILER_GCC
    void operator=(const CopyAssignableWeirdReturnType &)
    {
    }
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // CR_COMPILER == CR_COMPILER_GCC
};

struct NotCopyAssignable
{
    NotCopyAssignable &operator=(const NotCopyAssignable &) = delete;
};

template <typename Ty>
using NestedSizeType = typename Ty::size_type;

template <typename Ty>
using NestedDifferenceType = typename Ty::difference_type;

struct HasDiffType
{
    using difference_type = int;
};

struct HasNoDiffType
{
};

template <typename Ty>
using difference_type
    = pl::meta::detected_or_t<std::ptrdiff_t, NestedDifferenceType, Ty>;
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("is_detected_test")
{
    PL_TEST_STATIC_ASSERT(pl::meta::is_detected<
            pl::test::CopyAssign,
            pl::test::CopyAssignable
        >::value
    );

    PL_TEST_STATIC_ASSERT(pl::meta::is_detected<
            pl::test::CopyAssign,
            pl::test::CopyAssignableWeirdReturnType
        >::value
    );

    PL_TEST_STATIC_ASSERT(not pl::meta::is_detected<
            pl::test::CopyAssign,
            pl::test::NotCopyAssignable
        >::value
    );

    PL_TEST_STATIC_ASSERT(pl::meta::is_detected<
            pl::test::NestedSizeType,
            std::vector<double>
        >::value
    );

    PL_TEST_STATIC_ASSERT(not pl::meta::is_detected<
            pl::test::NestedSizeType,
            pl::test::CopyAssignable
        >::value
    );

    CHECK_UNARY(true);
}

TEST_CASE("detected_t_test")
{
    PL_TEST_STATIC_ASSERT(std::is_same<pl::meta::detected_t<
            pl::test::CopyAssign,
            pl::test::CopyAssignable
        >, pl::test::CopyAssign<pl::test::CopyAssignable>>::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<pl::meta::detected_t<
            pl::test::CopyAssign,
            pl::test::CopyAssignableWeirdReturnType
        >, pl::test::CopyAssign<pl::test::CopyAssignableWeirdReturnType>>::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<pl::meta::detected_t<
            pl::test::CopyAssign,
            pl::test::NotCopyAssignable
        >, pl::meta::nonesuch>::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<pl::meta::detected_t<
            pl::test::NestedSizeType,
            std::vector<double>
        >, pl::test::NestedSizeType<std::vector<double>>>::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<pl::meta::detected_t<
            pl::test::NestedSizeType,
            pl::test::CopyAssignable
        >, pl::meta::nonesuch>::value
    );

    CHECK_UNARY(true);
}

TEST_CASE("detected_or_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<
            pl::meta::detected_or<
                std::ptrdiff_t,
                pl::test::NestedDifferenceType,
                pl::test::HasDiffType
            >::value_t,
            std::true_type
        >::value
    );

    PL_TEST_STATIC_ASSERT(
        std::is_same<
            pl::meta::detected_or<
                std::ptrdiff_t,
                pl::test::NestedDifferenceType,
                pl::test::HasDiffType
            >::type,
            pl::test::NestedDifferenceType<pl::test::HasDiffType>
        >::value
    );

    PL_TEST_STATIC_ASSERT(
        std::is_same<
            pl::meta::detected_or<
                std::ptrdiff_t,
                pl::test::NestedDifferenceType,
                pl::test::HasNoDiffType
            >::value_t,
            std::false_type
        >::value
    );

    PL_TEST_STATIC_ASSERT(
        std::is_same<
            pl::meta::detected_or<
                std::ptrdiff_t,
                pl::test::NestedDifferenceType,
                pl::test::HasNoDiffType
            >::type,
            std::ptrdiff_t
        >::value
    );

    CHECK_UNARY(true);
}

TEST_CASE("detected_or_t_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<
            pl::test::difference_type<pl::test::HasDiffType>,
            int
        >::value
    );

    PL_TEST_STATIC_ASSERT(
        std::is_same<
            pl::test::difference_type<pl::test::HasNoDiffType>,
            std::ptrdiff_t
        >::value
    );

    CHECK_UNARY(true);
}

TEST_CASE("is_detected_exact_test")
{
    PL_TEST_STATIC_ASSERT(pl::meta::is_detected_exact<
            pl::test::CopyAssignable &,
            pl::test::CopyAssign,
            pl::test::CopyAssignable
        >::value
    );

    PL_TEST_STATIC_ASSERT(not pl::meta::is_detected_exact<
            pl::test::CopyAssignableWeirdReturnType &,
            pl::test::CopyAssign,
            pl::test::CopyAssignableWeirdReturnType
        >::value
    );

    PL_TEST_STATIC_ASSERT(not pl::meta::is_detected_exact<
            pl::test::NotCopyAssignable &,
            pl::test::CopyAssign,
            pl::test::NotCopyAssignable
        >::value
    );

    CHECK_UNARY(true);
}

TEST_CASE("is_detected_convertible")
{
    struct DiffTypeConvertible
    {
        using difference_type = short;
    };

    struct DiffTypeNonConvertible
    {
        using difference_type = std::string;
    };

    PL_TEST_STATIC_ASSERT(
        pl::meta::is_detected_convertible<
            int,
            pl::test::NestedDifferenceType,
            pl::test::HasDiffType
        >::value
    );

    PL_TEST_STATIC_ASSERT(
        pl::meta::is_detected_convertible<
            int,
            pl::test::NestedDifferenceType,
            DiffTypeConvertible
        >::value
    );

    PL_TEST_STATIC_ASSERT(
        not pl::meta::is_detected_convertible<
            int,
            pl::test::NestedDifferenceType,
            DiffTypeNonConvertible
        >::value
    );

    CHECK_UNARY(true);
}
