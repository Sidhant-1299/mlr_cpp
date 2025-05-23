//
// address_v4.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Disable autolinking for unit tests.
#if !defined(BOOST_ALL_NO_LIB)
#define BOOST_ALL_NO_LIB 1
#endif // !defined(BOOST_ALL_NO_LIB)

// Test that header file is self-contained.
#include <boost/asio/ip/address_v4.hpp>

#include "../unit_test.hpp"
#include <sstream>

//------------------------------------------------------------------------------

// ip_address_v4_compile test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// ip::address_v4 compile and link correctly. Runtime failures are ignored.

namespace ip_address_v4_compile {

void test()
{
  using namespace boost::asio;
  namespace ip = boost::asio::ip;

  try
  {
    boost::system::error_code ec;

    // address_v4 constructors.

    ip::address_v4 addr1;
    const ip::address_v4::bytes_type const_bytes_value = { { 127, 0, 0, 1 } };
    ip::address_v4 addr2(const_bytes_value);
    const unsigned long const_ulong_value = 0x7F000001;
    ip::address_v4 addr3(const_ulong_value);

    // address_v4 functions.

    bool b = addr1.is_loopback();
    (void)b;

    b = addr1.is_unspecified();
    (void)b;

    b = addr1.is_multicast();
    (void)b;

    ip::address_v4::bytes_type bytes_value = addr1.to_bytes();
    (void)bytes_value;

    ip::address_v4::uint_type uint_value = addr1.to_uint();
    (void)uint_value;

    std::string string_value = addr1.to_string();

    // address_v4 static functions.

    addr1 = ip::address_v4::any();

    addr1 = ip::address_v4::loopback();

    addr1 = ip::address_v4::broadcast();

    // address_v4 comparisons.

    b = (addr1 == addr2);
    (void)b;

    b = (addr1 != addr2);
    (void)b;

    b = (addr1 < addr2);
    (void)b;

    b = (addr1 > addr2);
    (void)b;

    b = (addr1 <= addr2);
    (void)b;

    b = (addr1 >= addr2);
    (void)b;

    // address_v4 creation functions.

    addr1 = ip::make_address_v4(const_bytes_value);
    addr1 = ip::make_address_v4(const_ulong_value);
    addr1 = ip::make_address_v4("127.0.0.1");
    addr1 = ip::make_address_v4("127.0.0.1", ec);
    addr1 = ip::make_address_v4(string_value);
    addr1 = ip::make_address_v4(string_value, ec);
#if defined(BOOST_ASIO_HAS_STRING_VIEW)
# if defined(BOOST_ASIO_HAS_STD_STRING_VIEW)
    std::string_view string_view_value("127.0.0.1");
# elif defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
    std::experimental::string_view string_view_value("127.0.0.1");
# endif // defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
    addr1 = ip::make_address_v4(string_view_value);
    addr1 = ip::make_address_v4(string_view_value, ec);
#endif // defined(BOOST_ASIO_HAS_STRING_VIEW)

    // address_v4 I/O.

    std::ostringstream os;
    os << addr1;

#if !defined(BOOST_NO_STD_WSTREAMBUF)
    std::wostringstream wos;
    wos << addr1;
#endif // !defined(BOOST_NO_STD_WSTREAMBUF)

#if defined(BOOST_ASIO_HAS_STD_HASH)
    std::size_t hash1 = std::hash<ip::address_v4>()(addr1);
    (void)hash1;
#endif // defined(BOOST_ASIO_HAS_STD_HASH)
  }
  catch (std::exception&)
  {
  }
}

} // namespace ip_address_v4_compile

//------------------------------------------------------------------------------

// ip_address_v4_runtime test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that the various public member functions meet the
// necessary postconditions.

