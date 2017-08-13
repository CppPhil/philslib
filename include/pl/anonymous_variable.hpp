/*!
 * \file anonymous_variable.hpp
 * \brief Exports the PL_ANONYMOUS_VARIABLE macro.
**/
#ifndef INCG_PL_ANONYMOUS_VARIABLE_HPP
#define INCG_PL_ANONYMOUS_VARIABLE_HPP
#include "glue.hpp" // PL_GLUE

/*!
 * \def PL_ANONYMOUS_VARIABLE(type, init)
 * \brief Declares an anonymous variable of type 'type'
 *        'init' is used to initialize the object of type 'type'.
**/

#ifndef __COUNTER__
#   warning "Your C++ implementation does not define the non-standard __COUNTER__, anonymous variables will not be available"
#endif // __COUNTER__

#define PL_ANONYMOUS_VARIABLE(type, init) \
    type PL_GLUE(_anonymous, PL_GLUE(type, __COUNTER__)) init;
#endif // INCG_PL_ANONYMOUS_VARIABLE_HPP
