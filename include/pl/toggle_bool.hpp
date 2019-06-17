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

/*!
 * \file toggle_bool.hpp
 * \brief Exports a function to toggle the value of a bool variable.
 **/
#ifndef INCG_PL_TOGGLE_BOOL_HPP
#define INCG_PL_TOGGLE_BOOL_HPP
#include "annotations.hpp" // PL_INOUT
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC, PL_COMPILER_VERSION, PL_COMPILER_VERSION_CHECK
#include <ciso646> // not

namespace pl {
/*!
 * \brief Toggles the boolean passed in.
 * \param b The boolean to be toggled.
 * \return The new value of the the boolean passed in.
 * \note Not a constexpr function on msvc15.
 *
 * If the boolean passed in is true it will be assigned false and the
 * value returned will be false.
 * If the boolean passed in is false it will be assigned true and the
 * value return will be true.
 **/
#if (PL_COMPILER != PL_COMPILER_MSVC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
constexpr
#else
inline
#endif
    bool
    toggle_bool(PL_INOUT bool& b) noexcept
{
    b = not b;
    return b;
}
} // namespace pl
#endif // INCG_PL_TOGGLE_BOOL_HPP
