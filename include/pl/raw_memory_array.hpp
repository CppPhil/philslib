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
 * \file raw_memory_array.hpp
 * \brief Exports the raw_memory_array template type.
 **/
#ifndef INCG_PL_RAW_MEMORY_ARRAY_HPP
#define INCG_PL_RAW_MEMORY_ARRAY_HPP
#include "algo/destroy.hpp" // pl::algo::destroy
#include "annotations.hpp"  // PL_NODISCARD, PL_OUT, PL_IN
#include "assert.hpp"       // PL_DBG_CHECK_PRE
#include <algorithm> // std::fill, std::equal, std::lexicographical_compare
#include <ciso646>   // not
#include <cstddef>   // std::size_t, std::ptrdiff_t
#include <iterator>  // std::reverse_iterator
#include <memory>    // std::uninitialized_fill
#include <stdexcept> // std::out_of_range

namespace pl {
/*!
 * \brief Type that can be used to treat some raw memory as a fixed size array.
 **/
template<typename Ty>
class raw_memory_array {
public:
    using this_type              = raw_memory_array;
    using value_type             = Ty;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /*!
     * \brief Creates a raw_memory_array by placement new'ing copies of
     *        'initial_value' into the raw memory passed in.
     * \param raw_memory Pointer to the first (0th) byte of the raw memory
     *                   that shall be treated as an array.
     * \param byte_count The size of the raw memory pointed to by 'raw_memory'
     *                   in bytes. May not be incorrect!
     * \param initial_value The initial value to be used in order to fill
     *                      the raw memory by using placement new.
     * \warning The raw memory may not be deallocated within the lifetime
     *          of this object.
     *          The raw memory must have been (statically or dynamically)
     *          allocated as a contiguous sequence in memory (such as an array)
     *          of either char, signed char, unsigned char,
     *          std::byte (since C++17), or an alias of one of these types.
     *          Or alternatively by some raw memory allocating function such as
     *          std::malloc or a version of alloca (non-standard).
     *          Specifically there must be no aliasing violation by
     *          reinterpreting the raw memory supplied as 'Ty' through a Ty *
     *          pointer type. Note that using an array of std::uint8_t or
     *          std::int8_t is not legal as these types are not required to
     *          be aliases of the above mentioned types, which are exempt
     *          from the strict aliasing rules.
     *          Additionally the raw memory must be suitably aligned for the
     *          value_type objects that are to be placed into it.
     **/
    raw_memory_array(
        PL_OUT void*          raw_memory,
        size_type             byte_count,
        PL_IN const_reference initial_value = value_type())
        : m_data{static_cast<pointer>(raw_memory)}
        , m_size{byte_count / sizeof(value_type)}
    {
        std::uninitialized_fill(begin(), end(), initial_value);
    }

    /*!
     * \brief Destroys the raw_memory_array by calling the destructors
     *        of all the elements that were placement new'ed into the raw
     *        memory.
     **/
    ~raw_memory_array() { ::pl::algo::destroy(begin(), end()); }
    /*!
     * \brief This type is non-copyable.
     **/
    raw_memory_array(const this_type&) = delete;

    /*!
     * \brief This type is non-copyable.
     **/
    this_type& operator=(const this_type&) = delete;

    /*!
     * \brief Returns a reference to the element at specified location
     *        'pos', with bounds checking.
     * \param pos Position of the element to return.
     * \return Reference to the requested element.
     * \throws std::out_of_range if 'pos' is not within the range of
     *         the raw_memory_array.
     * \note Constant complexity.
     **/
    PL_NODISCARD reference at(size_type pos)
    {
        if (not(pos < size())) {
            throw std::out_of_range{
                "pos in pl::raw_memory_array::at was out of bounds!"};
        }

        return (*this)[pos];
    }

