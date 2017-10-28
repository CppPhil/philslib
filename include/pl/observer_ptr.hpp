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
 * \file observer_ptr.hpp
 * \brief Exports the ObserverPtr type.
**/
#ifndef INCG_PL_OBSERVER_PTR_HPP
#define INCG_PL_OBSERVER_PTR_HPP
#include "annotations.hpp" // PL_IN_OPT, PL_INOUT, PL_NODISCARD
#include "assert.hpp" // PL_DBG_CHECK_PRE
#include <ciso646> // not
#include <cstddef> // std::nullptr_t, std::size_t
#include <utility> // std::swap
#include <functional> // std::hash
#include <type_traits> // std::enable_if_t, std::is_convertible, std::add_lvalue_reference_t

namespace pl
{
/*!
 * \brief A non-owning pointer.
 * \warning The template type parameter may not be a reference type,
 *          but it may be an incomplete type.
 * \note The copy-constructor, move-constructor, copy-assignment operator,
 *       move-assignment operator and destructor are implicitly declared.
 *
 * A non-owning pointer or observer.
 * The observer stores a pointer to a second object,
 * known as the watched object.
 * An ObserverPtr may also have no watched object.
 * An observer is not responsible in any way for the watched object;
 * there is no inherent relationship between an observer and the object it watches.
 * It is intended as a near drop-in replacement for raw pointer types,
 * with the advantage that, as a vocabulary type,
 * it indicates its intended use without need for detailed analysis by code readers.
**/
template <typename WatchedType>
class ObserverPtr
{
public:
    /*!
     * \brief The type of the object watched by this ObserverPtr.
    **/
    using element_type = WatchedType;

    /*!
     * \brief Constructs an ObserverPtr that has no corresponding watched object.
    **/
    constexpr ObserverPtr() noexcept
        : ObserverPtr{ nullptr }
    {
    }

    /*!
     * \brief Constructs an ObserverPtr that has no corresponding watched object.
    **/
    constexpr ObserverPtr(std::nullptr_t) noexcept
        : m_p{ nullptr }
    {
    }

    /*!
     * \brief Constructs an ObserverPtr that watches p.
     * \param p Pointer to the object to watch.
    **/
    explicit ObserverPtr(PL_IN_OPT element_type *p) noexcept
        : m_p{ p }
    {
    }

    /*!
     * \brief Constructs an ObserverPtr that watches other.get().
     * \note This constructor does not participate in overload resolution
     *       unless WatchedType2 *is convertible to element_type *.
     * \warning Do not replace the second template type parameter!
    **/
    template <typename WatchedType2,
              typename = std::enable_if_t<std::is_convertible<WatchedType2 *, element_type *>::value>>
    ObserverPtr(ObserverPtr<WatchedType2> other) noexcept
        : m_p{ other.get() }
    {
    }

    /*!
     * \brief Stop watching the watched object, if any.
     * \note .get() returns nullptr after the call.
     * \return A pointer to the previously watched object,
     *         or nullptr if there was no watched object,
     *         i.e. the value which would be returned by get() before the call.
    **/
    PL_NODISCARD constexpr element_type *release() noexcept
    {
        auto *returnValue = m_p;
        m_p = nullptr;

        return returnValue;
    }

    /*!
     * \brief Set *this to watch the object pointed to by p.
     * \note .get() returns p after the call.
     * \param p Pointer to a new abject to watch.
    **/
    constexpr void reset(PL_IN_OPT element_type *p = nullptr) noexcept
    {
        m_p = p;
    }

    /*!
     * \brief Swaps the watched object of *this and another ObserverPtr.
     * \param other Another ObserverPtr boject to swap the watched object with.
     *
     * Swaps the watched object of *this and another ObserverPtr,
     * by invoking swap on the stored pointers of *this and other.
    **/
    constexpr void swap(PL_INOUT ObserverPtr &other) noexcept
    {
        std::swap(m_p, other.m_p);
    }

    /*!
     * \brief Returns a pointer to the watched object
     *        or nullptr if no object is watched.
     * \return Pointer to the watched object or nullptr if no object is watched.
    **/
    PL_NODISCARD constexpr element_type *get() const noexcept
    {
        return m_p;
    }

    /*!
     * \brief Checks whether *this has an associated watched object.
     * \return true if *this has an associated watched object, false otherwise.
     *
     * Checks whether *this has an associated watched object,
     * i.e. whether get() != nullptr.
    **/
    PL_NODISCARD constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    /*!
     * \brief Provides access to the object watched by *this.
     * \return Returns the object watched by *this, equivalent to *get().
     * \warning The behavior is undefined if get() == nullptr.
    **/
    constexpr std::add_lvalue_reference_t<element_type> operator*() const
    {
        PL_DBG_CHECK_PRE(this->operator bool());
        return *get();
    }

    /*!
     * \brief Provides access to the object watched by *this.
     * \return Returns a pointer to the object watched by *this, i.e. get().
     * \warning Do not call this function if get() == nullptr.
    **/
    constexpr element_type *operator->() const
    {
        PL_DBG_CHECK_PRE(this->operator bool());
        return get();
    }

