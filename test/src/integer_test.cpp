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
#include "../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include "../../include/pl/no_macro_substitution.hpp" // PL_NO_MACRO_SUBSTITUTION
#include "../../include/pl/integer.hpp" // pl::Int, pl::Uint
#include <cstddef> // std::size_t
#include <cstdint> // std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t
#include <climits> // CHAR_BIT
#include <limits> // std::numeric_limits
#include <type_traits> // std::is_same

TEST_CASE("integer_test_types")
{
    PL_TEST_STATIC_ASSERT(std::is_same<pl::Int<8>, std::int8_t>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<pl::Int<16>, std::int16_t>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<pl::Int<32>, std::int32_t>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<pl::Int<64>, std::int64_t>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<pl::Uint<8>, std::uint8_t>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<pl::Uint<16>, std::uint16_t>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<pl::Uint<32>, std::uint32_t>::value);
    PL_TEST_STATIC_ASSERT(std::is_same<pl::Uint<64>, std::uint64_t>::value);

    CHECK_UNARY(true);
}

TEST_CASE("integer_test_byte_sizes")
{
    PL_TEST_STATIC_ASSERT(sizeof(pl::Int<8>) == static_cast<std::size_t>(1U));
    PL_TEST_STATIC_ASSERT(sizeof(pl::Int<16>) == static_cast<std::size_t>(2U));
    PL_TEST_STATIC_ASSERT(sizeof(pl::Int<32>) == static_cast<std::size_t>(4U));
    PL_TEST_STATIC_ASSERT(sizeof(pl::Int<64>) == static_cast<std::size_t>(8U));
    PL_TEST_STATIC_ASSERT(sizeof(pl::Uint<8>) == static_cast<std::size_t>(1U));
    PL_TEST_STATIC_ASSERT(sizeof(pl::Uint<16>) == static_cast<std::size_t>(2U));
    PL_TEST_STATIC_ASSERT(sizeof(pl::Uint<32>) == static_cast<std::size_t>(4U));
    PL_TEST_STATIC_ASSERT(sizeof(pl::Uint<64>) == static_cast<std::size_t>(8U));

    CHECK_UNARY(true);
}

TEST_CASE("integer_test_bit_sizes")
{
    PL_TEST_STATIC_ASSERT((sizeof(pl::Int<8>) * CHAR_BIT) == 8U);
    PL_TEST_STATIC_ASSERT((sizeof(pl::Int<16>) * CHAR_BIT) == 16U);
    PL_TEST_STATIC_ASSERT((sizeof(pl::Int<32>) * CHAR_BIT) == 32U);
    PL_TEST_STATIC_ASSERT((sizeof(pl::Int<64>) * CHAR_BIT) == 64U);
    PL_TEST_STATIC_ASSERT((sizeof(pl::Uint<8>) * CHAR_BIT) == 8U);
    PL_TEST_STATIC_ASSERT((sizeof(pl::Uint<16>) * CHAR_BIT) == 16U);
    PL_TEST_STATIC_ASSERT((sizeof(pl::Uint<32>) * CHAR_BIT) == 32U);
    PL_TEST_STATIC_ASSERT((sizeof(pl::Uint<64>) * CHAR_BIT) == 64U);

    CHECK_UNARY(true);
}

TEST_CASE("integer_test_min_max")
{
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Int<8>>::min PL_NO_MACRO_SUBSTITUTION()
        == std::numeric_limits<std::int8_t>::min PL_NO_MACRO_SUBSTITUTION());
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Int<16>>::min PL_NO_MACRO_SUBSTITUTION()
        == std::numeric_limits<std::int16_t>::min PL_NO_MACRO_SUBSTITUTION());
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Int<32>>::min PL_NO_MACRO_SUBSTITUTION()
        == std::numeric_limits<std::int32_t>::min PL_NO_MACRO_SUBSTITUTION());
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Int<64>>::min PL_NO_MACRO_SUBSTITUTION()
        == std::numeric_limits<std::int64_t>::min PL_NO_MACRO_SUBSTITUTION());
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Int<8>>::max PL_NO_MACRO_SUBSTITUTION()
        == std::numeric_limits<std::int8_t>::max PL_NO_MACRO_SUBSTITUTION());
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Int<16>>::max PL_NO_MACRO_SUBSTITUTION()
        == std::numeric_limits<std::int16_t>::max PL_NO_MACRO_SUBSTITUTION());
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Int<32>>::max PL_NO_MACRO_SUBSTITUTION()
        == std::numeric_limits<std::int32_t>::max PL_NO_MACRO_SUBSTITUTION());
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Int<64>>::max PL_NO_MACRO_SUBSTITUTION()
        == std::numeric_limits<std::int64_t>::max PL_NO_MACRO_SUBSTITUTION());
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Uint<8>>::min PL_NO_MACRO_SUBSTITUTION()
        == 0U);
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Uint<16>>::min PL_NO_MACRO_SUBSTITUTION()
        == 0U);
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Uint<32>>::min PL_NO_MACRO_SUBSTITUTION()
        == 0U);
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Uint<64>>::min PL_NO_MACRO_SUBSTITUTION()
        == 0U);
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Uint<8>>::max PL_NO_MACRO_SUBSTITUTION()
        == 0xFFU);
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Uint<16>>::max PL_NO_MACRO_SUBSTITUTION()
        == 0xFFFFU);
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Uint<32>>::max PL_NO_MACRO_SUBSTITUTION()
        == 0xFFFFFFFFU);
    PL_TEST_STATIC_ASSERT(
        std::numeric_limits<pl::Uint<64>>::max PL_NO_MACRO_SUBSTITUTION()
        == 0xFFFFFFFFFFFFFFFFU);

    CHECK_UNARY(true);
}
