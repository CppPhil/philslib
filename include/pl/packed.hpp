#ifndef INCG_PL_PACKED_HPP
#define INCG_PL_PACKED_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC

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

#if PL_COMPILER == PL_COMPILER_MSVC
#   define PL_PACKED_START __pragma(pack(push, 1))
#   define PL_PACKED_END __pragma(pack(pop))
#else
#   define PL_PACKED_START _Pragma("pack(push, 1)")
#   define PL_PACKED_END _Pragma("pack(pop)")
#endif
#endif // INCG_PL_PACKED_HPP
