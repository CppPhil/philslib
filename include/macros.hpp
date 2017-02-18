/*! \file macros.hpp
 *  \brief Defines various useful macros.
**/

#ifndef INCG_PL_MACROS_HPP
#define INCG_PL_MACROS_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_GCC, PL_COMPILER_CLANG, PL_COMPILER_ICC, PL_COMPILER_MSVC, PL_COMPILER_UNKNOWN

/*!
 * \def PL_ALWAYS_INLINE
 * \brief Declares a function as always to be inlined (if possible).
 * \warning Overrides the compiler's cost-benefit-analysis in regards to
 *          inlining. Only use when certain. May not work if compiler is
 *          unknown.
**/

/*!
 * \def PL_NEVER_INLINE
 * \brief Declares a function as never to be inlined.
 * \warning May not work if compiler is unknown.
**/

/*!
 * \def PL_RESTRICT
 * \brief Declares a pointer as a restrict pointer.
 * \warning If an independent pointer accesses the object pointed
 *          to by the pointer declared with PL_RESTRICT
 *          undefined behavior occurs.
 *
 * For the lifetime of the pointer declared with PL_RESTRICT
 * only the pointer itself and values directly derived
 * from the pointer (such as pointer + 1) may be used to access the
 * pointed to object. Using this macro when appropriate may aid
 * compiler optimizations as the effects of pointer aliasing are limited.
**/

/*!
 * \def PL_UNUSED(param)
 * \brief marks something as unused.
 *
 * Can be used to suppress compiler warning about unused variables.
**/

/*!
 * \def PL_BEGIN_MACRO
 * \brief To be used to begin definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see PL_END_MACRO
**/

/*!
 * \def PL_END_MACRO
 * \brief To be used to end definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see PL_BEGIN_MACRO
**/

/*!
 * \def PL_DETAIL_STRINGIFY(tokens)
 * \brief Implementation macro for PL_STRINGIFY
 * \warning Do not use.
 * \see PL_STRINGIFY
**/

/*!
 * \def PL_STRINGIFY(tokens)
 * \brief Turns a contiguous sequence of tokens passed in into a
 *        C-String literal.
 * \example PL_STRINGIFY(helloWorld) results in:
 *          "helloWorld"
**/

/*!
 * \def PL_DETAIL_GLUE(a, b)
 * \brief Implementation macro for PL_GLUE
 * \warning Do not use.
 * \see PL_GLUE
**/

/*!
 * \def PL_GLUE(a, b)
 * \brief Token pastes two contiguous sequences of tokens together as one.
 * \example PL_GLUE(hello, world) results in:
 *          helloworld
**/

/*!
 * \def PL_IN
 * \brief Annotates a pointer or reference parameter as an input parameter.
**/

/*!
 * \def PL_OUT
 * \brief Annotates a pointer or reference parameter as an output parameter.
**/

/*!
 * \def PL_INOUT
 * \brief Annotates a pointer or reference paramater as an input-output
 *        parameter.
**/

/*!
 * \def PL_IN_OPT
 * \brief Annotates a pointer parameter as an optional input parameter.
 * \note Pass nullptr to not use the input parameter.
**/

/*!
 * \def PL_OUT_OPT
 * \brief Annotates a pointer parameter as an optional output parameter.
 * \note Pass nullptr to not use the output parameter.
**/

/*!
 * \def PL_INOUT_OPT
 * \brief Annotates a pointer parameter as an optional input-output parameter.
 * \note Pass nullptr to not use the input-output parameter.
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

#if PL_COMPILER == PL_COMPILER_GCC
#   define PL_ALWAYS_INLINE __attribute__((always_inline)) inline
#   define PL_NEVER_INLINE __attribute__((noinline))
#   define PL_RESTRICT __restrict__
#elif PL_COMPILER == PL_COMPILER_CLANG
#   define PL_ALWAYS_INLINE __attribute__((always_inline))
#   define PL_NEVER_INLINE __attribute__((noinline))
#   define PL_RESTRICT __restrict__
#elif PL_COMPILER == PL_COMPILER_ICC
#   define PL_ALWAYS_INLINE __attribute__((always_inline))
#   define PL_NEVER_INLINE __attribute__((noinline))
#   define PL_RESTRICT restrict
#elif PL_COMPILER == PL_COMPILER_MSVC
#   define PL_ALWAYS_INLINE __forceinline
#   define PL_NEVER_INLINE __declspec(noinline)
#   define PL_RESTRICT __restrict
#elif PL_COMPILER == PL_COMPILER_UNKNOWN
#   define PL_ALWAYS_INLINE inline
#   define PL_NEVER_INLINE /* nothing */
#   define PL_RESTRICT /* nothing */
#endif

#define PL_UNUSED(param) static_cast<void>((param))

#define PL_BEGIN_MACRO do {

#define PL_END_MACRO } while (PL_UNUSED(0), 0)

#define PL_DETAIL_STRINGIFY(tokens) #tokens

#define PL_STRINGIFY(tokens) PL_DETAIL_STRINGIFY(tokens)

#define PL_DETAIL_GLUE(a, b) a##b

#define PL_GLUE(a, b) PL_DETAIL_GLUE(a, b)

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

#endif // INCG_PL_MACROS_HPP
