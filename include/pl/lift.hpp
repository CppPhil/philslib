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
 * \file lift.hpp
 * \brief Exports the PL_LIFT function like macro.
 **/
#ifndef INCG_PL_LIFT_HPP
#define INCG_PL_LIFT_HPP
#include "fwd.hpp" // PL_FWD

/*!
 * \def PL_LIFT(...)
 * \brief Function like macro that 'lifts' the given identifier representing
 *        an overload resolution set into a lambda closure object serving
 *        as the corresponding overload resolution object. Useful in conjunction
 *        with STL algorithms when the overload shall be resolved within the
 *        context of the callable object being called from within the generic
 *        algorithm.
 **/
#define PL_LIFT(...)                                                           \
  [](auto&&... args) noexcept(noexcept(                                        \
    __VA_ARGS__(PL_FWD(args)...))) -> decltype(__VA_ARGS__(PL_FWD(args)...)) { \
    return __VA_ARGS__(PL_FWD(args)...);                                       \
  }
#endif // INCG_PL_LIFT_HPP
