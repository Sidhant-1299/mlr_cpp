// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2018 Oxford Nanopore Technologies
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MAIN
#define BOOST_TEST_IGNORE_SIGCHLD
#include <boost/test/included/unit_test.hpp>

#include <system_error>
#include <boost/process/v1/filesystem.hpp>

#include <boost/process/v1/cmd.hpp>
#include <boost/process/v1/error.hpp>
#include <boost/process/v1/child.hpp>

namespace bp = boost::process::v1;


BOOST_AUTO_TEST_CASE(implicit_args_fs_path)
{
    using boost::unit_test::framework::master_test_suite;

    boost::process::v1::filesystem::path exe = master_test_suite().argv[1];

    std::error_code ec;
    bp::child c(
        exe,
        ec
    );
    BOOST_REQUIRE(!ec);

    c.wait(ec);
    BOOST_REQUIRE(!ec);

    BOOST_CHECK(c.exit_code() == 1); // should pass at least exe!
}

BOOST_AUTO_TEST_CASE(implicit_args_cmd)
{
    using boost::unit_test::framework::master_test_suite;

    std::error_code ec;
    bp::child c(
        master_test_suite().argv[1],
        ec
    );
    BOOST_REQUIRE(!ec);

    c.wait(ec);
    BOOST_REQUIRE(!ec);

    BOOST_CHECK(c.exit_code() == 1); // should pass at least exe!
}

BOOST_AUTO_TEST_CASE(explicit_args_fs_path)
{
    using boost::unit_test::framework::master_test_suite;

    boost::process::v1::filesystem::path exe = master_test_suite().argv[1];

    std::error_code ec;
    bp::child c(
        exe,
        "hello",
        ec
    );
    BOOST_REQUIRE(!ec);

    c.wait(ec);
    BOOST_REQUIRE(!ec);

    BOOST_CHECK(c.exit_code() == 2); // exe + "hello"
}
