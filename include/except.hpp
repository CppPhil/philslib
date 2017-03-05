/*! \file except.hpp
 *  \brief This header defines various utilities for working with exceptions.
**/

#ifndef INCG_PL_EXCEPT_HPP
#define INCG_PL_EXCEPT_HPP
#include <string> // std::string

/*!
 * \def PL_DEFINE_EXCEPTION_TYPE(exceptionTypeIdentifier, baseClass)
 * \brief Defines an exception type. Its name will be exceptionTypeIdentifier
 *        and the base class will be baseClass. The exception type is defined
 *        in the current namespace. This macro make defining new exception
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
        virtual const char *what() const noexcept override \
        { \
            return base_type::what(); \
        } \
    }

namespace pl
{
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
