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
 * \file assert.hpp
 * \brief Defines various assertion macros including macros specifically
 *        designed for pre- and postconditions.
 **/
#ifndef INCG_PL_ASSERT_HPP
#define INCG_PL_ASSERT_HPP
#include "begin_end_macro.hpp" // PL_BEGIN_MACRO, PL_END_MACRO
#include "except.hpp" // pl::assertion_violation_exception, pl::precondition_violation_exception, pl::postcondition_violation_exception
#include <cassert>    // NDEBUG
#include <ciso646>    // not
#include <string>     // std::string

/*!
 * \def PL_DBG_CHECK_PRE(precondition)
 * \brief Macro to check a precondition if NDEBUG is not defined.
 * \note Will do nothing if NDEBUG is defined so that a release version doesn't
 *       suffer runtime overhead.
 * \note Can be used to check for runtime errors that result from bugs that
 *       have to be fixed in the development process and will not be in the
 *       release version.
 * \warning If the development environment used does not define NDEBUG in
 *          release mode you will have to define it yourself when compiling
 *          in release mode. It is recommended to define NDEBUG in the
 *          compiler's command line parameters in that case.
 *
 * Throws pl::precondition_violation_exception with an appropriate message if
 * precondition evaluates to false and NDEBUG is not defined.
 * If NDEBUG is defined does nothing.
 **/

/*!
 * \def PL_DBG_CHECK_POST(postcondition)
 * \brief Macro to check a postcondition if NDEBUG is not defined.
 * \note Will do nothing if NDEBUG is defined so that a release version doesn't
 *       suffer runtime overhead.
 * \note Can be used to check for runtime errors that result from bugs that
 *       have to be fixed in the development process and will not be in the
 *       release version.
 * \warning If the development environment used does not define NDEBUG in
 *          release mode you will have to define it yourself when compiling
 *          in release mode. It is recommended to define NDEBUG in the
 *          compiler's command line parameters in that case.
 *
 * Throws pl::postcondition_violation_exception with an appropriate message if
 * postcondition evaluates to false and NDEBUG is not defined.
 * If NDEBUG is defined does nothing.
 **/

/*!
 * \def PL_DBG_ASSERT(condition)
 * \brief Macro to check a condition if NDEBUG is not defined.
 * \note Will do nothing if NDEBUG is defined so that a release version doesn't
 *       suffer runtime overhead.
 * \note Can be used to check for runtime errors that result from bugs that
 *       have to be fixed in the development process and will not be in the
 *       release version.
 * \warning If the development environment used does not define NDEBUG in
 *          release mode you will have to define it yourself when compiling
 *          in release mode. It is recommended to define NDEBUG in the
 *          compiler's command line parameters in that case.
 *
 * Throws pl::assertion_violation_exception with an appropriate message if
 * condition evaluates to false and NDEBUG is not defined.
 * If NDEBUG is defined does nothing.
 **/

/*!
 * \def PL_DETAIL_ASSERTION_IMPLEMENTATION
 *      (condition, exception_type, violation_type_string)
 * \brief Implementation macro not to be used directly.
 *
 * Implementation macro used in PL_CHECK_PRE, PL_CHECK_POST, PL_ASSERT,
 * PL_DBG_CHECK_PRE, PL_DBG_CHECK_POST and PL_DBG_ASSERT.
 **/
#define PL_DETAIL_ASSERTION_IMPLEMENTATION(                                   \
    condition, exception_type, violation_type_string)                         \
    PL_BEGIN_MACRO                                                            \
    if (not(condition)) {                                                     \
        PL_THROW_WITH_SOURCE_INFO(                                            \
            exception_type,                                                   \
            violation_type_string                                             \
            " VIOLATION:\n" PL_STRINGIFY(condition) "\nevaluated to false!"); \
    }                                                                         \
    PL_END_MACRO

/*!
 * \def PL_DETAIL_ASSERTION_IMPLEMENTATION_MSG
 *      (condition, exception_type, violation_type_string, message)
 * \brief Implementation macro not to be used directly.
 *
 * Implementation macro used in PL_ASSERT_MSG and PL_DBG_ASSERT_MSG.
 **/
#define PL_DETAIL_ASSERTION_IMPLEMENTATION_MSG(                          \
    condition, exception_type, violation_type_string, message)           \
    PL_BEGIN_MACRO                                                       \
    if (not(condition)) {                                                \
        PL_THROW_WITH_SOURCE_INFO(                                       \
            exception_type,                                              \
            violation_type_string                                        \
                " VIOLATION:\n"                                          \
                "assertion message: "                                    \
                + std::string{message}                                   \
                + "\n" PL_STRINGIFY(condition) "\nevaluated to false!"); \
    }                                                                    \
    PL_END_MACRO

/*!
 * \def PL_CHECK_PRE(precondition)
 * \brief Macro to check a precondition.
 *
 * Throws pl::precondition_violation_exception with an appropriate message if
 * precondition evaluates to false.
 **/
#define PL_CHECK_PRE(precondition)      \
    PL_DETAIL_ASSERTION_IMPLEMENTATION( \
        precondition, ::pl::precondition_violation_exception, "PRECONDITION")

/*!
 * \def PL_CHECK_POST(postcondition)
 * \brief Macro to check a postcondition.
 *
 * Throws pl::postcondition_violation_exception with an appropriate message if
 * postcondition evaluates to false.
 **/
#define PL_CHECK_POST(postcondition)             \
    PL_DETAIL_ASSERTION_IMPLEMENTATION(          \
        postcondition,                           \
        ::pl::postcondition_violation_exception, \
        "POSTCONDITION")

/*!
 * \def PL_ASSERT(condition)
 * \brief Macro to check a condition.
 *
 * Throws pl::assertion_violation_exception with an appropriate message if
 * postcondition evaluates to false.
 **/
#define PL_ASSERT(condition)            \
    PL_DETAIL_ASSERTION_IMPLEMENTATION( \
        condition, ::pl::assertion_violation_exception, "ASSERTION")

/*!
 * \def PL_ASSERT_MSG(condition, message)
 * \brief Macro to check a condition and display a custom message in case
 *        that the condition evaluated to false.
 *
 * Throws pl::assertion_violation_exception with an appropriate message if
 * condition evaluates to false.
 **/
#define PL_ASSERT_MSG(condition, message)   \
    PL_DETAIL_ASSERTION_IMPLEMENTATION_MSG( \
        condition, ::pl::assertion_violation_exception, "ASSERTION", message)

#ifdef NDEBUG
#define PL_DBG_CHECK_PRE(precondition) \
    PL_BEGIN_MACRO PL_END_MACRO /* do nothing */

#define PL_DBG_CHECK_POST(postcondition) \
    PL_BEGIN_MACRO PL_END_MACRO /* do nothing */

#define PL_DBG_ASSERT(condition) PL_BEGIN_MACRO PL_END_MACRO /* do nothing */

#define PL_DBG_ASSERT_MSG(condition, message) \
    PL_BEGIN_MACRO PL_END_MACRO /* do nothing */
#else
#define PL_DBG_CHECK_PRE(precondition) PL_CHECK_PRE(precondition)

#define PL_DBG_CHECK_POST(postcondition) PL_CHECK_POST(postcondition)

#define PL_DBG_ASSERT(condition) PL_ASSERT(condition)

#define PL_DBG_ASSERT_MSG(condition, message) PL_ASSERT_MSG(condition, message)
#endif
#endif // INCG_PL_ASSERT_HPP
