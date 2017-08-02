#ifndef INCG_PL_ObserverPtr_HPP
#define INCG_PL_ObserverPtr_HPP
#include <ciso646> // not
#include <cstddef> // std::nullptr_t, std::size_t
#include <utility> // std::swap
#include <functional> // std::hash
#include <type_traits> // std::enable_if_t, std::is_convertible, std::add_lvalue_reference_t

namespace pl
{
template <typename WatchedType>
class ObserverPtr
{
public:
    using element_type = WatchedType;

    constexpr ObserverPtr() noexcept
        : m_p{ nullptr }
    {

    }

    constexpr ObserverPtr(std::nullptr_t) noexcept
        : ObserverPtr{ }
    {

    }

    explicit ObserverPtr(element_type *p) noexcept
        : m_p{ p }
    {
    }

    template <typename WatchedType2,
              typename = std::enable_if_t<std::is_convertible<WatchedType2 *, element_type *>::value>>
    ObserverPtr(ObserverPtr<WatchedType2> other) noexcept
        : m_p{ other.get() }
    {

    }

    constexpr element_type *release() noexcept
    {
        auto *returnValue = m_p;
        m_p = nullptr;

        return returnValue;
    }

    constexpr void reset(element_type *p = nullptr) noexcept
    {
        m_p = p;
    }

    constexpr void swap(ObserverPtr &other) noexcept
    {
        std::swap(m_p, other.m_p);
    }

    constexpr element_type *get() const noexcept
    {
        return m_p;
    }

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr std::add_lvalue_reference_t<element_type> operator*() const
    {
        return *get();
    }

    constexpr element_type *operator->() const noexcept
    {
        return get();
    }

    constexpr explicit operator element_type *() const noexcept
    {
        return get();
    }

private:
    element_type *m_p;
};


template <typename WatchedType>
inline ObserverPtr<WatchedType> makeObserver(WatchedType *p) noexcept
{
    return ObserverPtr<WatchedType>(p);
}

template <typename WatchedType1, typename WatchedType2>
inline bool operator==(const ObserverPtr<WatchedType1> &p1, const ObserverPtr<WatchedType2> &p2)
{
    return p1.get() == p2.get();
}

template <typename WatchedType1, typename WatchedType2>
inline bool operator!=(const ObserverPtr<WatchedType1> &p1, const ObserverPtr<WatchedType2> &p2)
{
    return not (p1 == p2);
}

template <typename WatchedType>
inline bool operator==(const ObserverPtr<WatchedType> &p, std::nullptr_t) noexcept
{
    return p.get() == nullptr;
}

template <typename WatchedType>
inline bool operator==(std::nullptr_t, const ObserverPtr<WatchedType> &p) noexcept
{
    return ::pl::operator==(p, nullptr);
}

template <typename WatchedType>
inline bool operator!=(const ObserverPtr<WatchedType> &p, std::nullptr_t) noexcept
{
    return static_cast<bool>(p);
}

template <typename WatchedType>
inline bool operator!=(std::nullptr_t, const ObserverPtr<WatchedType> &p) noexcept
{
    return ::pl::operator!=(p, nullptr);
}

template <typename WatchedType1, typename WatchedType2>
inline bool operator<(const ObserverPtr<WatchedType1> &p1, const ObserverPtr<WatchedType2> &p2)
{
    return static_cast<const void *>(p1.get()) < static_cast<const void *>(p2.get());
}

template <typename WatchedType1, typename WatchedType2>
inline bool operator>(const ObserverPtr<WatchedType1> &p1, const ObserverPtr<WatchedType2> &p2)
{
    return p2 < p1;
}

template <typename WatchedType1, typename WatchedType2>
inline bool operator<=(const ObserverPtr<WatchedType1> &p1, const ObserverPtr<WatchedType2> &p2)
{
    return not (p2 < p1);
}

template <typename WatchedType1, typename WatchedType2>
inline bool operator>=(const ObserverPtr<WatchedType1> &p1, const ObserverPtr<WatchedType2> &p2)
{
    return not (p1 < p2);
}

template <typename WatchedType>
inline void swap(ObserverPtr<WatchedType> &lhs, ObserverPtr<WatchedType> &rhs) noexcept
{
    lhs.swap(rhs);
}
} // namespace pl

namespace std
{
template <typename Ty>
struct hash<::pl::ObserverPtr<Ty>>
{
    std::size_t operator()(const ::pl::ObserverPtr<Ty> &observerPtr) const
    {
        return std::hash<Ty *>{ }(observerPtr.get());
    }
};
} // namespace std
#endif // INCG_PL_ObserverPtr_HPP
