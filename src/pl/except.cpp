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
