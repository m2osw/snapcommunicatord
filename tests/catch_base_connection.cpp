// Copyright (c) 2011-2022  Made to Order Software Corp.  All Rights Reserved
//
// https://snapwebsites.org/project/edhttp
// contact@m2osw.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/** \file
 * \brief Verify the snap_uri class.
 *
 * This file implements tests to verify that the snap_uri
 * class functions as expected.
 */

// self
//
#include    "catch_main.h"


// snapcommunicatord
//
#include    <daemon/base_connection.h>



class test_connection
    : public sc::base_connection
{
public:
    test_connection(sc::server::pointer_t s)
        : base_connection(s)
    {
    }
};


CATCH_TEST_CASE("base_connection", "[connection]")
{
    CATCH_SECTION("verify object")
    {
        sc::server::pointer_t s;
        test_connection tc(s);

        // verify defaults
        //
        CATCH_REQUIRE(tc.get_connection_started() == -1);
        CATCH_REQUIRE(tc.get_connection_ended() == -1);
        CATCH_REQUIRE(tc.get_server_name().empty());
    }
}


// vim: ts=4 sw=4 et
