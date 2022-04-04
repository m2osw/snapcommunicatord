// Copyright (c) 2011-2022  Made to Order Software Corp.  All Rights Reserved
//
// https://snapwebsites.org/project/snapcommunicator
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
#pragma once

/** \file
 * \brief Exceptions.
 *
 * The following are all the exceptions used by the Snap Communicator.
 */


// libexcept
//
#include    "libexcept/exception.h"



namespace sc
{



DECLARE_LOGIC_ERROR(snapcommunicator_logic_error);

DECLARE_MAIN_EXCEPTION(snapcommunicator_error);

DECLARE_EXCEPTION(snapcommunicator_error, address_missing);
DECLARE_EXCEPTION(snapcommunicator_error, connection_unavailable);
DECLARE_EXCEPTION(snapcommunicator_error, unexpected_message);
DECLARE_EXCEPTION(snapcommunicator_error, unexpected_message_parameter);
DECLARE_EXCEPTION(snapcommunicator_error, unknown_command);
DECLARE_EXCEPTION(snapcommunicator_error, unknown_exception);
DECLARE_EXCEPTION(snapcommunicator_error, switching_to_user_failed);
DECLARE_EXCEPTION(snapcommunicator_error, user_missing);



} // namespace sc
// vim: ts=4 sw=4 et
