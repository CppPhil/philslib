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
#include "../../include/pl/named_operator.hpp" // pl::makeNamedOperator
#include <cmath> // std::pow
#include <iterator> // std::begin, std::end
#include <vector> // std::vector
#include <algorithm> // std::find

TEST_CASE("named_operator_test")
{
    using namespace pl::named_operator;

    const auto pow = pl::makeNamedOperator([](double base, double exponent) {
        return std::pow(base, exponent);
    });

    const auto contains = pl::makeNamedOperator(
        [](const auto &container, const auto &value) {
            const auto end = std::end(container);
            return std::find(std::begin(container), end, value) != end;
    });

    CHECK((2.0 <pow> 3.0) == doctest::Approx(8.0));

    double val{ 2.0 };
    val <pow>= 4.0;

    CHECK(val == doctest::Approx(16.0));

    const std::vector<int> v{ 1, 2, 3, 4, 5 };
    CHECK_UNARY(v <contains> 3);
    CHECK_UNARY_FALSE(v <contains> 0);

}
