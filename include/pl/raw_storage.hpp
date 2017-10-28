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
 * \file raw_storage.hpp
 * \brief Exports the RawStorage type.
**/
#ifndef INCG_PL_RAW_STORAGE_HPP
#define INCG_PL_RAW_STORAGE_HPP
#include "annotations.hpp" // PL_IN
#include <ciso646> // not
#include <cstring> // std::memcpy
#include <new> // ::operator new
#include <memory> // std::addressof
#include <type_traits> // std::is_reference, std::aligned_storage_t

namespace pl
{
/*!
 * \brief Low-level building block that holds raw memory storage large enough
 *        to hold exactly one object of type 'Ty'.
 *        Offers an interface to create and destroy the object of type 'Ty'.
 *        Useful for implementing higher level abstractions like optional.
 * \note Ty may not be a reference type as references are not objects.
**/
template <typename Ty>
class RawStorage
{
public:
    using this_type = RawStorage;
    using element_type = Ty;

    static_assert(not std::is_reference<element_type>::value,
                  "Ty in pl::RawStorage may not be a reference.");

    /*!
     * \brief The default constructor. Does nothing.
     *        The underlying storage is left in an unintialized state.
     * \note Leaves the underlying storage in the destroyed state.
    **/
    RawStorage() noexcept
        : m_data{ }
    {
    }

    /*!
     * \brief this type is noncopyable.
     * \note A type containing this type should if copy semantics are desired
     *       implement them by using the member functions of this type.
    **/
    RawStorage(const this_type &) = delete;

    /*!
     * \brief this type is noncopyable.
     * \note A type containing this type should if copy semantics are desired
     *       implement them by using the member functions of this type.
    **/
    this_type &operator=(const this_type &) = delete;

    /*!
     * \brief this type is nonmovable.
     * \note A type containing this type should if move semantics are desired
     *       implement them by using the member functions of this type.
    **/
    RawStorage(this_type &&) = delete;

    /*!
     * \brief this type is nonmovable.
     * \note A type containing this type should if move semantics are desired
     *       implement them by using the member functions of this type.
    **/
    this_type &operator=(this_type &&) = delete;

    /*!
     * \brief Reinterprets the underlying storage as 'Ty'.
     * \return A reference to the object in the underlying storage.
     * \warning Undefined behavior if the underlying storage is in the
     *          destroyed state.
    **/
    element_type &get() noexcept
    {
        auto p1 = &m_data;
        element_type *p2{ nullptr };

        static_assert(sizeof(decltype(p1)) == sizeof(element_type *),
                      "Pointers were not of equal size in pl::RawStorage::get");

        std::memcpy(&p2, &p1, sizeof(p1));

        return *p2;
    }

    /*!
     * \brief Behaves like the non-const overload, except for it returning a
     *        const reference.
     * \return A const reference to the object in the underlying storage.
    **/
    const element_type &get() const noexcept
    {
        return const_cast<this_type *>(this)->get();
    }

    /*!
     * \brief Constructs an object of type Ty into the raw storage.
     * \param args The arguments to pass to the constructor of Ty.
     * \return A reference to the newly created Ty.
     * \note Uses the classic parentheses syntax to call the constructor.
     *       Leaves the underlying storage in the constructed state.
     * \warning May only be called if the underlying storage is in the destroyed
     *          state.
    **/
    template <typename ...Args>
    element_type &constructParentheses(PL_IN Args &&...args)
    {
        return *::new(static_cast<void *>(std::addressof(m_data))) element_type(std::forward<Args>(args) ...);
    }

    /*!
     * \brief Constructs an object of type Ty into the raw storage.
     * \param args The arguments to pass to the constructor of Ty.
     * \return A reference to the newly created Ty.
     * \note Uses the uniform initialization syntax to call the constructor.
     *       Leaves the underlying storage in the constructed state.
     * \warning May only be called if the underlying storage is in the destroyed
     *          state.
    **/
    template <typename ...Args>
    element_type &construct(PL_IN Args &&...args)
    {
        return *::new(static_cast<void *>(std::addressof(m_data))) element_type{ std::forward<Args>(args) ... };
    }

    /*!
     * \brief Calls the destructor of the object in the underlying storage.
     * \note Leaves the underlying storage in the destroyed state.
     * \warning May only be called if the underlying storage is in the
     *          constructed state.
    **/
    void destroy() noexcept
    {
        get().~element_type();
    }

private:
    std::aligned_storage_t<sizeof(element_type), alignof(element_type)> m_data; /*!< The underlying storage */
};
} // namespace pl
#endif // INCG_PL_RAW_STORAGE_HPP
