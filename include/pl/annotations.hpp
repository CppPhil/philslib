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
 * \note Allows the pointer or reference parameter to refer to an unitialized
 *       object as the object referenced will only be written to.
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
 * \note The pointer is allowed to point to an uninitialized object as
 *       the pointed to object will only be written to and not be read from.
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
#elif PL_COMPILER == PL_COMPILER_MSVC
#   define PL_FALLTHROUGH /* nothing */
#   define PL_NODISCARD /* nothing */
#elif PL_COMPILER == PL_COMPILER_ICC
#   define PL_FALLTHROUGH /* nothing */
#   define PL_NODISCARD /* nothing */
#else
#   define PL_FALLTHROUGH /* nothing */
#   define PL_NODISCARD /* nothing */
#endif

#define PL_PARENT(parent) parent

#define PL_NO_PARENT nullptr

#define PL_IMPLICIT /* nothing */
#endif // INCG_PL_ANNOTATIONS_HPP
