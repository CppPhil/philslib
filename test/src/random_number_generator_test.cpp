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
#endif                                         // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/named_operator.hpp" // pl::make_named_operator
#include "../../include/pl/numeric.hpp"        // pl::is_between
#include "../../include/pl/random_number_generator.hpp" // pl::random_number_generator
#include <algorithm>                                    // std::find
#include <cstdint> // std::uint16_t, std::int16_t, std::uint32_t, std::int32_t, std::uint64_t, std::int64_t, ...
#include <iterator> // std::begin, std::end
#include <vector>   // std::vector

namespace pl {
namespace test {
namespace {
template<typename Engine, typename IntType>
bool is_ok(
    pl::random_number_generator<Engine>& rng,
    IntType                              lower_bound,
    IntType                              upper_bound)
{
    IntType result{rng.template generate<IntType>(lower_bound, upper_bound)};
    return pl::is_between(result, lower_bound, upper_bound);
}
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("random_number_generator_test")
{
    static constexpr std::uint16_t uint16_lower{UINT16_C(0)};
    static constexpr std::uint16_t uint16_upper{UINT16_C(5)};
    static constexpr std::int16_t  int16_lower{INT16_C(-50)};
    static constexpr std::int16_t  int16_upper{INT16_C(300)};
    static constexpr std::uint32_t uint32_lower{UINT32_C(7)};
    static constexpr std::uint32_t uint32_upper{UINT32_MAX};
    static constexpr std::int32_t  int32_lower{INT32_MIN};
    static constexpr std::int32_t  int32_upper{INT32_C(5555)};
    static constexpr std::uint64_t uint64_lower{UINT64_C(3)};
    static constexpr std::uint64_t uint64_upper{UINT64_C(99999999)};
    static constexpr std::int64_t  int64_lower{INT64_MIN};
    static constexpr std::int64_t  int64_upper{INT64_MAX};
    const float                    f_lower{0.0F};
    const float                    f_upper{5.0F};
    const double                   d_lower{20.85};
    const double                   d_upper{50.0};
    const long double              ld_lower{33.3333L};
    const long double              ld_upper{70.0001L};

    using namespace pl::named_operator;

    const auto contains
        = pl::make_named_operator([](const auto& container, const auto& value) {
              const auto end = std::end(container);
              return std::find(std::begin(container), end, value) != end;
          });

    pl::random_number_generator<>                mt19937{};
    pl::random_number_generator<std::mt19937_64> mt19937_64{};
    const auto use_mt19937 = [&mt19937](auto lower, auto upper) {
        return pl::test::is_ok(mt19937, lower, upper);
    };
    const auto use_mt19937_64 = [&mt19937_64](auto lower, auto upper) {
        return pl::test::is_ok(mt19937_64, lower, upper);
    };

    CHECK_UNARY(use_mt19937(uint16_lower, uint16_upper));
    CHECK_UNARY(use_mt19937(int16_lower, int16_upper));
    CHECK_UNARY(use_mt19937(uint32_lower, uint32_upper));
    CHECK_UNARY(use_mt19937(int32_lower, int32_upper));
    CHECK_UNARY(use_mt19937(uint64_lower, uint64_upper));
    CHECK_UNARY(use_mt19937(int64_lower, int64_upper));
    CHECK_UNARY(use_mt19937(f_lower, f_upper));
    CHECK_UNARY(use_mt19937(d_lower, d_upper));
    CHECK_UNARY(use_mt19937(ld_lower, ld_upper));

    CHECK_UNARY(use_mt19937_64(uint16_lower, uint16_upper));
    CHECK_UNARY(use_mt19937_64(int16_lower, int16_upper));
    CHECK_UNARY(use_mt19937_64(uint32_lower, uint32_upper));
    CHECK_UNARY(use_mt19937_64(int32_lower, int32_upper));
    CHECK_UNARY(use_mt19937_64(uint64_lower, uint64_upper));
    CHECK_UNARY(use_mt19937_64(int64_lower, int64_upper));
    CHECK_UNARY(use_mt19937_64(f_lower, f_upper));
    CHECK_UNARY(use_mt19937_64(d_lower, d_upper));
    CHECK_UNARY(use_mt19937_64(ld_lower, ld_upper));

    const bool bool_result1{mt19937.generate<bool>(1.0)};
    CHECK_UNARY(bool_result1);

    const bool bool_result2{mt19937_64.generate<bool>(1.0)};
    CHECK_UNARY(bool_result2);

    const bool bool_result3{mt19937.generate<bool>(0.0)};
    CHECK_UNARY_FALSE(bool_result3);

    const bool bool_result4{mt19937_64.generate<bool>(0.0)};
    CHECK_UNARY_FALSE(bool_result4);

    const std::vector<int> vector1{1, 2, 3, 4, 5, 6};
    std::vector<int>       copy{vector1};

    SUBCASE("test_shuffle_iter_mt19937")
    {
        mt19937.shuffle(std::begin(copy), std::end(copy));
        for (int i : vector1) {
            CHECK_UNARY(copy<contains> i);
        }
    }

    SUBCASE("test_shuffle_iter_mt19937_64")
    {
        mt19937_64.shuffle(std::begin(copy), std::end(copy));
        for (int i : vector1) {
            CHECK_UNARY(copy<contains> i);
        }
    }

    SUBCASE("test_shuffle_ranged_mt19937")
    {
        mt19937.shuffle(copy);
        for (int i : vector1) {
            CHECK_UNARY(copy<contains> i);
        }
    }

    SUBCASE("test_shuffle_ranged_mt19937_64")
    {
        mt19937_64.shuffle(copy);
        for (int i : vector1) {
            CHECK_UNARY(copy<contains> i);
        }
    }
}
