#ifndef INCG_PL_RAW_MEMORY_ARRAY_HPP
#define INCG_PL_RAW_MEMORY_ARRAY_HPP
#include "annotations.hpp" // PL_NODISCARD, PL_OUT, PL_IN
#include "except.hpp" // pl::InvalidSizeException
#include "algo/uninitialized_move.hpp" // pl::algo::uninitialized_move
#include "algo/destroy.hpp" // pl::algo::destroy
#include <ciso646> // not
#include <cstddef> // std::size_t, std::ptrdiff_t
#include <stdexcept> // std::out_of_range
#include <iterator> // std::reverse_iterator
#include <initializer_list> // std::initializer_list
#include <memory> // std::uninitialized_fill
#include <algorithm> // std::fill, std::equal, std::lexicographical_compare

namespace pl
{
/*!
 * \brief Type that can be used to treat some raw memory as a fixed size array.
**/
template <typename Ty>
class RawMemoryArray
{
public:
    using this_type = RawMemoryArray;
    using value_type = Ty;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /*!
     * \brief Creates a RawMemoryArray by placement new'ing copies of
     *        'initialValue' into the raw memory passed in.
     * \param rawMemory Pointer to the first (0th) byte of the raw memory
     *                  that shall be treated as an array.
     * \param byteCount The size of the raw memory pointed to by 'rawMemory'
     *                  in bytes. May not be incorrect!
     * \param initialValue The initial value to be used in order to fill
     *                     the raw memory by using placement new.
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
    **/
    RawMemoryArray(
        PL_OUT void *rawMemory,
        size_type byteCount,
        PL_IN const_reference initialValue = value_type())
        : m_data{ static_cast<pointer>(rawMemory) },
          m_size{ byteCount / sizeof(value_type) }
    {
        std::uninitialized_fill(begin(), end(), initialValue);
    }

    /*!
     * \brief Creates a RawMemoryArray by placement new'ing copies of
     *        the values in the 'initList' into the raw memory passed in.
     * \param rawMemory Pointer to the first (0th) byte of the raw memory
     *                  that shall be treated as an array.
     * \param byteCount The size of the raw memory pointed to by 'rawMemory'
     *                  in bytes. May not be incorrect!
     * \param initList The initializer_list that holds the values that the
     *                 raw memory shall be initialized with. Must have a size
     *                 of exactly 'byteCount' / sizeof('Ty') (integer division).
     * \throws pl::InvalidSizeException if the size of the initializer_list is
     *         incorrect.
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
    **/
    RawMemoryArray(
        PL_OUT void *rawMemory,
        size_type byteCount,
        std::initializer_list<value_type> initList)
        : m_data{ static_cast<pointer>(rawMemory) },
          m_size{ byteCount / sizeof(value_type) }
    {
        if (m_size != initList.size()) {
            throw ::pl::InvalidSizeException{
                "m_size was not equal to initList.size() in RawMemoryArray ctor."
            };
        }

        ::pl::algo::uninitialized_move(initList.begin(), initList.end(), begin());
    }

    /*!
     * \brief Destroys the RawMemoryArray by calling the destructors
     *        of all the elements that were placement new'ed into the raw
     *        memory.
    **/
    ~RawMemoryArray()
    {
        ::pl::algo::destroy(begin(), end());
    }

    /*!
     * \brief This type is non-copyable.
    **/
    RawMemoryArray(const this_type &) = delete;

    /*!
     * \brief This type is non-copyable.
    **/
    this_type &operator=(const this_type &) = delete;

    /*!
     * \brief Returns a reference to the element at specified location
     *        'pos', with bounds checking.
     * \param pos Position of the element to return.
     * \return Reference to the requested element.
     * \throws std::out_of_range if 'pos' is not within the range of
     *         the RawMemoryArray.
     * \note Constant complexity.
    **/
    PL_NODISCARD reference at(size_type pos)
    {
        if (not (pos < size())) {
            throw std::out_of_range{
                "pos in pl::RawMemoryArray::at was out of bounds!"
            };
        }

        return (*this)[pos];
    }

