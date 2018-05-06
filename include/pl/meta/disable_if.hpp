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
 * \file disable_if.hpp
 * \brief Exports the disable_if meta function.
**/
#ifndef INCG_PL_META_DISABLE_IF_HPP
#define INCG_PL_META_DISABLE_IF_HPP

namespace pl {
namespace meta {
/*!
 * \brief The disable_if meta function.
 * \note This is the false case.
 *
 * disable_if behaves like an inverted std::enable_if,
 * that is if the condition 'BoolVal' is false the
 * nested type 'type' will be defined.
 * If 'BoolVal' is true the nested type 'type' will not be defined.
**/
template <bool BoolVal, typename Ty = void>
struct disable_if {
    // BoolVal is false -> ok.
    using type = Ty;
};

/*!
 * \brief The disable_if meta function.
 * \note This is the true case.
 *
 * disable_if behaves like an inverted std::enable_if,
 * that is if the condition 'BoolVal' is false the
 * nested type 'type' will be defined.
 * If 'BoolVal' is true the nested type 'type' will not be defined.
**/
template <typename Ty>
struct disable_if<true, Ty> {
    // BoolVal is true -> SFINAE away.
};

/*!
 * \brief C++14 style helper template alias for disable_if.
**/
template <bool BoolVal, typename Ty = void>
using disable_if_t = typename disable_if<BoolVal, Ty>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_DISABLE_IF_HPP
