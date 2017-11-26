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
#include "../../../include/pl/meta/is_reference_wrapper.hpp" // pl::meta::is_reference_wrapper, pl::meta::is_not_reference_wrapper
#include <ciso646> // not
#include <unordered_map> // std::unordered_map

TEST_CASE("is_reference_wrapper_positive_test")
{
    using Ty1 = std::reference_wrapper<int>;
    using Ty2 = std::reference_wrapper<double>;
    using Ty3 = std::reference_wrapper<float>;
    using Ty4 = std::reference_wrapper<long long>;

    PL_TEST_STATIC_ASSERT(pl::meta::is_reference_wrapper<Ty1>::value);
    PL_TEST_STATIC_ASSERT(not pl::meta::is_not_reference_wrapper<Ty1>::value);

    PL_TEST_STATIC_ASSERT(pl::meta::is_reference_wrapper<Ty2>::value);
    PL_TEST_STATIC_ASSERT(not pl::meta::is_not_reference_wrapper<Ty2>::value);

    PL_TEST_STATIC_ASSERT(pl::meta::is_reference_wrapper<Ty3>::value);
    PL_TEST_STATIC_ASSERT(not pl::meta::is_not_reference_wrapper<Ty3>::value);

    PL_TEST_STATIC_ASSERT(pl::meta::is_reference_wrapper<Ty4>::value);
    PL_TEST_STATIC_ASSERT(not pl::meta::is_not_reference_wrapper<Ty4>::value);

    CHECK_UNARY(true);
}

TEST_CASE("is_reference_wrapper_negative_test")
{
    using Ty1 = unsigned long long;
    using Ty2 = wchar_t;
    using Ty3 = short;
    using Ty4 = std::unordered_map<int, const char *>;

    PL_TEST_STATIC_ASSERT(not pl::meta::is_reference_wrapper<Ty1>::value);
    PL_TEST_STATIC_ASSERT(pl::meta::is_not_reference_wrapper<Ty1>::value);

    PL_TEST_STATIC_ASSERT(not pl::meta::is_reference_wrapper<Ty2>::value);
    PL_TEST_STATIC_ASSERT(pl::meta::is_not_reference_wrapper<Ty2>::value);

    PL_TEST_STATIC_ASSERT(not pl::meta::is_reference_wrapper<Ty3>::value);
    PL_TEST_STATIC_ASSERT(pl::meta::is_not_reference_wrapper<Ty3>::value);

    PL_TEST_STATIC_ASSERT(not pl::meta::is_reference_wrapper<Ty4>::value);
    PL_TEST_STATIC_ASSERT(pl::meta::is_not_reference_wrapper<Ty4>::value);

    CHECK_UNARY(true);
}