    /*!
     * \brief Returns a reference to the element at specified location
     *        'pos', with bounds checking.
     * \param pos Position of the element to return.
     * \return Reference to the requested element.
     * \throws std::out_of_range if 'pos' is not within the range of
     *         the RawMemoryArray.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_reference at(size_type pos) const
    {
        return const_cast<this_type *>(this)->at(pos);
    }

    /*!
     * \brief Returns a reference to the element at specified location 'pos'.
     *        No bounds checking is performed!
     * \param pos Position of the element to return.
     * \return Reference to the requested element.
     * \warning Causes undefined behavior if 'pos' is out of bounds.
     * \note Constant complexity.
    **/
    PL_NODISCARD constexpr reference operator[](size_type pos)
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
    PL_NODISCARD const_reference operator[](size_type pos) const
    {
        return const_cast<this_type *>(this)->operator[](pos);
    }

    /*!
     * \brief Returns a reference to the first element.
     * \return Reference to the first elements.
     * \warning Calling front on an empty RawMemoryArray is undefined.
     * \note Constant complexity.
    **/
    PL_NODISCARD reference front()
    {
        return *begin();
    }

    /*!
     * \brief Returns a reference to the first element.
     * \return Reference to the first elements.
     * \warning Calling front on an empty RawMemoryArray is undefined.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_reference front() const
    {
        return const_cast<this_type *>(this)->front();
    }

    /*!
     * \brief Returns a reference to the last element.
     * \return Reference to the last element.
     * \warning Calling back on an empty RawMemoryArray is undefined.
     * \note Constant complexity.
    **/
    PL_NODISCARD reference back()
    {
        return *rbegin();
    }

    /*!
     * \brief Returns a reference to the last element.
     * \return Reference to the last element.
     * \warning Calling back on an empty RawMemoryArray is undefined.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_reference back() const
    {
        return const_cast<this_type *>(this)->back();
    }

    /*!
     * \brief Returns a pointer to the underlying element storage.
     *        The pointer is such that range [data(), data() + size()) is always
     *        a valid range, even if the RawMemoryArray is
     *        empty (data() is not dereferenceable in that case).
     * \return Pointer to the underlying element storage.
     *         For non-empty RawMemoryArrays, the returned pointer compares
     *         equal to the address of the first element.
     * \note Constant complexity.
    **/
    PL_NODISCARD pointer data() noexcept
    {
        return m_data;
    }

    /*!
     * \brief Returns a pointer to the underlying element storage.
     *        The pointer is such that range [data(), data() + size()) is always
     *        a valid range, even if the RawMemoryArray is
     *        empty (data() is not dereferenceable in that case).
     * \return Pointer to the underlying element storage.
     *         For non-empty RawMemoryArrays, the returned pointer compares
     *         equal to the address of the first element.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_pointer data() const noexcept
    {
        return const_cast<this_type *>(this)->data();
    }

    /*!
     * \brief Returns a pointer to the underlying element storage.
     *        The pointer is such that range [constData(), constData() + size())
     *        is always a valid range, even if the RawMemoryArray is
     *        empty (constData() is not dereferenceable in that case).
     * \return Pointer to the underlying element storage.
     *         For non-empty RawMemoryArrays, the returned pointer compares
     *         equal to the address of the first element.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_pointer constData() const noexcept
    {
        return data();
    }

    /*!
     * \brief Returns an iterator to the first element.
     * \return Iterator to the first element.
     * \note Constant complexity.
     *
     * Returns an iterator to the first element.
     * If the RawMemoryArray is empty, the returned iterator will be
     * equal to end().
    **/
    PL_NODISCARD iterator begin() noexcept
    {
        return data();
    }

