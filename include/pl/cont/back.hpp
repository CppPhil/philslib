/*!
 * \file back.hpp
 * \brief Exports the back function that returns the last element
 *        of a container or C-style array.
**/
#ifndef INCG_PL_CONT_BACK_HPP
#define INCG_PL_CONT_BACK_HPP
#include "../annotations.hpp" // PL_IN
#include <cstddef> // std::size_t

namespace pl
{
namespace cont
{
/*!
 * \brief Gets the last element of a container.
 * \param cont The container to get the last element of.
 * \return The last element of the container.
 * \warning Undefined behavior occurs if the container passed in is empty.
**/
template <typename Cont>
constexpr auto back(PL_IN Cont &cont) -> decltype(auto)
{
    return cont.back();
}

/*!
 * \brief Gets the last element of a C-Array.
 * \param arr The C-Array to get the last element of.
 * \return The last element of the C-Array.
**/
template <typename Type, std::size_t Size>
constexpr auto back(PL_IN Type (&arr)[Size]) noexcept -> decltype(auto)
{
    return arr[Size - static_cast<std::size_t>(1U)];
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_BACK_HPP
