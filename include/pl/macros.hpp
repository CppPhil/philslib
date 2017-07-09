/*!
 * \file macros.hpp
 * \brief Defines various useful macros.
**/
#ifndef INCG_PL_MACROS_HPP
#define INCG_PL_MACROS_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_GCC, PL_COMPILER_CLANG, PL_COMPILER_ICC, PL_COMPILER_MSVC, PL_COMPILER_UNKNOWN
#include <cstddef> // std::nullptr_t
#include <ciso646> // not
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
 * Can be used to suppress compiler warnings about unused variables.
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
 * \def PL_FOREVER
 * \brief Expands to for (;;). Macro to create a never ending loop.
 * \note Using for (;;) rather than while (true) avoids pedantic warnings
 *       regarding constant expressions being evaluated.
 * \warning Be careful not to create a never ending loop that has no
 *          observable behavior.
 * \see http://en.cppreference.com/w/cpp/language/memory_model#Forward_progress
**/

/*!
 * \def PL_NULL_TERMINATED
 * \brief Macro to annotate char * and char[] types as null terminated.
**/

/*!
 * \def PL_IMPLICIT
 * \brief Macro to annotate constructors callable with a single argument
 *        (converting constructors) and implicit conversion operators that
 *        lack the explicit keyword on purpose as implicit.
**/

/*!
 * \def PL_PACKED_START
 * \brief Place this macro before the beginning of a struct declaration in order
 *        to declare the struct as packed.
 * \warning Don't forget to place the PL_PACKED_END macro at the end of the struct
 *          declaration.
 * \see PL_PACKED_END
 * \example PL_PACKED_START
 *          struct PackedStruct
 *          {
 *              std::uint32_t a;
 *              std::uint16_t b;
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

/*!
 * \def PL_CURRENT_FUNCTION
 * \brief Expands to a C-String literal that represents the current function.
 * \note Uses the 'prettiest' function macro that the compiler being used provides.
 * \warning Depending on the compiler used, this macro will expand to a different
 *          C-String literal!
 * \warning The result of the macro expansion can not be string concatenated
 *          by the preprocessor with other C-String literals.
**/

/*!
 * \def PL_SOURCE_LINE
 * \brief The current line in the current source file.
 * \note Note that the line number may have been manipulated using #line.
 *
 * Macro that expands to a C-String literal of the current line in the current
 * source file. Equivalent to the stringification of the standard predefined
 * macro __LINE__
**/

/*!
 * \def PL_UNLESS(condition)
 * \brief Control flow statement that will execute its body unless the condition
 *        is true.
 * \note Behaves the same as if (not condition)
**/

/*!
 * \def PL_REPEAT
 * \brief Introduces a repeat until loop.
 * \warning Must be ended with PL_UNTIL
 * \note The repeat until loop behaves like do { } while (not condition)
**/

/*!
 * \def PL_UNTIL(condition)
 * \brief The until part of the repeat until loop. The loop will run until
 *        the condition is true, that is the loop will repeat its body as long
 *        as the condition is false.
 * \warning Must be introduced with PL_UNTIL
 * \note The repeat until loop behaves like do { } while (not condition)
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

#define PL_END_MACRO } while (PL_UNUSED(0), 0) /* avoid warnings */

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

#define PL_PARENT(parent) parent

#define PL_NO_PARENT nullptr

#define PL_FOREVER for (;;)

#define PL_NULL_TERMINATED /* nothing */

#define PL_IMPLICIT /* nothing */

#if PL_COMPILER == PL_COMPILER_MSVC
#   define PL_PACKED_START __pragma(pack(push, 1))
#   define PL_PACKED_END __pragma(pack(pop))
#else
#   define PL_PACKED_START _Pragma("pack(push, 1)")
#   define PL_PACKED_END _Pragma("pack(pop)")
#endif

#if PL_COMPILER == PL_COMPILER_MSVC
#   define PL_CURRENT_FUNCTION __FUNCSIG__
#elif PL_COMPILER == PL_COMPILER_GCC || PL_COMPILER == PL_COMPILER_CLANG
#   define PL_CURRENT_FUNCTION __PRETTY_FUNCTION__
#else
#   define PL_CURRENT_FUNCTION __func__ /* use __func__ from C99 as fallback */
#endif

#define PL_SOURCE_LINE PL_STRINGIFY(__LINE__)

#define PL_UNLESS(condition) if (not (condition))

#define PL_REPEAT do

#define PL_UNTIL(condition) while (not (condition))

#endif // INCG_PL_MACROS_HPP