    /*!
     * \brief Returns an iterator to the first element.
     * \return Iterator to the first element.
     * \note Constant complexity.
     *
     * Returns an iterator to the first element.
     * If the RawMemoryArray is empty, the returned iterator will be
     * equal to end().
    **/
    PL_NODISCARD const_iterator begin() const noexcept
    {
        return const_cast<this_type *>(this)->begin();
    }

    /*!
     * \brief Returns an iterator to the first element.
     * \return Iterator to the first element.
     * \note Constant complexity.
     *
     * Returns an iterator to the first element.
     * If the RawMemoryArray is empty, the returned iterator will be
     * equal to end().
    **/
    PL_NODISCARD const_iterator cbegin() const noexcept
    {
        return begin();
    }

    /*!
     * \brief Returns an iterator to the element following the last element.
     * \return Iterator to the element following the last element.
     * \warning Dereferencing the iterator returned results in undefined behavior.
     * \note Constant complexity.
    **/
    PL_NODISCARD iterator end() noexcept
    {
        return m_data + m_size;
    }

    /*!
     * \brief Returns an iterator to the element following the last element.
     * \return Iterator to the element following the last element.
     * \warning Dereferencing the iterator returned results in undefined behavior.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_iterator end() const noexcept
    {
        return const_cast<this_type *>(this)->end();
    }

    /*!
     * \brief Returns an iterator to the element following the last element.
     * \return Iterator to the element following the last element.
     * \warning Dereferencing the iterator returned results in undefined behavior.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_iterator cend() const noexcept
    {
        return end();
    }

    /*!
     * \brief Returns a reverse iterator to the first element of the
     *        reversed RawMemoryArray. It corresponds to the last element
     *        of the non-reversed RawMemoryArray.
     * \return Reverse iterator to the first element.
     * \note Constant complexity.
    **/
    PL_NODISCARD reverse_iterator rbegin() noexcept
    {
        return end();
    }

    /*!
     * \brief Returns a reverse iterator to the first element of the
     *        reversed RawMemoryArray. It corresponds to the last element
     *        of the non-reversed RawMemoryArray.
     * \return Reverse iterator to the first element.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_reverse_iterator rbegin() const noexcept
    {
        return const_cast<this_type *>(this)->rbegin();
    }

    /*!
     * \brief Returns a reverse iterator to the first element of the
     *        reversed RawMemoryArray. It corresponds to the last element
     *        of the non-reversed RawMemoryArray.
     * \return Reverse iterator to the first element.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_reverse_iterator crbegin() const noexcept
    {
        return rbegin();
    }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed RawMemoryArray. It corresponds to the
     *        element preceding the first element of the non-reversed
     *        RawMemoryArray. This element acts as a placeholder, attempting to
     *        access it results in undefined behavior.
     * \return Reverse iterator to the element following the last element.
     * \note Constant complexity.
    **/
    PL_NODISCARD reverse_iterator rend() noexcept
    {
        return begin();
    }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed RawMemoryArray. It corresponds to the
     *        element preceding the first element of the non-reversed
     *        RawMemoryArray. This element acts as a placeholder, attempting to
     *        access it results in undefined behavior.
     * \return Reverse iterator to the element following the last element.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_reverse_iterator rend() const noexcept
    {
        return const_cast<this_type *>(this)->rend();
    }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed RawMemoryArray. It corresponds to the
     *        element preceding the first element of the non-reversed
     *        RawMemoryArray. This element acts as a placeholder, attempting to
     *        access it results in undefined behavior.
     * \return Reverse iterator to the element following the last element.
     * \note Constant complexity.
    **/
    PL_NODISCARD const_reverse_iterator crend() const noexcept
    {
        return rend();
    }

    /*!
     * \brief Checks if the RawMemoryArray has no elements.
     * \return true if the RawMemoryArray is empty, false otherwise.
    **/
    PL_NODISCARD bool empty() const noexcept
    {
        return size() == 0U;
    }

