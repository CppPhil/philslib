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
 * \brief Exports the observer_ptr type.
**/
#ifndef INCG_PL_OBSERVER_PTR_HPP
#define INCG_PL_OBSERVER_PTR_HPP
#include "annotations.hpp" // PL_IN_OPT, PL_INOUT, PL_NODISCARD, PL_IMPLICIT
#include "assert.hpp"      // PL_DBG_CHECK_PRE
#include "compiler.hpp"    // PL_COMPILER, PL_COMPILER_MSVC, ...
#include <ciso646>         // not
#include <cstddef>         // std::nullptr_t, std::size_t
#include <functional>      // std::hash
#include <type_traits> // std::enable_if, std::is_convertible, std::add_lvalue_reference
#include <utility> // std::swap

#if PL_COMPILER == PL_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 4814) // in C++14 'constexpr' will not imply 'const';
                                // consider explicitly specifying 'const'
#endif                          // PL_COMPILER == PL_COMPILER_MSVC
namespace pl {
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
 * An observer_ptr may also have no watched object.
 * An observer is not responsible in any way for the watched object;
 * there is no inherent relationship between an observer and the object it
 * watches. It is intended as a near drop-in replacement for raw pointer types,
 * with the advantage that, as a vocabulary type,
 * it indicates its intended use without need for detailed analysis by code
 * readers.
**/
template <typename WatchedType>
class observer_ptr {
public:
    /*!
     * \brief The type of the object watched by this observer_ptr.
    **/
    using element_type = WatchedType;

    /*!
     * \brief Constructs an observer_ptr that has no corresponding watched
     *        object.
    **/
    constexpr observer_ptr() noexcept : observer_ptr{nullptr} {}
    /*!
     * \brief Constructs an observer_ptr that has no corresponding watched
     *        object.
    **/
    PL_IMPLICIT constexpr observer_ptr(std::nullptr_t) noexcept : m_p{nullptr}
    {
    }
    /*!
     * \brief Constructs an observer_ptr that watches p.
     * \param p Pointer to the object to watch.
    **/
    explicit observer_ptr(PL_IN_OPT element_type* p) noexcept : m_p{p} {}
    /*!
     * \brief Constructs an observer_ptr that watches other.get().
     * \note This constructor does not participate in overload resolution
     *       unless WatchedType2 *is convertible to element_type *.
     * \warning Do not replace the second template type parameter!
    **/
    template <typename WatchedType2,
              typename = typename ::std::
                  enable_if<std::is_convertible<WatchedType2*,
                                                element_type*>::value>::type>
    PL_IMPLICIT observer_ptr(observer_ptr<WatchedType2> other) noexcept
        : m_p{other.get()}
    {
    }

    /*!
     * \brief Stop watching the watched object, if any.
     * \note .get() returns nullptr after the call.
     * \return A pointer to the previously watched object,
     *         or nullptr if there was no watched object,
     *         i.e. the value which would be returned by get() before the call.
     * \note Not a constexpr function on msvc15.
    **/
    PL_NODISCARD
#if (PL_COMPILER != PL_COMPILER_MSVC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
    constexpr
#endif
        element_type*
        release() noexcept
    {
        auto* return_value = m_p;
        m_p                = nullptr;

        return return_value;
    }

/*!
 * \brief Set *this to watch the object pointed to by p.
 * \note .get() returns p after the call.
 * \param p Pointer to a new abject to watch.
 * \note Not a constexpr function on msvc15.
**/
#if (PL_COMPILER != PL_COMPILER_MSVC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
    constexpr
#endif
        void
        reset(PL_IN_OPT element_type* p = nullptr) noexcept
    {
        m_p = p;
    }

/*!
 * \brief Swaps the watched object of *this and another observer_ptr.
 * \param other Another observer_ptr boject to swap the watched object with.
 * \note Not a constexpr function on msvc15.
 *
 * Swaps the watched object of *this and another observer_ptr,
 * by invoking swap on the stored pointers of *this and other.
**/
#if (PL_COMPILER != PL_COMPILER_MSVC) \
    || (PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(19, 11, 0))
    constexpr
#endif
        void
        swap(PL_INOUT::pl::observer_ptr<element_type>& other) noexcept
    {
        ::std::swap(m_p, other.m_p);
    }

    /*!
     * \brief Returns a pointer to the watched object
     *        or nullptr if no object is watched.
     * \return Pointer to the watched object or nullptr if no object is watched.
    **/
    PL_NODISCARD constexpr element_type* get() const noexcept { return m_p; }
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
    constexpr typename std::add_lvalue_reference<element_type>::type operator*()
        const
    {
        PL_DBG_CHECK_PRE(this->operator bool());
        return *get();
    }

    /*!
     * \brief Provides access to the object watched by *this.
     * \return Returns a pointer to the object watched by *this, i.e. get().
     * \warning Do not call this function if get() == nullptr.
    **/
    constexpr element_type* operator->() const
    {
        PL_DBG_CHECK_PRE(this->operator bool());
        return get();
    }