namespace ip_address_v4_runtime {

void test()
{
  using boost::asio::ip::address_v4;

  address_v4 a1;
  BOOST_ASIO_CHECK(a1.to_bytes()[0] == 0);
  BOOST_ASIO_CHECK(a1.to_bytes()[1] == 0);
  BOOST_ASIO_CHECK(a1.to_bytes()[2] == 0);
  BOOST_ASIO_CHECK(a1.to_bytes()[3] == 0);
  BOOST_ASIO_CHECK(a1.to_uint() == 0);

  address_v4::bytes_type b1 = {{ 1, 2, 3, 4 }};
  address_v4 a2(b1);
  BOOST_ASIO_CHECK(a2.to_bytes()[0] == 1);
  BOOST_ASIO_CHECK(a2.to_bytes()[1] == 2);
  BOOST_ASIO_CHECK(a2.to_bytes()[2] == 3);
  BOOST_ASIO_CHECK(a2.to_bytes()[3] == 4);
  BOOST_ASIO_CHECK(((a2.to_uint() >> 24) & 0xFF) == b1[0]);
  BOOST_ASIO_CHECK(((a2.to_uint() >> 16) & 0xFF) == b1[1]);
  BOOST_ASIO_CHECK(((a2.to_uint() >> 8) & 0xFF) == b1[2]);
  BOOST_ASIO_CHECK((a2.to_uint() & 0xFF) == b1[3]);

  address_v4 a3(0x01020304);
  BOOST_ASIO_CHECK(a3.to_bytes()[0] == 1);
  BOOST_ASIO_CHECK(a3.to_bytes()[1] == 2);
  BOOST_ASIO_CHECK(a3.to_bytes()[2] == 3);
  BOOST_ASIO_CHECK(a3.to_bytes()[3] == 4);
  BOOST_ASIO_CHECK(a3.to_uint() == 0x01020304);

  BOOST_ASIO_CHECK(address_v4(0x7F000001).is_loopback());
  BOOST_ASIO_CHECK(address_v4(0x7F000002).is_loopback());
  BOOST_ASIO_CHECK(!address_v4(0x00000000).is_loopback());
  BOOST_ASIO_CHECK(!address_v4(0x01020304).is_loopback());

  BOOST_ASIO_CHECK(address_v4(0x00000000).is_unspecified());
  BOOST_ASIO_CHECK(!address_v4(0x7F000001).is_unspecified());
  BOOST_ASIO_CHECK(!address_v4(0x01020304).is_unspecified());

  BOOST_ASIO_CHECK(!address_v4(0x01000000).is_multicast());
  BOOST_ASIO_CHECK(!address_v4(0x7F000000).is_multicast());
  BOOST_ASIO_CHECK(!address_v4(0x80000000).is_multicast());
  BOOST_ASIO_CHECK(!address_v4(0xBFFF0000).is_multicast());
  BOOST_ASIO_CHECK(!address_v4(0xC0000000).is_multicast());
  BOOST_ASIO_CHECK(!address_v4(0xDFFFFF00).is_multicast());
  BOOST_ASIO_CHECK(address_v4(0xE0000000).is_multicast());
  BOOST_ASIO_CHECK(address_v4(0xEFFFFFFF).is_multicast());
  BOOST_ASIO_CHECK(!address_v4(0xF0000000).is_multicast());
  BOOST_ASIO_CHECK(!address_v4(0xFFFFFFFF).is_multicast());

  address_v4 a4 = address_v4::any();
  BOOST_ASIO_CHECK(a4.to_bytes()[0] == 0);
  BOOST_ASIO_CHECK(a4.to_bytes()[1] == 0);
  BOOST_ASIO_CHECK(a4.to_bytes()[2] == 0);
  BOOST_ASIO_CHECK(a4.to_bytes()[3] == 0);
  BOOST_ASIO_CHECK(a4.to_uint() == 0);

  address_v4 a5 = address_v4::loopback();
  BOOST_ASIO_CHECK(a5.to_bytes()[0] == 0x7F);
  BOOST_ASIO_CHECK(a5.to_bytes()[1] == 0);
  BOOST_ASIO_CHECK(a5.to_bytes()[2] == 0);
  BOOST_ASIO_CHECK(a5.to_bytes()[3] == 0x01);
  BOOST_ASIO_CHECK(a5.to_uint() == 0x7F000001);

  address_v4 a6 = address_v4::broadcast();
  BOOST_ASIO_CHECK(a6.to_bytes()[0] == 0xFF);
  BOOST_ASIO_CHECK(a6.to_bytes()[1] == 0xFF);
  BOOST_ASIO_CHECK(a6.to_bytes()[2] == 0xFF);
  BOOST_ASIO_CHECK(a6.to_bytes()[3] == 0xFF);
  BOOST_ASIO_CHECK(a6.to_uint() == 0xFFFFFFFF);
}

} // namespace ip_address_v4_runtime

//------------------------------------------------------------------------------

BOOST_ASIO_TEST_SUITE
(
  "ip/address_v4",
  BOOST_ASIO_COMPILE_TEST_CASE(ip_address_v4_compile::test)
  BOOST_ASIO_TEST_CASE(ip_address_v4_runtime::test)
)
