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
 * \brief Defines various assertion macros including macros specifically designed
 *        for pre- and postconditions.
**/
#ifndef INCG_PL_ASSERT_HPP
#define INCG_PL_ASSERT_HPP
#include "begin_end_macro.hpp" // PL_BEGIN_MACRO, PL_END_MACRO
#include "except.hpp" // pl::AssertionViolationException, pl::PreconditionViolationException, pl::PostconditionViolationException
#include <ciso646> // not
#include <cassert> // NDEBUG
/*!
 * \def PL_DETAIL_ASSERTION_IMPLEMENTATION(condition, exceptionType, violationTypeString)
 * \brief Implementation macro not to be used directly.
 *
 * Implementation macro used in PL_CHECK_PRE, PL_CHECK_POST, PL_ASSERT, PL_DBG_CHECK_PRE,
 * PL_DBG_CHECK_POST and PL_DBG_ASSERT.
**/

/*!
 * \def PL_CHECK_PRE(precondition)
 * \brief Macro to check a precondition.
 *
 * Throws pl::PreconditionViolationException with an appropriate message if
 * precondition evaluates to false.
**/

/*!
 * \def PL_CHECK_POST(postcondition)
 * \brief Macro to check a postcondition.
 *
 * Throws pl::PostconditionViolationException with an appropriate message if
 * postcondition evaluates to false.
**/

/*!
 * \def PL_ASSERT(condition)
 * \brief Macro to check a condition.
 *
 * Throws pl::AssertionViolationException with an appropriate message if
 * postcondition evaluates to false.
**/

/*!
 * \def PL_DBG_CHECK_PRE(precondition)
 * \brief Macro to check a precondition if NDEBUG is not defined.
 * \note Will do nothing if NDEBUG is defined so that a release version doesn't
 *       suffer runtime overhead.
 * \note Can be used to check for runtime errors that result from bugs that
 *       have to be fixed in the development process and will not be in the
 *       release version.
 * \warning If the development environment used does not define NDEBUG in release mode
 *          you will have to define it yourself when compiling in release mode.
 *          It is recommended to define NDEBUG in the compiler's command line parameters
 *          in that case.
 *
 * Throws pl::PreconditionViolationException with an appropriate message if
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
 * \warning If the development environment used does not define NDEBUG in release mode
 *          you will have to define it yourself when compiling in release mode.
 *          It is recommended to define NDEBUG in the compiler's command line parameters
 *          in that case.
 *
 * Throws pl::PostconditionViolationException with an appropriate message if
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
 * \warning If the development environment used does not define NDEBUG in release mode
 *          you will have to define it yourself when compiling in release mode.
 *          It is recommended to define NDEBUG in the compiler's command line parameters
 *          in that case.
 *
 * Throws pl::AssertionViolationException with an appropriate message if
 * condition evaluates to false and NDEBUG is not defined.
 * If NDEBUG is defined does nothing.
**/

#define PL_DETAIL_ASSERTION_IMPLEMENTATION(condition, exceptionType, violationTypeString) \
    PL_BEGIN_MACRO \
        if (not (condition)) { \
            PL_THROW_WITH_SOURCE_INFO(exceptionType, \
                violationTypeString " VIOLATION:\n" \
                PL_STRINGIFY(condition) \
                "\nevaluated to false!" \
            ); \
        } \
    PL_END_MACRO

#define PL_CHECK_PRE(precondition) \
    PL_DETAIL_ASSERTION_IMPLEMENTATION(precondition, \
        ::pl::PreconditionViolationException, \
        "PRECONDITION" \
    )

#define PL_CHECK_POST(postcondition) \
    PL_DETAIL_ASSERTION_IMPLEMENTATION(postcondition, \
        ::pl::PostconditionViolationException, \
        "POSTCONDITION" \
    )

#define PL_ASSERT(condition) \
    PL_DETAIL_ASSERTION_IMPLEMENTATION(condition, \
        ::pl::AssertionViolationException, \
        "ASSERTION" \
    )

#ifdef NDEBUG
#   define PL_DBG_CHECK_PRE(precondition) PL_BEGIN_MACRO PL_END_MACRO /* do nothing */
#   define PL_DBG_CHECK_POST(postcondition) PL_BEGIN_MACRO PL_END_MACRO  /* do nothing */
#   define PL_DBG_ASSERT(condition) PL_BEGIN_MACRO PL_END_MACRO  /* do nothing */
#else
#   define PL_DBG_CHECK_PRE(precondition) PL_CHECK_PRE(precondition)
#   define PL_DBG_CHECK_POST(postcondition) PL_CHECK_POST(postcondition)
#   define PL_DBG_ASSERT(condition) PL_ASSERT(condition)
#endif
#endif // INCG_PL_ASSERT_HPP
