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
 * \file packed.hpp
 * \brief Exports macros in order to be able to define packed
 *        structure types.
 **/
#ifndef INCG_PL_PACKED_HPP
#define INCG_PL_PACKED_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC

/*!
 * \def PL_PACKED_START
 * \brief Place this macro before the beginning of a struct declaration in order
 *        to declare the struct as packed.
 * \warning Don't forget to place the PL_PACKED_END macro at the end of the
 *          struct declaration.
 * \see PL_PACKED_END
 * \example PL_PACKED_START
 *          struct PackedStruct
 *          {
 *              std::uint16_t a;
 *              std::uint32_t b;
 *          };
 *          PL_PACKED_END
 *
 * A packed struct will contain no padding.
 * This can be used to treat packed structs as raw memory.
 **/

/*!
 * \def PL_PACKED_END
 * \brief The macro that ends a packed struct declaration introduced by
 *        PL_PACKED_START
 * \see PL_PACKED_START
 **/

#if PL_COMPILER == PL_COMPILER_MSVC
#define PL_PACKED_START __pragma(pack(push, 1))
#define PL_PACKED_END __pragma(pack(pop))
#else
#define PL_PACKED_START _Pragma("pack(push, 1)")
#define PL_PACKED_END _Pragma("pack(pop)")
#endif
#endif // INCG_PL_PACKED_HPP
