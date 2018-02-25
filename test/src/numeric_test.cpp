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
#include "../../include/pl/numeric.hpp" // pl::isEven, pl::isOdd, pl::isBetween

TEST_CASE("is_even_test")
{
    CHECK_UNARY(pl::isEven(-2));
    CHECK_UNARY_FALSE(pl::isEven(-1));
    CHECK_UNARY(pl::isEven(0));
    CHECK_UNARY_FALSE(pl::isEven(1));
}

TEST_CASE("is_odd_test")
{
    CHECK_UNARY_FALSE(pl::isOdd(-2));
    CHECK_UNARY(pl::isOdd(-1));
    CHECK_UNARY_FALSE(pl::isOdd(0));
    CHECK_UNARY(pl::isOdd(1));
}

TEST_CASE("is_between_test")
{
    CHECK_UNARY(pl::isBetween(5,  5, 5));
    CHECK_UNARY(pl::isBetween(5,  4, 5));
    CHECK_UNARY(pl::isBetween(5,  5, 6));
    CHECK_UNARY(pl::isBetween(5,  4, 6));

    CHECK_UNARY(pl::isBetween(0,  0, 0));
    CHECK_UNARY(pl::isBetween(0, -1, 0));
    CHECK_UNARY(pl::isBetween(0,  0, 1));
    CHECK_UNARY(pl::isBetween(0, -1, 1));

    CHECK_UNARY_FALSE(pl::isBetween(5, 6, 6));
}