    /*!
     * \brief Provides an explicit conversion to the type of the stored pointer.
     * \return A pointer to the watched object, i.e., get().
     */
    constexpr explicit operator element_type *() const noexcept
    {
        return get();
    }

private:
    element_type *m_p; /*!< The underlying pointer to the watched object. */
};

/*!
 * \brief Creates an ObserverPtr object, deducing the template argument
 *        from the type of the function argument.
 * \param p Pointer to the object to be watched by the ObserverPtr object.
 * \return An object of type ObserverPtr,
 *         created as if by ::pl::ObserverPtr<WatchedType>(p).
**/
template <typename WatchedType>
inline ObserverPtr<WatchedType> makeObserver(PL_IN_OPT WatchedType *p) noexcept
{
    return ObserverPtr<WatchedType>(p);
}

/*!
 * \brief Compares two ObserverPtrs for equality.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return True if the underlying pointers of both arguments compare equal,
 *         otherwise false.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator==(
    PL_IN const ObserverPtr<WatchedType1> &p1,
    PL_IN const ObserverPtr<WatchedType2> &p2)
{
    return p1.get() == p2.get();
}

/*!
 * \brief The negation of operator==.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if the arguments do not compare equal.
 *         false if the arguments compare equal.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator!=(
    PL_IN const ObserverPtr<WatchedType1> &p1,
    PL_IN const ObserverPtr<WatchedType2> &p2)
{
    return not (p1 == p2);
}

/*!
 * \brief Determines whether the ObserverPtr 'p' is a 'null'-Pointer.
 * \param p The ObserverPtr to check.
 * \return true if p is a 'null'-Pointer; false otherwise.
**/
template <typename WatchedType>
inline bool operator==(PL_IN const ObserverPtr<WatchedType> &p, std::nullptr_t) noexcept
{
    return p.get() == nullptr;
}

/*!
 * \brief Determines whether the ObserverPtr 'p' is a 'null'-Pointer.
 * \param p The ObserverPtr to check.
 * \return true if p is a 'null'-Pointer; false otherwise.
**/
template <typename WatchedType>
inline bool operator==(std::nullptr_t, PL_IN const ObserverPtr<WatchedType> &p) noexcept
{
    return ::pl::operator==(p, nullptr);
}

/*!
 * \brief Checks if p watches an object.
 * \param p The ObserverPtr to check.
 * \return true if p watches an object; false otherwise.
**/
template <typename WatchedType>
inline bool operator!=(PL_IN const ObserverPtr<WatchedType> &p, std::nullptr_t) noexcept
{
    return static_cast<bool>(p);
}

/*!
 * \brief Checks if p watches an object.
 * \param p The ObserverPtr to check.
 * \return true if p watches an object; false otherwise.
**/
template <typename WatchedType>
inline bool operator!=(std::nullptr_t, PL_IN const ObserverPtr<WatchedType> &p) noexcept
{
    return ::pl::operator!=(p, nullptr);
}

/*!
 * \brief Compares the addresses that are held in the internal pointers of the
 *        two ObserverPtrs passed in using operator<.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if p1's pointer's address is less than p2's pointer's.
 *         false otherwise.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator<(
    PL_IN const ObserverPtr<WatchedType1> &p1,
    PL_IN const ObserverPtr<WatchedType2> &p2)
{
    return static_cast<const void *>(p1.get()) < static_cast<const void *>(p2.get());
}

/*!
 * \brief Greater than operator for ObserverPtrs.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if p1's pointer's address is greater than p2's pointer's.
 *         false otherwise.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator>(
    PL_IN const ObserverPtr<WatchedType1> &p1,
    PL_IN const ObserverPtr<WatchedType2> &p2)
{
    return p2 < p1;
}

/*!
 * \brief operator<= for ObserverPtrs.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if p1's pointer's address is <= than p2's pointer's.
 *         false otherwise.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator<=(
    PL_IN const ObserverPtr<WatchedType1> &p1,
    PL_IN const ObserverPtr<WatchedType2> &p2)
{
    return not (p2 < p1);
}

/*!
 * \brief operator>= for ObserverPtrs.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if p1's pointer's address is >= than p2's pointer's,
 *         otherwise false is returned.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator>=(
    PL_IN const ObserverPtr<WatchedType1> &p1,
    PL_IN const ObserverPtr<WatchedType2> &p2)
{
    return not (p1 < p2);
}

/*!
 * \brief Specializes the swap algorithm for ::pl::ObserverPtr.
 * \param lhs The first argument.
 * \param rhs The second argument.
 * \note Has constant complexity.
 *
 * Swaps the pointers of lhs and rhs.
 * Calls lhs.swap(rhs).
**/
template <typename WatchedType>
inline void swap(
    PL_INOUT ObserverPtr<WatchedType> &lhs,
    PL_INOUT ObserverPtr<WatchedType> &rhs) noexcept
{
    lhs.swap(rhs);
}
} // namespace pl

namespace std
{
/*!
 * \brief The template specialization of std::hash for pl::ObserverPtr<Ty>
 *        allows users to obtain hashes of objects of type pl::ObserverPtr<Ty>.
 * \note For a given pl::ObserverPtr<Ty> p, this specialization ensures that
 *       std::hash<pl::ObserverPtr<Ty>>()(p) == std::hash<Ty *>()(p.get()).
**/
template <typename Ty>
struct hash<::pl::ObserverPtr<Ty>>
{
    std::size_t operator()(PL_IN const ::pl::ObserverPtr<Ty> &observerPtr) const
    {
        return std::hash<Ty *>{ }(observerPtr.get());
    }
};
} // namespace std
#endif // INCG_PL_OBSERVER_PTR_HPP
