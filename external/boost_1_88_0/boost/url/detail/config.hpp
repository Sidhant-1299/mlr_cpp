//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2022 Alan de Freitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//

#ifndef BOOST_URL_DETAIL_CONFIG_HPP
#define BOOST_URL_DETAIL_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <limits.h>
#include <stdint.h>

#if CHAR_BIT != 8
# error unsupported platform
#endif

// Determine if compiling as a dynamic library
#if (defined(BOOST_URL_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_URL_STATIC_LINK)
#    define BOOST_URL_BUILD_DLL
#endif

// Set visibility flags
#if !defined(BOOST_URL_BUILD_DLL)
#    define BOOST_URL_DECL /* static library */
#elif defined(BOOST_URL_SOURCE)
#    define BOOST_URL_DECL BOOST_SYMBOL_EXPORT /* source: dllexport/visibility */
#else
#    define BOOST_URL_DECL BOOST_SYMBOL_IMPORT /* header: dllimport */
#endif

// Set up auto-linker
# if !defined(BOOST_URL_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_URL_NO_LIB)
#  define BOOST_LIB_NAME boost_url
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_URL_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
# endif

// Set up SSE2
#if ! defined(BOOST_URL_NO_SSE2) && \
    ! defined(BOOST_URL_USE_SSE2)
# if (defined(_M_IX86) && _M_IX86_FP == 2) || \
      defined(_M_X64) || defined(__SSE2__)
#  define BOOST_URL_USE_SSE2
# endif
#endif

// constexpr
#if BOOST_WORKAROUND( BOOST_GCC_VERSION, <= 72000 ) || \
    BOOST_WORKAROUND( BOOST_CLANG_VERSION, <= 35000 )
# define BOOST_URL_CONSTEXPR
#else
# define BOOST_URL_CONSTEXPR constexpr
#endif

// Add source location to error codes
#ifdef BOOST_URL_NO_SOURCE_LOCATION
# define BOOST_URL_ERR(ev) (::boost::system::error_code(ev))
# define BOOST_URL_RETURN_EC(ev) return (ev)
# define BOOST_URL_POS ::boost::source_location()
#else
# define BOOST_URL_ERR(ev) (::boost::system::error_code( (ev), [] { \
         static constexpr auto loc((BOOST_CURRENT_LOCATION)); \
         return &loc; }()))
# define BOOST_URL_RETURN_EC(ev) \
    static constexpr auto loc ## __LINE__((BOOST_CURRENT_LOCATION)); \
    return ::boost::system::error_code((ev), &loc ## __LINE__)
# define BOOST_URL_POS (BOOST_CURRENT_LOCATION)
#endif

#if !defined(BOOST_NO_CXX20_HDR_CONCEPTS) && defined(__cpp_lib_concepts)
#define BOOST_URL_HAS_CONCEPTS
#endif

#ifdef  BOOST_URL_HAS_CONCEPTS
#define BOOST_URL_CONSTRAINT(C) C
#else
#define BOOST_URL_CONSTRAINT(C) class
#endif

// String token parameters
#ifndef BOOST_URL_STRTOK_TPARAM
#define BOOST_URL_STRTOK_TPARAM BOOST_URL_CONSTRAINT(string_token::StringToken) StringToken = string_token::return_string
#endif
#ifndef BOOST_URL_STRTOK_RETURN
#define BOOST_URL_STRTOK_RETURN typename StringToken::result_type
#endif
#ifndef BOOST_URL_STRTOK_ARG
#define BOOST_URL_STRTOK_ARG(name) StringToken&& token = {}
#endif

// Move
#if BOOST_WORKAROUND( BOOST_GCC_VERSION, < 80000 ) || \
    BOOST_WORKAROUND( BOOST_CLANG_VERSION, < 30900 )
#define BOOST_URL_RETURN(x) return std::move((x))
#else
#define BOOST_URL_RETURN(x) return (x)
#endif

// Limit tests
#ifndef BOOST_URL_MAX_SIZE
// we leave room for a null,
// and still fit in size_t
#define BOOST_URL_MAX_SIZE ((std::size_t(-1))-1)
#endif

// noinline attribute
#ifdef BOOST_GCC
#define BOOST_URL_NO_INLINE [[gnu::noinline]]
#else
#define BOOST_URL_NO_INLINE
#endif

// libstdcxx copy-on-write strings
#ifndef BOOST_URL_COW_STRINGS
#if defined(BOOST_LIBSTDCXX_VERSION) && (BOOST_LIBSTDCXX_VERSION < 60000 || (defined(_GLIBCXX_USE_CXX11_ABI) && _GLIBCXX_USE_CXX11_ABI == 0))
#define BOOST_URL_COW_STRINGS
#endif
#endif

// detect 32/64 bit
#if UINTPTR_MAX == UINT64_MAX
# define BOOST_URL_ARCH 64
#elif UINTPTR_MAX == UINT32_MAX
# define BOOST_URL_ARCH 32
#else
# error Unknown or unsupported architecture, please open an issue
#endif

// deprecated attribute
#if defined(BOOST_MSVC) || defined(BOOST_URL_DOCS)
#define BOOST_URL_DEPRECATED(msg)
#else
#define BOOST_URL_DEPRECATED(msg) BOOST_DEPRECATED(msg)
#endif

// Implementation defined type for Doxygen while Clang
// can still parse the comments into the AST
#ifndef BOOST_URL_DOCS
#define BOOST_URL_IMPLEMENTATION_DEFINED(Type) Type
#else
#define BOOST_URL_IMPLEMENTATION_DEFINED(Type) __implementation_defined__
#endif

#ifndef BOOST_URL_DOCS
#define BOOST_URL_SEE_BELOW(Type) Type
#else
#define BOOST_URL_SEE_BELOW(Type) __see_below__
#endif

#ifdef __cpp_lib_array_constexpr
#define BOOST_URL_LIB_ARRAY_CONSTEXPR constexpr
#else
#define BOOST_URL_LIB_ARRAY_CONSTEXPR
#endif

// avoid Boost.TypeTraits for these traits
namespace boost {
namespace urls {

template<class...> struct make_void { typedef void type; };
template<class... Ts> using void_t = typename make_void<Ts...>::type;

} // urls
} // boost

#endif
