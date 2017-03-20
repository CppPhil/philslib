/*!
 * \file except.hpp
 * \brief This header defines various utilities for working with exceptions.
**/
#ifndef INCG_PL_EXCEPT_HPP
#define INCG_PL_EXCEPT_HPP
#include "macros.hpp" // PL_SOURCE_LINE, PL_PRETTY_FUNCTION
#include <string> // std::string
#include <stdexcept> // std::runtime_error
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
 *
 * Includes the file, line and function from where the exception was thrown
 * in the message of the exception object of type exceptionType that can be
 * accessed via the .what() member function. The first parameter of this macro
 * must be an exception type, that type will be the type of the exception
 * thrown by the macro. The second parameter of the macro is the message
 * of the user to include in the exception object's message, std::string must
 * be constructible from message.
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
