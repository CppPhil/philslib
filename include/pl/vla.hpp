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
 * \file vla.hpp
 * \brief Exports the PL_VLA macro.
**/
#ifndef INCG_PL_VLA_HPP
#define INCG_PL_VLA_HPP
#include "alloca.hpp"           // PL_ALLOCA
#include "raw_memory_array.hpp" // pl::RawMemoryArray

/*!
 * \def PL_VLA(type, identifier, size, initialValue)
 * \brief Creates a VLA. 'type' is the type of the elements that the VLA
 *        will store. 'identifier' is the identifier of the VLA.
 *        'size' is the amount of objects of type 'type' that the VLA will
 *        store.
 *        Pass an object with which to initialize the objects in the
 *        VLA by copy construction into the macro varargs.
 * \warning Internally uses PL_ALLOCA. Beware of stack overflow. See the
 *          documentation of PL_ALLOCA.
 * \see PL_ALLOCA
 * \note If the type contains a comma such as
 *       std::unordered_map<int, std::string>
 *       you have to use a type alias for that type, rather than using the type
 *       directly so that the comma effectively disappears.
**/

#define PL_VLA(type, identifier, size, ...) \
    ::pl::RawMemoryArray<type> identifier(  \
        PL_ALLOCA(sizeof(type) * size), sizeof(type) * size, __VA_ARGS__)
#endif // INCG_PL_VLA_HPP
