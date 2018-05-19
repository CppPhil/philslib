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
 * \file annotations.hpp
 * \brief Exports various macros to annotate the source code.
**/
#ifndef INCG_PL_ANNOTATIONS_HPP
#define INCG_PL_ANNOTATIONS_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_GCC, PL_COMPILER_CLANG, PL_COMPILER_ICC, PL_COMPILER_MSVC, PL_COMPILER_UNKNOWN
#include <cstddef>      // std::nullptr_t

/*!
 * \def PL_FALLTHROUGH
 * \brief Annotation to mark a case label's end as fallthrough.
 * \note Uses the C++17 attribute if available
**/

/*!
 * \def PL_NODISCARD
 * \brief Annotation to mark a function's return as not to be discarded.
 * \note Uses the C++17 attribute if available
**/

/*!
 * \def PL_PRINTF_FUNCTION(format_str_pos, var_args_pos)
 * \brief Annotates a function as a printf-style function.
 * \note This allows GCC and clang to issue warnings if the arguments
 *       and the format string do not match.
 *
 * Annotates a function as a printf-style function. To be placed
 * after the parameter list in a function declaration.
 * format_str_pos is the parameter (starting at 1) which will hold the
 * format string, var_args_pos is the parameter which will be the C-style
 * varargs. If implementing a vprintf-style function taking a std::va_list
 * argument use 0 as the var_args_pos.
 * Note that if used on non-static member functions the this pointer
 * will be considered to be the first argument!
**/

/*!
 * \def PL_IN
 * \brief Annotates a pointer or reference parameter as an input parameter.
 *
 * Indicates that the referenced object will only be read from.
**/
#define PL_IN /* nothing */

/*!
* \def PL_OUT
* \brief Annotates a pointer or reference parameter as an output parameter.
*
* Indicates that the referenced object will only be written to,
* but not be read from.
**/
#define PL_OUT /* nothing */

/*!
 * \def PL_INOUT
 * \brief Annotates a pointer or reference parameter as an input-output
 *        parameter.
 *
 * Indicates that the referenced object will be both read from and
 * be written to.
**/
#define PL_INOUT /* nothing */

/*!
 * \def PL_IN_OPT
 * \brief Annotates a pointer parameter as an optional input parameter.
 * \note Pass nullptr to not use the input parameter.
 *
 * Indicates that if the pointer is not a null pointer the pointed to object
 * will only be read from.
**/
#define PL_IN_OPT /* nothing */

/*!
 * \def PL_OUT_OPT
 * \brief Annotates a pointer parameter as an optional output parameter.
 * \note Pass nullptr to not use the output parameter.
 *
 * Indicates that if the pointer is not a null pointer the pointed to object
 * will only be written to, but never be read from.
**/
#define PL_OUT_OPT /* nothing */

/*!
 * \def PL_INOUT_OPT
 * \brief Annotates a pointer parameter as an optional input-output parameter.
 * \note Pass nullptr to not use the input-output parameter.
 *
 * Indicates that if the pointer is not a null pointer the pointed to object
 * will be both read from and written to.
**/
#define PL_INOUT_OPT /* nothing */

#if PL_COMPILER == PL_COMPILER_GCC
#if (__GNUC__ >= 7) && !defined(PL_NO_CPP17)
#define PL_FALLTHROUGH [[fallthrough]];
#define PL_NODISCARD [[nodiscard]]
#else
#define PL_FALLTHROUGH /* nothing */
#define PL_NODISCARD   /* nothing */
#endif
#define PL_PRINTF_FUNCTION(format_str_pos, var_args_pos) \
    __attribute__((format(printf, format_str_pos, var_args_pos)))
#elif PL_COMPILER == PL_COMPILER_CLANG
#if PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(3, 5, 0)
#define PL_FALLTHROUGH [[clang::fallthrough]];
#else
#define PL_FALLTHROUGH /* nothing */
#endif
#if (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(3, 9, 0)) \
    && !defined(PL_NO_CPP17)
#define PL_NODISCARD [[nodiscard]]
#else
#define PL_NODISCARD /* nothing */
#endif
#define PL_PRINTF_FUNCTION(format_str_pos, var_args_pos) \
    __attribute__((format(printf, format_str_pos, var_args_pos)))
#elif PL_COMPILER == PL_COMPILER_MSVC
#if (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0)) \
    && !defined(PL_NO_CPP17)
#define PL_FALLTHROUGH [[fallthrough]];
#define PL_NODISCARD [[nodiscard]]
#else
#define PL_FALLTHROUGH /* nothing */
#define PL_NODISCARD   /* nothing */
#endif
#define PL_PRINTF_FUNCTION(format_str_pos, var_args_pos) /* nothing */
#elif PL_COMPILER == PL_COMPILER_ICC
#define PL_FALLTHROUGH                                   /* nothing */
#define PL_NODISCARD                                     /* nothing */
#define PL_PRINTF_FUNCTION(format_str_pos, var_args_pos) /* nothing */
#else
#define PL_FALLTHROUGH                                   /* nothing */
#define PL_NODISCARD                                     /* nothing */
#define PL_PRINTF_FUNCTION(format_str_pos, var_args_pos) /* nothing */
#endif

/*!
 * \def PL_PARENT(parent)
 * \brief Macro that can be used to mark something as a parent.
 *        Can be used when using Qt Framework's parent system for instance.
**/
#define PL_PARENT(parent) parent

/*!
 * \def PL_NO_PARENT
 * \brief Macro that expands to nullptr. Can be used when using Qt Framework's
 *        parent system for instance. Can be used to create a QObject type with
 *        no parent.
**/
#define PL_NO_PARENT nullptr

/*!
 * \def PL_IMPLICIT
 * \brief Macro to annotate constructors callable with a single argument
 *        (converting constructors) and implicit conversion operators that
 *        lack the explicit keyword on purpose as implicit.
**/
#define PL_IMPLICIT /* nothing */

/*!
 * \def PL_NULL_TERMINATED(type)
 * \brief Macro to annotate a cv char * or cv char[] type as null terminated.
**/
#define PL_NULL_TERMINATED(type) type

/*!
 * \def PL_FMT_STR(type)
 * \brief Macro to annotate a cv char * or cv char[] type as a null terminated
 *        printf style format string.
**/
#define PL_FMT_STR(type) type
#endif // INCG_PL_ANNOTATIONS_HPP
