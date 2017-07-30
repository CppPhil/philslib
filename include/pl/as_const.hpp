/*!
 * \file as_const.hpp
 * \brief Exports a function to view an object as const.
**/
#ifndef INCG_PL_AS_CONST_HPP
#define INCG_PL_AS_CONST_HPP
#include "annotations.hpp" // PL_IN
#include <type_traits> // std::add_const_t

namespace pl
{
/*!
 * \brief Function to view something as const.
 * \param ty The object to be viewed as const.
 * \return A const & to ty.
**/
template <typename Ty>
constexpr std::add_const_t<Ty> &asConst(PL_IN Ty &ty) noexcept
{
    return ty;
}

/*!
 * \brief asConst may not be called with rvalues.
**/
template <typename Ty>
void asConst(PL_IN const Ty &&) = delete;
} // namespace pl
#endif // INCG_PL_AS_CONST_HPP
