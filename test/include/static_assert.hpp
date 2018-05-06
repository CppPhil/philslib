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

#ifndef INCG_PL_TEST_STATIC_ASSERT_HPP
#define INCG_PL_TEST_STATIC_ASSERT_HPP
#include "../../include/pl/source_line.hpp" // PL_SOURCE_LINE

/*!
 * \def PL_TEST_STATIC_ASSERT(...)
 * \brief Test macro to be used in tests to check a condition at compile time.
 *        Will generate a compilation error including the file, line and
 *        expression where the condition passed in failed.
 *        The error message will also include the expression used for
 *        the PL_TEST_STATIC_ASSERT macro as well.
**/

#define PL_TEST_STATIC_ASSERT(...)                                          \
    static_assert(                                                          \
        (__VA_ARGS__),                                                      \
        "static_assert failed in file: " __FILE__ ", line: " PL_SOURCE_LINE \
        ", expression: " #__VA_ARGS__)
#endif // INCG_PL_TEST_STATIC_ASSERT_HPP
