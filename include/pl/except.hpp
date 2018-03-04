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
 * \file except.hpp
 * \brief This header defines various utilities for working with exceptions.
**/
#ifndef INCG_PL_EXCEPT_HPP
#define INCG_PL_EXCEPT_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC
#include "source_line.hpp" // PL_SOURCE_LINE
#include "current_function.hpp" // PL_CURRENT_FUNCTION
#include "begin_end_macro.hpp" // PL_BEGIN_MACRO, PL_END_MACRO
#include "stringify.hpp" // PL_STRINGIFY
#include <string> // std::string
#include <exception> // std::exception
#include <stdexcept> // std::runtime_error, std::logic_error
#include <system_error> // std::error_code
#include <future> // std::future_error
#include <memory> // std::bad_weak_ptr
#include <typeinfo> // std::bad_typeid
#include <iostream> // std::cerr

/*!
 * \def PL_DEFINE_EXCEPTION_TYPE(exceptionTypeIdentifier, baseClass)
 * \brief Defines an exception type. Its name will be exceptionTypeIdentifier
 *        and the base class will be baseClass. The exception type is defined
 *        in the current namespace. This macro makes defining new exception
 *        types a lot more convenient by generating a lot of boilerplate code.
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
    }

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
#define PL_THROW_WITH_SOURCE_INFO(exceptionType, message) \
    throw exceptionType{ \
        "Message: " \
        + std::string{ message } \
        + "\nexception was thrown at:" \
          "\nfile: " __FILE__ \
          "\nline: " PL_SOURCE_LINE \
          "\nfunction: " \
        + std::string{ PL_CURRENT_FUNCTION } \
    }

/*!
 * \def PL_THROW_IF_NULL(pointer)
 * \brief Throws pl::NullPointerException if the pointer passed in is null.
 * \note Uses PL_THROW_WITH_SOURCE_INFO internally.
 * \see PL_THROW_WITH_SOURCE_INFO
**/
#define PL_THROW_IF_NULL(pointer) \
    PL_BEGIN_MACRO \
    if ((pointer) == nullptr) { \
        PL_THROW_WITH_SOURCE_INFO(pl::NullPointerException, \
            PL_STRINGIFY(pointer) " was null!"); \
    } \
    PL_END_MACRO

/*!
 * \def PL_NOT_YET_IMPLEMENTED
 * \brief Throws pl::NotYetImplementedException. Can be used to 'implement'
 *        functions that are net yet implemented so that they throw when called.
 * \note Uses PL_THROW_WITH_SOURCE_INFO internally.
 * \see PL_THROW_WITH_SOURCE_INFO
**/
#define PL_NOT_YET_IMPLEMENTED() \
    PL_THROW_WITH_SOURCE_INFO(pl::NotYetImplementedException, \
        "function has not yet been implemented!")

namespace pl
{
/*!
 * \brief Exception thrown on assertion violation.
 * \note Not to be caught, this exception indicates a bug.
 * \see assert.hpp
**/
class AssertionViolationException
    : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/*!
 * \brief Exception thrown on precondition violation.
 * \note Not to be caught, this exception indicates a bug.
 * \see assert.hpp
**/
class PreconditionViolationException
    : public AssertionViolationException
{
public:
    using AssertionViolationException::AssertionViolationException;
};

/*!
 * \brief Exception thrown on postcondition violation.
 * \note Not to be caught, this exception indicates a bug.
 * \see assert.hpp
**/
class PostconditionViolationException
    : public AssertionViolationException
{
public:
    using AssertionViolationException::AssertionViolationException;
};

/*!
 * \brief Exception that you can throw if given an unexpected null pointer.
**/
class NullPointerException
    : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/*!
 * \brief Used by the PL_NOT_YET_IMPLEMENTED macro.
**/
class NotYetImplementedException
    : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/*!
 * \brief Exception that you can throw if an arithmetic error were to occur.
**/
class ArithmeticException
    : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/*!
 * \brief Exception that you can throw if given an illegal argument.
**/
class IllegalArgumentException
    : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/*!
 * \brief Exception that you can throw if an index is out of bounds.
**/
class IndexOutOfBoundsException
    : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/*!
 * \brief Exception that you can throw if a requested operation is not supported.
**/
class OperationNotSupportedException
    : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

/*!
 * \brief Exception that indicates an invalid size.
**/
class InvalidSizeException
    : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

#if PL_COMPILER == PL_COMPILER_MSVC
#   pragma warning(push)
#   pragma warning(disable:4505) // unreferenced local function has been removed
#endif // PL_COMPILER == PL_COMPILER_MSVC
/*!
 * \brief Function to handle uncaught exceptions.
 * \warning Only call this function in a catch block!
 * \note This function attempts to rethrow the exception that was just caught
 *       in order to catch it again.
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
 * std::cerr. May be used for debugging purposes.
**/
static void handleExceptions()
{
    static constexpr char functionName[] = "pl::handleExceptions";

    try {
        throw;
    } catch (const std::bad_array_new_length &e) {
        std::cerr << functionName
                  << " caught std::bad_array_new_length exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_alloc &e) {
        std::cerr << functionName
                  << " caught std::bad_alloc exception:\n"
                  << e.what() << '\n';
    } catch (const std::ios_base::failure &e) {
        std::cerr << functionName
                  << " caught std::bad_ios_base::failure exception:\n"
                  << e.what() << '\n';
    } catch (const std::system_error &e) {
        std::cerr << functionName
                  << " caught std::system_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::out_of_range &e) {
        std::cerr << functionName
                  << " caught std::out_of_range exception:\n"
                  << e.what() << '\n';
    } catch (const std::length_error &e) {
        std::cerr << functionName
                  << " caught std::length_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::invalid_argument &e) {
        std::cerr << functionName
                  << " caught std::invalid_argument exception:\n"
                  << e.what() << '\n';
    } catch (const std::future_error &e) {
        std::cerr << functionName
                  << " caught std::future_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::domain_error &e) {
        std::cerr << functionName
                  << " caught std::domain_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::logic_error &e) {
        std::cerr << functionName
                  << " caught std::logic_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::overflow_error &e) {
        std::cerr << functionName
                  << " caught std::overflow_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::underflow_error &e) {
        std::cerr << functionName
                  << " caught std::underflow_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::range_error &e) {
        std::cerr << functionName
                  << " caught std::range_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::runtime_error &e) {
        std::cerr << functionName
                  << " caught std::runtime_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_weak_ptr &e) {
        std::cerr << functionName
                  << " caught std::bad_weak_ptr exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_typeid &e) {
        std::cerr << functionName
                  << " caught std::bad_typeid exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_exception &e) {
        std::cerr << functionName
                  << " caught std::bad_exception exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_cast &e) {
        std::cerr << functionName
                  << " caught std::bad_cast exception:\n"
                  << e.what() << '\n';
    } catch (const std::exception &e) {
        std::cerr << functionName
                  << " caught std::exception exception:\n"
                  << e.what() << '\n';
    } catch (...) {
        std::cerr << functionName
                  << " caught unknown exception!\n";
    }
}
#if PL_COMPILER == PL_COMPILER_MSVC
#   pragma warning(pop)
#endif // PL_COMPILER == PL_COMPILER_MSVC
} // namespace pl
#endif // INCG_PL_EXCEPT_HPP
