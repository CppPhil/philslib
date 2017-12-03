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
#include "../../../include/pl/meta/remove_cvref.hpp" // pl::meta::remove_cvref
#include <type_traits> // std::is_same

TEST_CASE("remove_cvref_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<int>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<int &>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<int &&>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<const int>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<volatile int>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<const volatile int>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<const int &>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<volatile int &>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<const volatile int &>, int>
            ::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<const int &&>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<volatile int &&>, int>::value);

    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::remove_cvref_t<const volatile int &&>, int>
            ::value);

    CHECK_UNARY(true);
}
