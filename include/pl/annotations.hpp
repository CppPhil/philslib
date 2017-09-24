/*!
 * \file annotations.hpp
 * \brief Exports various macros to annotate the source code.
**/
#ifndef INCG_PL_ANNOTATIONS_HPP
#define INCG_PL_ANNOTATIONS_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_GCC, PL_COMPILER_CLANG, PL_COMPILER_ICC, PL_COMPILER_MSVC, PL_COMPILER_UNKNOWN
#include <cstddef> // std::nullptr_t

/*!
 * \def PL_IN
 * \brief Annotates a pointer or reference parameter as an input parameter.
 *
 * Indicates that the referenced object will only be read from.
**/

/*!
 * \def PL_OUT
 * \brief Annotates a pointer or reference parameter as an output parameter.
 *
 * Indicates that the referenced object will only be written to,
 * but not be read from.
**/

/*!
 * \def PL_INOUT
 * \brief Annotates a pointer or reference paramater as an input-output
 *        parameter.
 *
 * Indicates that the referenced object will be both read from and
 * be written to.
**/

/*!
 * \def PL_IN_OPT
 * \brief Annotates a pointer parameter as an optional input parameter.
 * \note Pass nullptr to not use the input parameter.
 *
 * Indicates that if the pointer is not a null pointer the pointed to object
 * will only be read from.
**/

/*!
 * \def PL_OUT_OPT
 * \brief Annotates a pointer parameter as an optional output parameter.
 * \note Pass nullptr to not use the output parameter.
 *
 * Indicates that if the pointer is not a null pointer the pointed to object
 * will only be written to, but never be read from.
**/

/*!
 * \def PL_INOUT_OPT
 * \brief Annotates a pointer parameter as an optional input-output parameter.
 * \note Pass nullptr to not use the input-output parameter.
 *
 * Indicates that if the pointer is not a null pointer the pointed to object
 * will be both read from and written to.
**/

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
 * \def PL_PRINTF_FUNCTION(formatStrPos, varArgsPos)
 * \brief Annotates a function as a printf-style function.
 * \note This allows GCC and clang to issue warnings if the arguments
 *       and the format string do not match.
 *
 * Annotates a function as a printf-style function. To be placed
 * after the parameter list in a function declaration.
 * formatStrPos is the parameter (starting at 1) which will hold the
 * format string, varArgsPos is the parameter which will be the C-style
 * varargs. If implementing a vprintf-style function taking a std::va_list
 * argument use 0 as the varArgsPos.
 * Note that if used on non-static member functions the this pointer
 * will be considered to be the first argument!
**/

/*!
 * \def PL_PARENT(parent)
 * \brief Macro that can be used to mark something as a parent.
 *        Can be used when using Qt Framework's parent system for instance.
**/

/*!
 * \def PL_NO_PARENT
 * \brief Macro that expands to nullptr. Can be used when using Qt Framework's
 *        parent system for instance. Can be used to create a QObject type with
 *        no parent.
**/

/*!
 * \def PL_IMPLICIT
 * \brief Macro to annotate constructors callable with a single argument
 *        (converting constructors) and implicit conversion operators that
 *        lack the explicit keyword on purpose as implicit.
**/

/*!
 * \def PL_NULL_TERMINATED(type)
 * \brief Macro to annotate a cv char * or cv char[] type as null terminated.
**/

/*!
 * \def PL_FMT_STR(type)
 * \brief Macro to annotate a cv char * or cv char[] type as a null terminated
 *        printf style format string.
**/

#define PL_IN /* nothing */
#define PL_OUT /* nothing */
#define PL_INOUT /* nothing */
#define PL_IN_OPT /* nothing */
#define PL_OUT_OPT /* nothing */
#define PL_INOUT_OPT /* nothing */

#if PL_COMPILER == PL_COMPILER_GCC
#   if __GNUC__ >= 7
#       define PL_FALLTHROUGH [[fallthrough]];
#       define PL_NODISCARD [[nodiscard]]
#   else
#       define PL_FALLTHROUGH /* nothing */
#       define PL_NODISCARD /* nothing */
#   endif
#   define PL_PRINTF_FUNCTION(formatStrPos, varArgsPos) __attribute__((format (printf, formatStrPos, varArgsPos)))
#elif PL_COMPILER == PL_COMPILER_CLANG
#   if __has_cpp_attribute(fallthrough)
#       define PL_FALLTHROUGH [[fallthrough]];
#   else
#       define PL_FALLTHROUGH /* nothing */
#   endif
#   if __has_cpp_attribute(nodiscard)
#       define PL_NODISCARD [[nodiscard]]
#   else
#       define PL_NODISCARD /* nothing */
#   endif
#   define PL_PRINTF_FUNCTION(formatStrPos, varArgsPos) __attribute__((format (printf, formatStrPos, varArgsPos)))
#elif PL_COMPILER == PL_COMPILER_MSVC
#   define PL_FALLTHROUGH /* nothing */
#   define PL_NODISCARD /* nothing */
#   define PL_PRINTF_FUNCTION(formatStrPos, varArgsPos) /* nothing */
#elif PL_COMPILER == PL_COMPILER_ICC
#   define PL_FALLTHROUGH /* nothing */
#   define PL_NODISCARD /* nothing */
#   define PL_PRINTF_FUNCTION(formatStrPos, varArgsPos) /* nothing */
#else
#   define PL_FALLTHROUGH /* nothing */
#   define PL_NODISCARD /* nothing */
#   define PL_PRINTF_FUNCTION(formatStrPos, varArgsPos) /* nothing */
#endif

#define PL_PARENT(parent) parent

#define PL_NO_PARENT nullptr

#define PL_IMPLICIT /* nothing */

#define PL_NULL_TERMINATED(type) type

#define PL_FMT_STR(type) type
#endif // INCG_PL_ANNOTATIONS_HPP
