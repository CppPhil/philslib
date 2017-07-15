#include "../../include/pl/except.hpp"
#include "../../include/pl/annotations.hpp" // PL_IN
#include <exception> // std::exception
#include <stdexcept> // std::logic_error, std::runtime_error
#include <system_error> // std::error_code
#include <future> // std::future_error
#include <memory> // std::bad_weak_ptr
#include <typeinfo> // std::bad_typeid
#include <iostream> // std::cerr

namespace pl
{
AssertionViolationException::AssertionViolationException(const std::string &what_arg)
    : base_type{ what_arg }
{
}

AssertionViolationException::AssertionViolationException(const char *what_arg)
    : base_type{ what_arg }
{
}

const char *AssertionViolationException::what() const noexcept
{
    return base_type::what();
}

PreconditionViolationException::PreconditionViolationException(const std::string &what_arg)
    : base_type{ what_arg }
{
}

PreconditionViolationException::PreconditionViolationException(const char *what_arg)
    : base_type{ what_arg }
{
}

const char *PreconditionViolationException::what() const noexcept
{
    return base_type::what();
}

PostconditionViolationException::PostconditionViolationException(const std::string &what_arg)
    : base_type{ what_arg }
{
}

PostconditionViolationException::PostconditionViolationException(const char *what_arg)
    : base_type{ what_arg }
{
}

const char *PostconditionViolationException::what() const noexcept
{
    return base_type::what();
}

NullPointerException::NullPointerException(const std::string &what_arg)
    : base_type{ what_arg }
{
}

NullPointerException::NullPointerException(const char *what_arg)
    : base_type{ what_arg }
{
}

const char *NullPointerException::what() const noexcept
{
    return base_type::what();
}

NotYetImplementedException::NotYetImplementedException(const std::string &what_arg)
    : base_type{ what_arg }
{
}

NotYetImplementedException::NotYetImplementedException(const char *what_arg)
    : base_type{ what_arg }
{
}

const char *NotYetImplementedException::what() const noexcept
{
    return base_type::what();
}

namespace detail
{
/*!
 * \brief Prints the information from an exception's error code.
 * \param e An exception that has an error code of which the associated
 *        information shall be printed.
**/
template <typename Ty>
inline void handleCodeException(PL_IN const Ty &e)
{
#if !((PL_COMPILER == PL_COMPILER_GCC) && (PL_COMPILER_VERSION < PL_COMPILER_VERSION_CHECK(6, 3, 0)))
    auto code = e.code();

    std::cerr << "- category:     " << code.category().name() << '\n'
              << "- value:        " << code.value() << '\n'
              << "- msg:          " << code.message() << '\n'
              << "- def category: " << code.default_error_condition().category().name() << '\n'
              << "- def value:    " << code.default_error_condition().value() << '\n'
              << "- def msg:      " << code.default_error_condition().message() << std::endl;
#endif
}
} // namespace detail

void handleExceptions()
{
    static constexpr char functionName[] = "pl::handleExceptions";

    try {
        throw;
    } catch (const std::bad_array_new_length &e) {
        std::cerr << functionName
                  << " caught std::bad_array_new_length exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_alloc &e) {
        std::cerr << functionName
                  << " caught std::bad_alloc exception:\n"
                  << e.what() << '\n';
    } catch (const std::ios_base::failure &e) {
        std::cerr << functionName
                  << " caught std::bad_ios_base::failure exception:\n"
                  << e.what() << '\n';
        detail::handleCodeException(e);
    } catch (const std::system_error &e) {
        std::cerr << functionName
                  << " caught std::system_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::out_of_range &e) {
        std::cerr << functionName
                  << " caught std::out_of_range exception:\n"
                  << e.what() << '\n';
    } catch (const std::length_error &e) {
        std::cerr << functionName
                  << " caught std::length_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::invalid_argument &e) {
        std::cerr << functionName
                  << " caught std::invalid_argument exception:\n"
                  << e.what() << '\n';
    } catch (const std::future_error &e) {
        std::cerr << functionName
                  << " caught std::future_error exception:\n"
                  << e.what() << '\n';
        detail::handleCodeException(e);
    } catch (const std::domain_error &e) {
        std::cerr << functionName
                  << " caught std::domain_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::logic_error &e) {
        std::cerr << functionName
                  << " caught std::logic_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::overflow_error &e) {
        std::cerr << functionName
                  << " caught std::overflow_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::underflow_error &e) {
        std::cerr << functionName
                  << " caught std::underflow_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::range_error &e) {
        std::cerr << functionName
                  << " caught std::range_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::runtime_error &e) {
        std::cerr << functionName
                  << " caught std::runtime_error exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_weak_ptr &e) {
        std::cerr << functionName
                  << " caught std::bad_weak_ptr exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_typeid &e) {
        std::cerr << functionName
                  << " caught std::bad_typeid exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_exception &e) {
        std::cerr << functionName
                  << " caught std::bad_exception exception:\n"
                  << e.what() << '\n';
    } catch (const std::bad_cast &e) {
        std::cerr << functionName
                  << " caught std::bad_cast exception:\n"
                  << e.what() << '\n';
    } catch (const std::exception &e) {
        std::cerr << functionName
                  << " caught std::exception exception:\n"
                  << e.what() << '\n';
    } catch (...) {
        std::cerr << functionName
                  << " caught unknown exception!\n";
    }
}
} // namespace pl
