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
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/random_number_generator.hpp" // pl::RandomNumberGenerator
#include "../../include/pl/named_operator.hpp" // pl::makeNamedOperator
#include "../../include/pl/numeric.hpp" // pl::isBetween
#include <ciso646> // or, not
#include <cstdint> // std::uint16_t, std::int16_t, std::uint32_t, std::int32_t, std::uint64_t, std::int64_t, ...
#include <iterator> // std::begin, std::end
#include <vector> // std::vector
#include <algorithm> // std::find

namespace pl
{
namespace test
{
namespace
{
template <typename Engine, typename IntType>
bool isOk(
    pl::RandomNumberGenerator<Engine> &rng,
    IntType lowerBound,
    IntType upperBound)
{
    IntType result{ rng.template generate<IntType>(lowerBound, upperBound) };
    return pl::isBetween(result, lowerBound, upperBound);
}
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("random_number_generator_test")
{
    static constexpr std::uint16_t uint16Lower{ UINT16_C(0) };
    static constexpr std::uint16_t uint16Upper{ UINT16_C(5) };
    static constexpr std::int16_t int16Lower{ INT16_C(-50) };
    static constexpr std::int16_t int16Upper{ INT16_C(300) };
    static constexpr std::uint32_t uint32Lower{ UINT32_C(7) };
    static constexpr std::uint32_t uint32Upper{ UINT32_MAX };
    static constexpr std::int32_t int32Lower{ INT32_MIN };
    static constexpr std::int32_t int32Upper{ INT32_C(5555) };
    static constexpr std::uint64_t uint64Lower{ UINT64_C(3) };
    static constexpr std::uint64_t uint64Upper{ UINT64_C(99999999) };
    static constexpr std::int64_t int64Lower{ INT64_MIN };
    static constexpr std::int64_t int64Upper{ INT64_MAX };
    const float fLower{ 0.0F };
    const float fUpper{ 5.0F };
    const double dLower{ 20.85 };
    const double dUpper{ 50.0 };
    const long double ldLower{ 33.3333L };
    const long double ldUpper{ 70.0001L };

    using namespace pl::named_operator;

    const auto contains = pl::makeNamedOperator(
        [](const auto &container, const auto &value) {
            const auto end = std::end(container);
            return std::find(std::begin(container), end, value) != end;
    });

    pl::RandomNumberGenerator<> mt19937{ };
    pl::RandomNumberGenerator<std::mt19937_64> mt19937_64{ };
    const auto useMt19937 = [&mt19937](auto lower, auto upper) {
        return pl::test::isOk(mt19937, lower, upper);
    };
    const auto useMt19937_64 = [&mt19937_64](auto lower, auto upper) {
        return pl::test::isOk(mt19937_64, lower, upper);
    };

    CHECK_UNARY(useMt19937(uint16Lower, uint16Upper));
    CHECK_UNARY(useMt19937(int16Lower, int16Upper));
    CHECK_UNARY(useMt19937(uint32Lower, uint32Upper));
    CHECK_UNARY(useMt19937(int32Lower, int32Upper));
    CHECK_UNARY(useMt19937(uint64Lower, uint64Upper));
    CHECK_UNARY(useMt19937(int64Lower, int64Upper));
    CHECK_UNARY(useMt19937(fLower, fUpper));
    CHECK_UNARY(useMt19937(dLower, dUpper));
    CHECK_UNARY(useMt19937(ldLower, ldUpper));

    CHECK_UNARY(useMt19937_64(uint16Lower, uint16Upper));
    CHECK_UNARY(useMt19937_64(int16Lower, int16Upper));
    CHECK_UNARY(useMt19937_64(uint32Lower, uint32Upper));
    CHECK_UNARY(useMt19937_64(int32Lower, int32Upper));
    CHECK_UNARY(useMt19937_64(uint64Lower, uint64Upper));
    CHECK_UNARY(useMt19937_64(int64Lower, int64Upper));
    CHECK_UNARY(useMt19937_64(fLower, fUpper));
    CHECK_UNARY(useMt19937_64(dLower, dUpper));
    CHECK_UNARY(useMt19937_64(ldLower, ldUpper));

    const bool boolResult1{ mt19937.generate<bool>(1.0) };
    CHECK_UNARY(boolResult1);

    const bool boolResult2{ mt19937_64.generate<bool>(1.0) };
    CHECK_UNARY(boolResult2);

    const bool boolResult3{ mt19937.generate<bool>(0.0) };
    CHECK_UNARY_FALSE(boolResult3);

    const bool boolResult4{ mt19937_64.generate<bool>(0.0) };
    CHECK_UNARY_FALSE(boolResult4);

    const std::vector<int> vector1{ 1, 2, 3, 4, 5, 6 };
    std::vector<int> copy{ vector1 };

    SUBCASE("test_shuffle_iter_mt19937") {
        mt19937.shuffle(std::begin(copy), std::end(copy));
        for (int i : vector1) {
            CHECK_UNARY(copy <contains> i);
        }
    }

    SUBCASE("test_shuffle_iter_mt19937_64") {
        mt19937_64.shuffle(std::begin(copy), std::end(copy));
        for (int i : vector1) {
            CHECK_UNARY(copy <contains> i);
        }
    }

    SUBCASE("test_shuffle_ranged_mt19937") {
        mt19937.shuffle(copy);
        for (int i : vector1) {
            CHECK_UNARY(copy <contains> i);
        }
    }

    SUBCASE("test_shuffle_ranged_mt19937_64") {
        mt19937_64.shuffle(copy);
        for (int i : vector1) {
            CHECK_UNARY(copy <contains> i);
        }
    }
}
