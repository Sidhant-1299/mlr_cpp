//
// Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#if !defined(BOOST_WINDOWS)
#include <cstdlib>
#endif

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::getenv;
    using std::system;
#else
    ///
    /// \brief UTF-8 aware getenv. Returns 0 if the variable is not set.
    ///
    /// The string pointed to shall not be modified by the program.
    /// This function is thread-safe as long as no other thread modifies the host environment.
    /// However subsequent calls to this function might overwrite the string pointed to.
    ///
    /// Warning: The returned pointer might only be valid for as long as the calling thread is alive.
    ///          So avoid passing it across thread boundaries.
    ///
    BOOST_NOWIDE_DECL char* getenv(const char* key);

    ///
    /// Same as std::system but cmd is UTF-8.
    ///
    BOOST_NOWIDE_DECL int system(const char* cmd);

#endif
    ///
    /// \brief Set environment variable \a key to \a value
    ///
    /// if overwrite is not 0, that the old value is always overwritten, otherwise,
    /// if the variable exists it remains unchanged
    ///
    /// \a key and \a value are UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int setenv(const char* key, const char* value, int overwrite);

    ///
    /// \brief Remove environment variable \a key
    ///
    /// \a key is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int unsetenv(const char* key);

    ///
    /// \brief Adds or changes an environment variable, \a string must be in format KEY=VALUE
    ///
    /// \a string MAY become part of the environment, hence changes to the value MAY change
    /// the environment. For portability it is hence recommended NOT to change it.
    /// \a string is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int putenv(char* string);

} // namespace nowide
} // namespace boost

#endif
