/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

/*!
 * \file destroy_at.hpp
 * \brief Exports the C++17 destroy_at algorithm.
 **/
#ifndef INCG_PL_ALGO_DESTROY_AT_HPP
#define INCG_PL_ALGO_DESTROY_AT_HPP
#include "../annotations.hpp" // PL_OUT
#include "../assert.hpp"      // PL_DBG_CHECK_PRE
#include <cstddef>            // std::nullptr_t

namespace pl {
namespace algo {
/*!
 * \brief Calls the destructor of the object pointed to by 'ptr',
 *        as if by ptr->~Ty();
 * \param ptr A pointer to the object to be destroyed. May not be nullptr
 *            or otherwise be invalid.
 **/
template<typename Ty>
inline void destroy_at(PL_OUT Ty* ptr)
{
    PL_DBG_CHECK_PRE(ptr != nullptr);

    (void)ptr; // suppress msvc warning about parameter 'ptr' being 'unused'.

    ptr->~Ty();
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_DESTROY_AT_HPP