    /*!
     * \brief Returns a reference to the element at specified location
     *        'pos', with bounds checking.
     * \param pos Position of the element to return.
     * \return Reference to the requested element.
     * \throws std::out_of_range if 'pos' is not within the range of
     *         the raw_memory_array.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_reference at(size_type pos) const
    {
        return const_cast<this_type*>(this)->at(pos);
    }

    /*!
     * \brief Returns a reference to the element at specified location 'pos'.
     *        No bounds checking is performed!
     * \param pos Position of the element to return.
     * \return Reference to the requested element.
     * \warning Causes undefined behavior if 'pos' is out of bounds.
     * \note Constant complexity.
     **/
    PL_NODISCARD reference operator[](size_type pos) noexcept
    {
        return m_data[pos];
    }

    /*!
     * \brief Returns a reference to the element at specified location 'pos'.
     *        No bounds checking is performed!
     * \param pos Position of the element to return.
     * \return Reference to the requested element.
     * \warning Causes undefined behavior if 'pos' is out of bounds.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_reference operator[](size_type pos) const noexcept
    {
        return const_cast<this_type*>(this)->operator[](pos);
    }

    /*!
     * \brief Returns a reference to the first element.
     * \return Reference to the first elements.
     * \warning Calling front on an empty raw_memory_array is undefined.
     * \note Constant complexity.
     **/
    PL_NODISCARD reference front()
    {
        PL_DBG_CHECK_PRE(not empty());
        return *begin();
    }

    /*!
     * \brief Returns a reference to the first element.
     * \return Reference to the first elements.
     * \warning Calling front on an empty raw_memory_array is undefined.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_reference front() const
    {
        return const_cast<this_type*>(this)->front();
    }

    /*!
     * \brief Returns a reference to the last element.
     * \return Reference to the last element.
     * \warning Calling back on an empty raw_memory_array is undefined.
     * \note Constant complexity.
     **/
    PL_NODISCARD reference back()
    {
        PL_DBG_CHECK_PRE(not empty());
        return *rbegin();
    }

    /*!
     * \brief Returns a reference to the last element.
     * \return Reference to the last element.
     * \warning Calling back on an empty raw_memory_array is undefined.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_reference back() const
    {
        return const_cast<this_type*>(this)->back();
    }

    /*!
     * \brief Returns a pointer to the underlying element storage.
     *        The pointer is such that range [data(), data() + size()) is always
     *        a valid range, even if the raw_memory_array is
     *        empty (data() is not dereferenceable in that case).
     * \return Pointer to the underlying element storage.
     *         For non-empty raw_memory_arrays, the returned pointer compares
     *         equal to the address of the first element.
     * \note Constant complexity.
     **/
    PL_NODISCARD pointer data() noexcept { return m_data; }
    /*!
     * \brief Returns a pointer to the underlying element storage.
     *        The pointer is such that range [data(), data() + size()) is always
     *        a valid range, even if the raw_memory_array is
     *        empty (data() is not dereferenceable in that case).
     * \return Pointer to the underlying element storage.
     *         For non-empty raw_memory_arrays, the returned pointer compares
     *         equal to the address of the first element.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_pointer data() const noexcept
    {
        return const_cast<this_type*>(this)->data();
    }

    /*!
     * \brief Returns a pointer to the underlying element storage.
     *        The pointer is such that range
     *        [const_data(), const_data() + size())
     *        is always a valid range, even if the raw_memory_array is
     *        empty (const_data() is not dereferenceable in that case).
     * \return Pointer to the underlying element storage.
     *         For non-empty raw_memory_arrays, the returned pointer compares
     *         equal to the address of the first element.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_pointer const_data() const noexcept { return data(); }
    /*!
     * \brief Returns an iterator to the first element.
     * \return Iterator to the first element.
     * \note Constant complexity.
     *
     * Returns an iterator to the first element.
     * If the raw_memory_array is empty, the returned iterator will be
     * equal to end().
     **/
    PL_NODISCARD iterator begin() noexcept { return data(); }
    /*!
     * \brief Returns an iterator to the first element.
     * \return Iterator to the first element.
     * \note Constant complexity.
     *
     * Returns an iterator to the first element.
     * If the raw_memory_array is empty, the returned iterator will be
     * equal to end().
     **/
    PL_NODISCARD const_iterator begin() const noexcept
    {
        return const_cast<this_type*>(this)->begin();
    }