    /*!
     * \brief Provides an explicit conversion to the type of the stored pointer.
     * \return A pointer to the watched object, i.e., get().
     */
    constexpr explicit operator element_type*() const noexcept { return get(); }
private:
    element_type* m_p; /*!< The underlying pointer to the watched object. */
};

/*!
 * \brief Creates an observer_ptr object, deducing the template argument
 *        from the type of the function argument.
 * \param p Pointer to the object to be watched by the observer_ptr object.
 * \return An object of type observer_ptr,
 *         created as if by ::pl::observer_ptr<WatchedType>(p).
**/
template <typename WatchedType>
inline observer_ptr<WatchedType> make_observer(
    PL_IN_OPT WatchedType* p) noexcept
{
    return observer_ptr<WatchedType>(p);
}

/*!
 * \brief Compares two observer_ptrs for equality.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return True if the underlying pointers of both arguments compare equal,
 *         otherwise false.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator==(
    PL_IN const observer_ptr<WatchedType1>& p1,
    PL_IN const observer_ptr<WatchedType2>& p2)
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
    PL_IN const observer_ptr<WatchedType1>& p1,
    PL_IN const observer_ptr<WatchedType2>& p2)
{
    return not(p1 == p2);
}

/*!
 * \brief Determines whether the observer_ptr 'p' is a 'null'-Pointer.
 * \param p The observer_ptr to check.
 * \return true if p is a 'null'-Pointer; false otherwise.
**/
template <typename WatchedType>
inline bool operator==(
    PL_IN const observer_ptr<WatchedType>& p,
    std::nullptr_t) noexcept
{
    return p.get() == nullptr;
}

/*!
 * \brief Determines whether the observer_ptr 'p' is a 'null'-Pointer.
 * \param p The observer_ptr to check.
 * \return true if p is a 'null'-Pointer; false otherwise.
**/
template <typename WatchedType>
inline bool operator==(
    std::nullptr_t,
    PL_IN const observer_ptr<WatchedType>& p) noexcept
{
    return ::pl::operator==(p, nullptr);
}

/*!
 * \brief Checks if p watches an object.
 * \param p The observer_ptr to check.
 * \return true if p watches an object; false otherwise.
**/
template <typename WatchedType>
inline bool operator!=(
    PL_IN const observer_ptr<WatchedType>& p,
    std::nullptr_t) noexcept
{
    return static_cast<bool>(p);
}

/*!
 * \brief Checks if p watches an object.
 * \param p The observer_ptr to check.
 * \return true if p watches an object; false otherwise.
**/
template <typename WatchedType>
inline bool operator!=(
    std::nullptr_t,
    PL_IN const observer_ptr<WatchedType>& p) noexcept
{
    return ::pl::operator!=(p, nullptr);
}

/*!
 * \brief Compares the addresses that are held in the internal pointers of the
 *        two observer_ptr passed in using operator<.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if p1's pointer's address is less than p2's pointer's.
 *         false otherwise.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator<(
    PL_IN const observer_ptr<WatchedType1>& p1,
    PL_IN const observer_ptr<WatchedType2>& p2)
{
    return static_cast<const void*>(p1.get())
           < static_cast<const void*>(p2.get());
}

/*!
 * \brief Greater than operator for observer_ptrs.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if p1's pointer's address is greater than p2's pointer's.
 *         false otherwise.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator>(
    PL_IN const observer_ptr<WatchedType1>& p1,
    PL_IN const observer_ptr<WatchedType2>& p2)
{
    return p2 < p1;
}

/*!
 * \brief operator<= for observer_ptrs.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if p1's pointer's address is <= than p2's pointer's.
 *         false otherwise.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator<=(
    PL_IN const observer_ptr<WatchedType1>& p1,
    PL_IN const observer_ptr<WatchedType2>& p2)
{
    return not(p2 < p1);
}

/*!
 * \brief operator>= for observer_ptrs.
 * \param p1 The first argument.
 * \param p2 The second argument.
 * \return true if p1's pointer's address is >= than p2's pointer's,
 *         otherwise false is returned.
**/
template <typename WatchedType1, typename WatchedType2>
inline bool operator>=(
    PL_IN const observer_ptr<WatchedType1>& p1,
    PL_IN const observer_ptr<WatchedType2>& p2)
{
    return not(p1 < p2);
}

/*!
 * \brief Specializes the swap algorithm for ::pl::observer_ptr.
 * \param lhs The first argument.
 * \param rhs The second argument.
 * \note Has constant complexity.
 *
 * Swaps the pointers of lhs and rhs.
 * Calls lhs.swap(rhs).
**/
template <typename WatchedType>
inline void swap(
    PL_INOUT::pl::observer_ptr<WatchedType>& lhs,
    PL_INOUT::pl::observer_ptr<WatchedType>& rhs) noexcept
{
    lhs.swap(rhs);
}
} // namespace pl

namespace std {
/*!
 * \brief The template specialization of std::hash for pl::observer_ptr<Ty>
 *        allows users to obtain hashes of objects of type pl::observer_ptr<Ty>.
 * \note For a given pl::observer_ptr<Ty> p, this specialization ensures that
 *       std::hash<pl::observer_ptr<Ty>>()(p) == std::hash<Ty *>()(p.get()).
**/
template <typename Ty>
struct hash<::pl::observer_ptr<Ty>> {
    std::size_t operator()(
        PL_IN const ::pl::observer_ptr<Ty>& observerPtr) const
    {
        return std::hash<Ty*>{}(observerPtr.get());
    }
};
} // namespace std
#if PL_COMPILER == PL_COMPILER_MSVC
#pragma warning(pop)
#endif // PL_COMPILER == PL_COMPILER_MSVC
#endif // INCG_PL_OBSERVER_PTR_HPP
