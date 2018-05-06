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
#include "../../../include/pl/meta/nested_types.hpp" // pl::meta::value_type, pl::meta::allocator_type, pl::meta::difference_type, pl::meta::size_type, pl::meta::key_type, pl::meta::mapped_type, pl::meta::element_type, pl::meta::deleter_type, pl::meta::container_type
#include "../../include/static_assert.hpp"           // PL_TEST_STATIC_ASSERT
#include <deque>                                     // std::deque
#include <memory>                                    // std::unique_ptr
#include <stack>                                     // std::stack
#include <string>                                    // std::string
#include <type_traits>                               // std::is_same
#include <unordered_map>                             // std::unordered_map
#include <vector>                                    // std::vector

TEST_CASE("value_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::value_type<std::vector<int>>, int>::value);
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::value_type<std::deque<std::string>>,
                     std::string>::value);

    CHECK_UNARY(true);
}

TEST_CASE("allocator_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::allocator_type<std::vector<int>>,
                     std::allocator<int>>::value);

    CHECK_UNARY(true);
}

TEST_CASE("difference_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::difference_type<std::vector<int>>,
                     std::vector<int>::difference_type>::value);

    CHECK_UNARY(true);
}

TEST_CASE("size_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::size_type<std::vector<double>>,
                     std::vector<double>::size_type>::value);

    CHECK_UNARY(true);
}

TEST_CASE("key_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::key_type<std::unordered_map<int, double>>,
                     int>::value);

    CHECK_UNARY(true);
}

TEST_CASE("mapped_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::mapped_type<std::unordered_map<int, double>>,
                     double>::value);

    CHECK_UNARY(true);
}

TEST_CASE("element_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::element_type<std::unique_ptr<float>>,
                     float>::value);

    CHECK_UNARY(true);
}

TEST_CASE("deleter_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::deleter_type<std::unique_ptr<std::string>>,
                     std::default_delete<std::string>>::value);

    CHECK_UNARY(true);
}

TEST_CASE("container_type_test")
{
    PL_TEST_STATIC_ASSERT(
        std::is_same<pl::meta::container_type<std::stack<const char*>>,
                     std::deque<const char*>>::value);

    CHECK_UNARY(true);
}