    /*!
     * \brief Returns an iterator to the first element.
     * \return Iterator to the first element.
     * \note Constant complexity.
     *
     * Returns an iterator to the first element.
     * If the raw_memory_array is empty, the returned iterator will be
     * equal to end().
     **/
    PL_NODISCARD const_iterator cbegin() const noexcept { return begin(); }
    /*!
     * \brief Returns an iterator to the element following the last element.
     * \return Iterator to the element following the last element.
     * \warning Dereferencing the iterator returned results in undefined
     *behavior.
     * \note Constant complexity.
     **/
    PL_NODISCARD iterator end() noexcept { return m_data + m_size; }
    /*!
     * \brief Returns an iterator to the element following the last element.
     * \return Iterator to the element following the last element.
     * \warning Dereferencing the iterator returned results in undefined
     *behavior.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_iterator end() const noexcept
    {
        return const_cast<this_type*>(this)->end();
    }

    /*!
     * \brief Returns an iterator to the element following the last element.
     * \return Iterator to the element following the last element.
     * \warning Dereferencing the iterator returned results in undefined
     *behavior.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_iterator cend() const noexcept { return end(); }
    /*!
     * \brief Returns a reverse iterator to the first element of the
     *        reversed raw_memory_array. It corresponds to the last element
     *        of the non-reversed raw_memory_array.
     * \return Reverse iterator to the first element.
     * \note Constant complexity.
     **/
    PL_NODISCARD reverse_iterator rbegin() noexcept
    {
        return reverse_iterator{end()};
    }

    /*!
     * \brief Returns a reverse iterator to the first element of the
     *        reversed raw_memory_array. It corresponds to the last element
     *        of the non-reversed raw_memory_array.
     * \return Reverse iterator to the first element.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_reverse_iterator rbegin() const noexcept
    {
        return const_cast<this_type*>(this)->rbegin();
    }

    /*!
     * \brief Returns a reverse iterator to the first element of the
     *        reversed raw_memory_array. It corresponds to the last element
     *        of the non-reversed raw_memory_array.
     * \return Reverse iterator to the first element.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_reverse_iterator crbegin() const noexcept
    {
        return rbegin();
    }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed raw_memory_array. It corresponds to the
     *        element preceding the first element of the non-reversed
     *        raw_memory_array. This element acts as a placeholder, attempting
     *        to access it results in undefined behavior.
     * \return Reverse iterator to the element following the last element.
     * \note Constant complexity.
     **/
    PL_NODISCARD reverse_iterator rend() noexcept
    {
        return reverse_iterator{begin()};
    }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed raw_memory_array. It corresponds to the
     *        element preceding the first element of the non-reversed
     *        raw_memory_array. This element acts as a placeholder, attempting
     *        to access it results in undefined behavior.
     * \return Reverse iterator to the element following the last element.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_reverse_iterator rend() const noexcept
    {
        return const_cast<this_type*>(this)->rend();
    }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed raw_memory_array. It corresponds to the
     *        element preceding the first element of the non-reversed
     *        raw_memory_array. This element acts as a placeholder, attempting
     *        to access it results in undefined behavior.
     * \return Reverse iterator to the element following the last element.
     * \note Constant complexity.
     **/
    PL_NODISCARD const_reverse_iterator crend() const noexcept
    {
        return rend();
    }

    /*!
     * \brief Checks if the raw_memory_array has no elements.
     * \return true if the raw_memory_array is empty, false otherwise.
     **/
    PL_NODISCARD bool empty() const noexcept { return size() == 0U; }
    /*!
     * \brief Returns the number of elements.
     * \return The number of elements.
     * \note Constant complexity.
     **/
    PL_NODISCARD size_type size() const noexcept { return m_size; }
    /*!
     * \brief Returns the maximum number of elements this object is able to
     *        hold due to system or implementation limitations.
     * \return Maximum number of elements.
     * \note Constant complexity.
     *       Because raw_memory_array is of fixed size the value returned is
     *equal
     *       to the value returned by size().
     **/
    PL_NODISCARD size_type max_size() const noexcept { return size(); }
    /*!
     * \brief Assigns the given value to all elements.
     * \param value The value to assign to the elements.
     * \return A reference to this object.
     * \note Complexity is linear in .size().
     **/
    this_type& fill(PL_IN const_reference value)
    {
        std::fill(begin(), end(), value);

        return *this;
    }

