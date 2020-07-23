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
#endif                                      // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/strcontains.hpp" // pl::strcontains
#include "../../include/pl/string_view.hpp" // pl::string_view
#include <string> // std::basic_string, std::literals::string_literals::operator""s

using namespace pl::literals::string_view_literals;
using namespace std::literals::string_literals;

#define CHECK_STRCONTAINS_IMPL(check_macro, haystack, needle)       \
    check_macro(pl::strcontains(haystack, needle));                 \
    check_macro(pl::strcontains(haystack##_sv, needle##_sv));       \
    check_macro(pl::strcontains(haystack##_sv, needle));            \
    check_macro(pl::strcontains(haystack, needle##_sv));            \
    check_macro(pl::strcontains(haystack##s, needle##s));           \
    check_macro(pl::strcontains(haystack##s, needle));              \
    check_macro(pl::strcontains(haystack, needle##s));              \
                                                                    \
    check_macro(pl::strcontains(u##haystack, u##needle));           \
    check_macro(pl::strcontains(u##haystack##_sv, u##needle##_sv)); \
    check_macro(pl::strcontains(u##haystack##_sv, u##needle));      \
    check_macro(pl::strcontains(u##haystack, u##needle##_sv));      \
    check_macro(pl::strcontains(u##haystack##s, u##needle##s));     \
    check_macro(pl::strcontains(u##haystack##s, u##needle));        \
    check_macro(pl::strcontains(u##haystack, u##needle##s));        \
                                                                    \
    check_macro(pl::strcontains(U##haystack, U##needle));           \
    check_macro(pl::strcontains(U##haystack##_sv, U##needle##_sv)); \
    check_macro(pl::strcontains(U##haystack##_sv, U##needle));      \
    check_macro(pl::strcontains(U##haystack, U##needle##_sv));      \
    check_macro(pl::strcontains(U##haystack##s, U##needle##s));     \
    check_macro(pl::strcontains(U##haystack##s, U##needle));        \
    check_macro(pl::strcontains(U##haystack, U##needle##s));        \
                                                                    \
    check_macro(pl::strcontains(L##haystack, L##needle));           \
    check_macro(pl::strcontains(L##haystack##_sv, L##needle##_sv)); \
    check_macro(pl::strcontains(L##haystack##_sv, L##needle));      \
    check_macro(pl::strcontains(L##haystack, L##needle##_sv));      \
    check_macro(pl::strcontains(L##haystack##s, L##needle##s));     \
    check_macro(pl::strcontains(L##haystack##s, L##needle));        \
    check_macro(pl::strcontains(L##haystack, L##needle##s))

#define CHECK_STRCONTAINS(haystack, needle) \
    CHECK_STRCONTAINS_IMPL(CHECK_UNARY, haystack, needle)

#define CHECK_STRNOTCONTAINS(haystack, needle) \
    CHECK_STRCONTAINS_IMPL(CHECK_UNARY_FALSE, haystack, needle)

TEST_CASE("strcontains should find substring")
{
    CHECK_STRCONTAINS("Hello World", "World");
    CHECK_STRCONTAINS("test", "");
    CHECK_STRCONTAINS("test", "t");
    CHECK_STRCONTAINS("test", "te");
    CHECK_STRCONTAINS("test", "es");
    CHECK_STRCONTAINS("test", "st");
    CHECK_STRCONTAINS("test", "test");
}

TEST_CASE("strcontains should find the empty string in the empty string")
{
    CHECK_STRCONTAINS("", "");
}

TEST_CASE("strcontains shouldn't find text in an empty string")
{
    CHECK_STRNOTCONTAINS("", "a");
    CHECK_STRNOTCONTAINS("", "test");
}

TEST_CASE("strcontains should find single character in single character string")
{
    CHECK_STRCONTAINS("a", "a");
}

TEST_CASE("strcontains should find all substrings")
{
    CHECK_STRCONTAINS("abc", "");
    CHECK_STRCONTAINS("abc", "a");
    CHECK_STRCONTAINS("abc", "ab");
    CHECK_STRCONTAINS("abc", "abc");
    CHECK_STRCONTAINS("abc", "b");
    CHECK_STRCONTAINS("abc", "bc");
    CHECK_STRCONTAINS("abc", "c");
}

TEST_CASE("strcontains shouldn't find reverse string")
{
    CHECK_STRNOTCONTAINS("test_string", "gnirts_tset");
}

TEST_CASE("strcontains should find the empty string in any string")
{
    CHECK_STRCONTAINS("", "");
    CHECK_STRCONTAINS("a", "");
    CHECK_STRCONTAINS("ab", "");
    CHECK_STRCONTAINS("abc", "");
    CHECK_STRCONTAINS("text", "");
}

TEST_CASE("strcontains should find equal string")
{
    CHECK_STRCONTAINS("This is a sample text.", "This is a sample text.");
}

TEST_CASE("strcontains should find string at the start")
{
    CHECK_STRCONTAINS("This is a lengthy text.", "This");
}

TEST_CASE("strcontains should find a string in the middle")
{
    CHECK_STRCONTAINS("This is a lengthy text.", "a lengthy ");
}

TEST_CASE("strcontains should find a string at the end")
{
    CHECK_STRCONTAINS("This is a lengthy text.", "text.");
}

TEST_CASE("strcontains should find bytes")
{
    CHECK_STRCONTAINS("\xDE\xAD\xC0\xDE", "\xC0\xDE");
}
