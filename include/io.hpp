/*! \file io.hpp
 *  \brief Defines various input/output utilities.
**/

#ifndef INCG_PL_IO_HPP
#define INCG_PL_IO_HPP
#include <ostream>
#include <utility> // std::addressof
namespace pl
{
namespace detail
{
/*!
 * \brief Flushes the stream it was constructed from in its destructor.
 *
 * Type to flush any stream at scope exit.
 * Can be used to flush global io streams like std::cout on application exit
 * by creating a local variable of this type in the main function.
**/
template <typename Stream>
class ScopedStreamFlusher
{
public:
    using this_type = ScopedStreamFlusher;
    using element_type = Stream;

    /*!
     * \brief Creates a ScopedStreamFlusher from any lvalue stream.
     * \param streamToFlush The stream that shall be flushed in the
     *        destructor of this ScopedStreamFlusher.
    **/
    explicit ScopedStreamFlusher(element_type &streamToFlush) noexcept
        : m_streamToFlush{ std::addressof(streamToFlush) }
    {
    }

    /*!
     * \brief Creates a ScopedStreamFlusher from another ScopedStreamFlusher.
     * \param other The other ScopedStreamFlusher to create this one from.
     * \note Both ScopedStreamFlushers will point to the same stream after
     *       this function has been executed. Thus the stream pointed to
     *       will be flushed twice.
    **/
    ScopedStreamFlusher(const this_type &other)
        : m_streamToFlush{ other.m_streamToFlush }
    {
    }

    /*!
     * \brief Creates a ScopedStreamFlusher from another ScopedStreamFlusher.
     * \param other The other ScopedStreamFlusher to create this one from.
    **/
    ScopedStreamFlusher(this_type &&other) noexcept
        : m_streamToFlush{ other.m_streamToFlush }
    {
        other.m_streamToFlush = nullptr;
    }

    /*!
     * \brief Assign this ScopedStreamFlusher with the one passed into the
     *        parameter.
     * \param other The ScopedStreamFlusher to assign to this ScopedStreamFlusher.
     * \return A reference to this ScopedStreamFlusher.
     * \note Both ScopedStreamFlushers will point to the same stream after
     *       this function has been executed. Thus the stream pointed to
     *       will be flushed twice.
     * \warning The stream pointed to by this object will not be flushed anymore
     *          on destruction of this object as the pointer that this object holds
     *          will be replaced with the one stored in the ScopedStreamFlusher
     *          passed into the parameter.
    **/
    this_type &operator=(const this_type &other)
    {
        m_streamToFlush = other.m_streamToFlush;
        return *this;
    }

    this_type &operator=(this_type &&other) noexcept
    {
        m_streamToFlush = other.m_streamToFlush;
        return *this;
    }

    ~ScopedStreamFlusher()
    {
        if (m_streamToFlush != nullptr) {
            (*m_streamToFlush) << std::flush;
        }
    }

private:
    element_type *m_streamToFlush;
};
} // namespace detail

template <typename Stream>
detail::ScopedStreamFlusher<Stream> makeScopedStreamFlusher(Stream &streamToFlush)
{
    return detail::ScopedStreamFlusher<Stream>{ streamToFlush };
}

} // namespace pl
#endif // INCG_PL_IO_HPP
