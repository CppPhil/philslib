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
#endif // INCG_PL_EXCEPT_HPP
