/*!
 * \file vla.hpp
 * \brief Exports the PL_VLA macro.
**/
#ifndef INCG_PL_VLA_HPP
#define INCG_PL_VLA_HPP
#include "glue.hpp" // PL_GLUE
#include "alloca.hpp" // PL_ALLOCA
#include "raw_memory_array.hpp" // pl::RawMemoryArray
#include <initializer_list> // std::initializer_list
#include <utility> // std::move

/*!
 * \def PL_VLA(type, identifier, ...)
 * \brief Creates a VLA. 'type' is the type of the elements that the VLA
 *        will store. 'identifier' is the identifier of the VLA.
 *        Supply the values to initialize the VLA in the macro varargs.
 * \example PL_VLA(std::vector<int>, myVla, { 1, 2, 3 }, { 4, 5, 6 });
 * \warning Internally uses PL_ALLOCA. Beware of stack overflow. See the
 *          documentation of PL_ALLOCA.
 * \see PL_ALLOCA
 * \note If the type contains a comma such as std::unordered_map<int, std::string>
 *       you have to use a type alias for that type, rather than using the type
 *       directly so that the comma effectively disappears.
**/

#define PL_VLA(type, identifier, ...) \
    std::initializer_list<type> PL_GLUE(_detailInitList, identifier) = { __VA_ARGS__ }; \
    ::pl::RawMemoryArray<decltype(PL_GLUE(_detailInitList, identifier))::value_type> identifier( \
        PL_ALLOCA(sizeof(decltype(PL_GLUE(_detailInitList, identifier))::value_type) \
                  * PL_GLUE(_detailInitList, identifier).size()), \
        sizeof(decltype(PL_GLUE(_detailInitList, identifier))::value_type) \
        * PL_GLUE(_detailInitList, identifier).size(),\
        std::move(PL_GLUE(_detailInitList, identifier)))
#endif // INCG_PL_VLA_HPP