    /*!
     * \brief Assigns the given value to all elements.
     * \param value The value to assign to the elements.
     * \return A reference to this object.
     * \note Complexity is linear in .size().
     **/
    this_type& assign(PL_IN const_reference value) { return fill(value); }

private:
    pointer   m_data; /*!< Pointer to the raw memory interpreted as 'Ty'. */
    size_type m_size; /*!< The amount of elements that fit in the raw memory */
};

/*!
 * \brief Checks if the contents of 'lhs' and 'rhs' are equal, that is,
 *        whether each element in 'lhs' compares equal with the element
 *        in 'rhs' at the same position.
 * \param lhs The object to compare with 'rhs'.
 * \param rhs The object to compare with 'lhs'.
 * \return true if the contents of the raw_memory_arrays are equal,
 *         false otherwise.
 * \note Returns false if 'lhs' and 'rhs' are not of the same size.
 **/
template<typename Ty>
bool operator==(
    PL_IN const ::pl::raw_memory_array<Ty>& lhs,
    PL_IN const ::pl::raw_memory_array<Ty>& rhs)
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/*!
 * \brief Checks if the contents of 'lhs' and 'rhs' are not equal, that is,
 *        whether each element in 'lhs' compares not equal with the element
 *        in 'rhs' at the same position.
 * \param lhs The object to compare with 'rhs'.
 * \param rhs The object to compare with 'lhs'.
 * \return true if the contents of the raw_memory_arrays are not equal,
 *         false otherwise.
 * \note Returns true if 'lhs' and 'rhs' are not of the same size.
 **/
template<typename Ty>
bool operator!=(
    PL_IN const ::pl::raw_memory_array<Ty>& lhs,
    PL_IN const ::pl::raw_memory_array<Ty>& rhs)
{
    return not(lhs == rhs);
}

/*!
 * \brief Compares the contents of 'lhs' and 'rhs' lexicographically.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \return true if the contents of 'lhs' are lexicographically less than
 *         the contents of 'rhs', false otherwise
 **/
template<typename Ty>
bool operator<(
    PL_IN const ::pl::raw_memory_array<Ty>& lhs,
    PL_IN const ::pl::raw_memory_array<Ty>& rhs)
{
    return std::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/*!
 * \brief Compares the contents of 'lhs' and 'rhs' lexicographically.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \return true if the contents of 'lhs' are lexicographically less than or
 *         equal the contents of 'rhs', false otherwise
 **/
template<typename Ty>
bool operator<=(
    PL_IN const ::pl::raw_memory_array<Ty>& lhs,
    PL_IN const ::pl::raw_memory_array<Ty>& rhs)
{
    return not(rhs < lhs);
}

/*!
 * \brief Compares the contents of 'lhs' and 'rhs' lexicographically.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \return true if the contents of 'lhs' are lexicographically greater than
 *         the contents of 'rhs', false otherwise
 **/
template<typename Ty>
bool operator>(
    PL_IN const ::pl::raw_memory_array<Ty>& lhs,
    PL_IN const ::pl::raw_memory_array<Ty>& rhs)
{
    return rhs < lhs;
}

/*!
 * \brief Compares the contents of 'lhs' and 'rhs' lexicographically.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \return true if the contents of 'lhs' are lexicographically greater than or
 *         equal the contents of 'rhs', false otherwise
 **/
template<typename Ty>
bool operator>=(
    PL_IN const ::pl::raw_memory_array<Ty>& lhs,
    PL_IN const ::pl::raw_memory_array<Ty>& rhs)
{
    return not(lhs < rhs);
}
} // namespace pl
#endif // INCG_PL_RAW_MEMORY_ARRAY_HPP