    /*!
     * \brief Returns the number of elements.
     * \return The number of elements.
     * \note Constant complexity.
    **/
    PL_NODISCARD size_type size() const noexcept
    {
        return m_size;
    }

    /*!
     * \brief Returns the maximum number of elements this object is able to
     *        hold due to system or implementation limitations.
     * \return Maximum number of elements.
     * \note Constant complexity.
     *       Because RawMemoryArray is of fixed size the value returned is equal
     *       to the value returned by size().
    **/
    PL_NODISCARD size_type max_size() const noexcept
    {
        return size();
    }

    /*!
     * \brief Assigns the given value to all elements.
     * \param value The value to assign to the elements.
     * \return A reference to this object.
     * \note Complexity is linear in .size().
    **/
    this_type &fill(PL_IN const_reference value)
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
    this_type &assign(PL_IN const_reference value)
    {
        return fill(value);
    }

private:
    pointer m_data; /*!< Pointer to the raw memory interpreted as 'Ty'. */
    size_type m_size; /*!< The amount of elements that fit in the raw memory */
};

/*!
 * \brief Checks if the contents of 'lhs' and 'rhs' are equal, that is,
 *        whether each element in 'lhs' compares equal with the element
 *        in 'rhs' at the same position.
 * \param lhs The object to compare with 'rhs'.
 * \param rhs The object to compare with 'lhs'.
 * \return true if the contents of the RawMemoryArrays are equal,
 *         false otherwise.
 * \note Returns false if 'lhs' and 'rhs' are not of the same size.
**/
template <typename Ty>
bool operator==(
    const ::pl::RawMemoryArray<Ty> &lhs,
    const ::pl::RawMemoryArray<Ty> &rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/*!
 * \brief Checks if the contents of 'lhs' and 'rhs' are not equal, that is,
 *        whether each element in 'lhs' compares not equal with the element
 *        in 'rhs' at the same position.
 * \param lhs The object to compare with 'rhs'.
 * \param rhs The object to compare with 'lhs'.
 * \return true if the contents of the RawMemoryArrays are not equal,
 *         false otherwise.
 * \note Returns true if 'lhs' and 'rhs' are not of the same size.
**/
template <typename Ty>
bool operator!=(
    const ::pl::RawMemoryArray<Ty> &lhs,
    const ::pl::RawMemoryArray<Ty> &rhs)
{
    return not (lhs == rhs);
}

/*!
 * \brief Compares the contents of 'lhs' and 'rhs' lexicographically.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \return true if the contents of 'lhs' are lexicographically less than
 *         the contents of 'rhs', false otherwise
**/
template <typename Ty>
bool operator<(
    const ::pl::RawMemoryArray<Ty> &lhs,
    const ::pl::RawMemoryArray<Ty> &rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end());
}

/*!
 * \brief Compares the contents of 'lhs' and 'rhs' lexicographically.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \return true if the contents of 'lhs' are lexicographically less than or equal
 *         the contents of 'rhs', false otherwise
**/
template <typename Ty>
bool operator<=(
    const ::pl::RawMemoryArray<Ty> &lhs,
    const ::pl::RawMemoryArray<Ty> &rhs)
{
    return not (rhs < lhs);
}

/*!
 * \brief Compares the contents of 'lhs' and 'rhs' lexicographically.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \return true if the contents of 'lhs' are lexicographically greater than
 *         the contents of 'rhs', false otherwise
**/
template <typename Ty>
bool operator>(
    const ::pl::RawMemoryArray<Ty> &lhs,
    const ::pl::RawMemoryArray<Ty> &rhs)
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
template <typename Ty>
bool operator>=(
    const ::pl::RawMemoryArray<Ty> &lhs,
    const ::pl::RawMemoryArray<Ty> &rhs)
{
    return not (lhs < rhs);
}
} // namespace pl
#endif // INCG_PL_RAW_MEMORY_ARRAY_HPP
