/*!
 * \file make_array.hpp
 * \brief Exports the makeArray function that creates a std::array
 *        from a given template type parameter pack.
**/
#ifndef INCG_PL_CONT_MAKE_ARRAY_HPP
#define INCG_PL_CONT_MAKE_ARRAY_HPP
#include "../macros.hpp" // PL_IN
#include <utility> // std::forward
#include <array> // std::array
#include <type_traits> // std::common_type_t

namespace pl
{
namespace cont
{
/*!
 * \brief Creates a std::array from a template type parameter pack.
 * \param args The arguments to construct the std::array returned from.
 * \return The resulting std::array.
 * \note The resulting std::array will use the common type for all of its
 *       elements. Some of the values passed in may be converted to that common type.
**/
template <typename ...Args>
constexpr auto makeArray(PL_IN Args &&...args)
    -> std::array<std::common_type_t<Args ...>, sizeof...(args)>
{
    return {
        static_cast<std::common_type_t<Args ...>>(
            std::forward<Args>(args)
        )...
    };
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_MAKE_ARRAY_HPP
