/*!
 * \file front.hpp
 * \brief Exports the front function that returns the first (index 0)
 *        element of container or a C-style array.
**/
#ifndef INCG_PL_CONT_FRONT_HPP
#define INCG_PL_CONT_FRONT_HPP
#include "../annotations.hpp" // PL_IN
#include <cstddef> // std::size_t

namespace pl
{
namespace cont
{
/*!
 * \brief Gets the first (index 0) element of a container.
 * \param cont The container to get the first (index 0) element of.
 * \return The first (index 0) element of the container.
 * \warning Undefined behavior occurs if the container passed is empty.
**/
template <typename Cont>
constexpr auto front(PL_IN Cont &cont) -> decltype(auto)
{
    return cont.front();
}

/*!
 * \brief Gets the first (index 0) element of a C-Array.
 * \param arr The C-Array to get the first (index 0) element of.
 * \return The first (index 0) element of the C-Array.
**/
template <typename Type, std::size_t Size>
constexpr auto front(PL_IN Type (&arr)[Size]) noexcept -> decltype(auto)
{
    return arr[static_cast<std::size_t>(0U)];
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_FRONT_HPP
