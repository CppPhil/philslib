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
#include "../../../include/pl/meta/container_traits.hpp" // pl::meta::container_traits_category
#include <type_traits> // std::is_same

TEST_CASE("container_traits_test")
{
    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::vector<int>>,
            pl::meta::vectorlike_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::deque<int>>,
            pl::meta::vectorlike_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::string>,
            pl::meta::vectorlike_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::list<int>>,
            pl::meta::listlike_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::forward_list<int>>,
            pl::meta::listlike_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::set<int>>,
            pl::meta::associative_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::multiset<int>>,
            pl::meta::associative_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::unordered_set<int>>,
            pl::meta::associative_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::unordered_multiset<int>>,
            pl::meta::associative_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::map<int, int>>,
            pl::meta::associative_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::multimap<int, int>>,
            pl::meta::associative_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::unordered_map<int, int>>,
            pl::meta::associative_tag
        >::value
    );

    PL_TEST_STATIC_ASSERT(std::is_same<
            pl::meta::container_traits_category<std::unordered_multimap<int, int>>,
            pl::meta::associative_tag
        >::value
    );

    CHECK_UNARY(true);
}
