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
 * \file uninitialized_value_construct.hpp
 * \brief Exports the C++17 uninitialized_value_construct algorithm.
**/
#ifndef INCG_PL_ALGO_UNINITIALIZED_VALUE_CONSTRUCT_HPP
#define INCG_PL_ALGO_UNINITIALIZED_VALUE_CONSTRUCT_HPP
#include <iterator> // std::iterator_traits
#include <memory>   // std::addressof
#include <new>      // ::operator new

namespace pl {
namespace algo {
/*!
 * \brief Constructs objects of type
 *        typename iterator_traits<'ForwardIterator'>::value_type in the
 *        uninitialized storage designated by the range ['first', 'last')
 *        by value-initialization.
 * \param first The begin iterator of the range of elements to initialize.
 * \param last The end iterator of the range of elements to initialize.
 * \warning No increment, assignment, comparison, or indirection through
 *          valid instances of 'ForwardIterator' may throw exceptions.
 * \note If an exception is thrown during the initialization, the function
 *       has no effects.
 *       The complexity is linear in the distance between 'first' and 'last'.
**/
template <typename ForwardIterator>
inline void uninitialized_value_construct(
    ForwardIterator first,
    ForwardIterator last)
{
    using value_type =
        typename std::iterator_traits<ForwardIterator>::value_type;

    ForwardIterator cur{first};

    try {
        while (cur != last) {
            ::new (static_cast<void*>(std::addressof(*cur))) value_type();

            ++cur;
        }
    }
    catch (...) {
        while (first != cur) {
            first->~value_type();
            ++first;
        }

        throw;
    }
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_UNINITIALIZED_VALUE_CONSTRUCT_HPP
