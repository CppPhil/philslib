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
#include "../../include/pl/no_macro_substitution.hpp" // PL_NO_MACRO_SUBSTITUTION
#include "../../include/pl/os.hpp" // PL_OS, PL_OS_WINDOWS
#include <cstdint> // std::uint32_t
#include <limits> // std::numeric_limits
#if PL_OS == PL_OS_WINDOWS
#   include <vfw.h> // min
#   include <Windef.h> // max
#endif // PL_OS == PL_OS_WINDOWS

#if !defined(min)
#   define min(a, b)  (((a) < (b)) ? (a) : (b))
#endif // !defined(min)

#if !defined(max)
#   define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif // !defined(max)

TEST_CASE("no_macro_substitution_test")
{
    constexpr auto minValue
        = std::numeric_limits<std::uint32_t>::min PL_NO_MACRO_SUBSTITUTION();
    constexpr auto maxValue
        = std::numeric_limits<std::uint32_t>::max PL_NO_MACRO_SUBSTITUTION();

    CHECK(minValue == 0U);
    CHECK(maxValue == 0xFFFFFFFFU);
}
