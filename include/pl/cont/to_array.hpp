#ifndef INCG_PL_CONT_TO_ARRAY_HPP
#define INCG_PL_CONT_TO_ARRAY_HPP
#include "../annotations.hpp" // PL_IN
#include <cstddef> // std::size_t
#include <utility> // std::index_sequence
#include <array> // std::array
#include <type_traits> // std::remove_cv_t

namespace pl
{
namespace cont
{
namespace detail
{
/*!
 * \brief Implementation function of toArray, not to be used diretly.
**/
template <typename Ty, std::size_t Size, std::size_t ...Indices>
constexpr std::array<std::remove_cv_t<Ty>, Size>
toArrayImpl(PL_IN Ty (&array)[Size], std::index_sequence<Indices ...>)
{
    return { { array[Indices] ... } };
}
} // namespace detail

/*!
 * \brief Creates a std::array from a built-in array.
 * \param array The built-in array to be used to initialize the std::array.
 * \return A std::array object whose elements are copy-initialized from
 *         the corresponding element of 'array'.
 *
 * Creates a std::array from the built-in array 'array'.
 * The elements of the std::array are copy-initialized from the
 * corresponding element of 'array'.
**/
template <typename Ty, std::size_t Size>
constexpr std::array<std::remove_cv_t<Ty>, Size> toArray(
    PL_IN Ty (&array)[Size])
{
    return detail::toArrayImpl(array, std::make_index_sequence<Size>{ });
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_TO_ARRAY_HPP
