/*!
 * \file data.hpp
 * \brief Exports the data function that effectively returns a pointer to
 *        the first (index 0) element of container or C-style array.
 *        In case of a container it simply calls the .data() member function.
**/
#ifndef INCG_PL_CONT_DATA_HPP
#define INCG_PL_CONT_DATA_HPP
#include "../annotations.hpp" // PL_IN
#include <cstddef> // std::size_t
#include <memory> // std::addressof

namespace pl
{
namespace cont
{
/*!
 * \brief Calls .data() on the container passed in.
 * \param cont The container to call .data() on.
 * \return The result of calling .data() on cont.
 * \warning Do not dereference the pointer returned by this function if
 *          the container passed in was empty.
**/
template <typename Cont>
auto data(PL_IN Cont &cont) noexcept -> decltype(auto)
{
    return cont.data();
}

/*!
 * \brief Function to get a pointer to the first (index 0) element of a C-Array.
 * \param arr The C-Array for which
 *        to get the pointer to its first (index 0) element from.
**/
template <typename Type, std::size_t Size>
auto data(PL_IN Type (&arr)[Size]) noexcept -> decltype(auto)
{
    return std::addressof(arr[0]);
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_DATA_HPP
