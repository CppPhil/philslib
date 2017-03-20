/*!
 * \file except.hpp
 * \brief This header defines various utilities for working with exceptions.
**/
#ifndef INCG_PL_EXCEPT_HPP
#define INCG_PL_EXCEPT_HPP
#include "macros.hpp" // PL_SOURCE_LINE, PL_PRETTY_FUNCTION
#include <string> // std::string
#include <stdexcept> // std::runtime_error
#include <cassert> // NDEBUG
/*!
 * \def PL_DEFINE_EXCEPTION_TYPE(exceptionTypeIdentifier, baseClass)
 * \brief Defines an exception type. Its name will be exceptionTypeIdentifier
 *        and the base class will be baseClass. The exception type is defined
 *        in the current namespace. This macro makes defining new exception
 *        types a lot more convenient by generating a lot of boilerplate code.
**/

/*!
 * \def PL_THROW_WITH_SOURCE_INFO(exceptionType, message)
 * \brief Throws an exception of type exceptionType with the message message
 *        including information regarding where the exception was thrown.
 * \note Note that the line number may have been manipulated using #line.
 *
 * Includes the file, line and function from where the exception was thrown
 * in the message of the exception object of type exceptionType that can be
 * accessed via the .what() member function. The first parameter of this macro
 * must be an exception type, that type will be the type of the exception
 * thrown by the macro. The second parameter of the macro is the message
 * of the user to include in the exception object's message, std::string must
 * be constructible from message.
**/

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

#define PL_DEFINE_EXCEPTION_TYPE(exceptionTypeIdentifier, baseClass) \
    class exceptionTypeIdentifier \
        : public baseClass \
    { \
    public: \
        using this_type = exceptionTypeIdentifier; \
        using base_type = baseClass; \
        \
        explicit exceptionTypeIdentifier(const std::string &what_arg) \
            : base_type{ what_arg } \
        { \
        } \
        \
        explicit exceptionTypeIdentifier(const char *what_arg) \
            : base_type{ what_arg } \
        { \
        } \
        \
        virtual const char *what() const noexcept override \
        { \
            return base_type::what(); \
        } \
    }

#define PL_THROW_WITH_SOURCE_INFO(exceptionType, message) \
    throw exceptionType{ \
        "Message: " \
        + std::string{ message } \
        + "\nexception was thrown at:" \
          "\nfile: " __FILE__ \
          "\nline: " PL_SOURCE_LINE \
          "\nfunction: " \
        + std::string{ PL_PRETTY_FUNCTION } \
    }

#define PL_DETAIL_ASSERTION_IMPLEMENTATION(condition, exceptionType, violationTypeString) \
    PL_BEGIN_MACRO \
        if (!(condition)) { \
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

namespace pl
{
/* TODO: add documentation for the exception types defined below.
**/
class AssertionViolationException
    : public std::runtime_error
{
public:
    using this_type = AssertionViolationException;
    using base_type = std::runtime_error;

    explicit AssertionViolationException(const std::string &what_arg);

    explicit AssertionViolationException(const char *what_arg);

    virtual const char *what() const noexcept override;
};

class PreconditionViolationException
    : public AssertionViolationException
{
public:
    using this_type = PreconditionViolationException;
    using base_type = AssertionViolationException;

    explicit PreconditionViolationException(const std::string &what_arg);

    explicit PreconditionViolationException(const char *what_arg);

    virtual const char *what() const noexcept override;
};

class PostconditionViolationException
    : public AssertionViolationException
{
public:
    using this_type = PostconditionViolationException;
    using base_type = AssertionViolationException;

    explicit PostconditionViolationException(const std::string &what_arg);

    explicit PostconditionViolationException(const char *what_arg);

    virtual const char *what() const noexcept override;
};

/*!
 * \brief Function to handle uncaught exceptions.
 * \warning Only call this function in a catch block!
 * \note This function attempts to rethrow the exception that was just caught.
 * \example int main()
 *          try {
 *              app::throwException();
 *          } catch (...) {
 *              pl::handleExceptions();
 *          }
 *
 * This function can be used to handle uncaught exceptions that would escape
 * from the main function for instance.
 * This function shall be called in a try { } catch (...) { } block.
 * pl::handleException will rethrow the exception that was just caught and
 * handle it, by printing the information associated with that exception to
 * std::cerr.
**/
void handleExceptions();
} // namespace pl
#endif // INCG_PL_EXCEPT_HPP
