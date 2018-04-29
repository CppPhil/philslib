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
 * \file as_ptr_const.hpp
 * \brief Exports the asPtrConst function template.
**/
#ifndef INCG_PL_AS_PTR_CONST_HPP
#define INCG_PL_AS_PTR_CONST_HPP
#include "annotations.hpp" // PL_IN_OPT
#include <type_traits> // std::add_const_t

namespace pl
{
/*!
 * \brief Returns a low level const qualified pointer to the object
 *        that is pointed to by 'p'.
 * \param p The pointer passed in.
 * \return A low level const qualified pointer to the object that is pointed
 *         to by 'p'.
**/
template <typename Ty>
constexpr std::add_const_t<Ty> *asPtrConst(PL_IN_OPT Ty *p) noexcept
{
    return p;
}
} // namespace pl
#endif // INCG_PL_AS_PTR_CONST_HPP
