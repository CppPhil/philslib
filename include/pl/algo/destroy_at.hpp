/*!
 * \file destroy_at.hpp
 * \brief Exports the C++17 destroy_at algorithm.
**/
#ifndef INCG_PL_ALGO_DESTROY_AT_HPP
#define INCG_PL_ALGO_DESTROY_AT_HPP
#include "../annotations.hpp" // PL_OUT
#include "../assert.hpp" // PL_DBG_CHECK_PRE
#include <cstddef> // std::nullptr_t

namespace pl
{
namespace algo
{
/*!
 * \brief Calls the destructor of the object pointed to by 'ptr',
 *        as if by ptr->~Ty();
 * \param ptr A pointer to the object to be destroyed. May not be nullptr!
**/
template <typename Ty>
void destroy_at(PL_OUT Ty *ptr)
{
    PL_DBG_CHECK_PRE(ptr != nullptr);

    ptr->~Ty();
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_DESTROY_AT_HPP
