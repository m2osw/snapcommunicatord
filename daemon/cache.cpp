// Copyright (c) 2011-2022  Made to Order Software Corp.  All Rights Reserved
//
// https://snapwebsites.org/project/communicatord
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
 * \brief Implementation of the cache facility.
 *
 * The Communicator is able to memorize messages it receives when the
 * destination is not yet known. The structure here is used to manage that
 * cache.
 */

// self
//
#include    "cache.h"


// advgetopt
//
#include    <advgetopt/validator_integer.h>


// snaplogger
//
#include    <snaplogger/message.h>


// snapdev
//
#include    <snapdev/tokenize_string.h>


// last include
//
#include    <snapdev/poison.h>



namespace scd
{



/** \brief Cache the specified message.
 *
 * This function caches the specified message.
 *
 * \todo
 * Limit the cache size.
 *
 * \todo
 * Do not cache more than one signal message (i.e. PING, STOP, LOG...)
 * Problem is: how do we know that a message is a signal message?
 *
 * \param[in] msg  The message to save in the cache.
 */
void cache::cache_message(ed::message & msg)
{
    std::string cache_value;
    if(msg.has_parameter("cache"))
    {
        cache_value = msg.get_parameter("cache");
    }

    if(cache_value == "no")
    {
        return;
    }

    // convert `cache` in a map of name/value parameters
    //
    std::list<std::string> cache_parameters;
    snapdev::tokenize_string(cache_parameters, cache_value, { ";" }, true);
    std::map<std::string, std::string> params;
    for(auto const & p : cache_parameters)
    {
        std::string::size_type pos(p.find('='));
        if(pos == std::string::npos)
        {
            params[p] = "true"; // a.k.a. defined
        }
        else if(pos == 0)
        {
            SNAP_LOG_NOTICE
                << "invalid cache parameter \""
                << p
                << "\"; expected \"<name>[=<value>]\"; \"<name>\" is missing, it cannot be empty."
                << SNAP_LOG_SEND;
        }
        else
        {
            params[p.substr(0, pos)] = p.substr(pos + 1);
        }
    }

    // get TTL if defined (1 min. per default)
    //
    std::int64_t ttl(60);
    auto it(params.find("ttl"));
    if(it != params.end())
    {
        std::int64_t value(0);
        if(!advgetopt::validator_integer::convert_string(it->second, value))
        {
            SNAP_LOG_ERROR
                << "cache TTL parameter is not a valid integer ("
                << it->second
                << ")."
                << SNAP_LOG_SEND;
        }
        else if(ttl < 10 || ttl > 86400)
        {
            SNAP_LOG_UNIMPORTANT
                << "cache TTL is out of range ("
                << it->second
                << "); expected a number between 10 and 86400."
                << SNAP_LOG_SEND;
        }
        else
        {
            ttl = value;
        }
    }

    // save the message
    //
    message_cache cache_message;
    cache_message.f_timeout_timestamp = time(nullptr) + ttl;
    cache_message.f_message = msg;
    f_message_cache.push_back(cache_message);

//#ifdef _DEBUG
//    // to make sure we get messages cached as expected
//    //
//    SNAP_LOG_TRACE
//        << "cached command=[" << command
//        << "], server_name=[" << server_name
//        << "], service=[" << service
//        << "], message=[" << msg.to_message()
//        << "], ttl=[" << ttl
//        << "]"
//        << SNAP_LOG_SEND;
//#endif
}


void cache::remove_old_messages()
{
    time_t const now(time(nullptr));
    auto it(f_message_cache.begin());
    while(it != f_message_cache.end())
    {
        if(now > it->f_timeout_timestamp)
        {
            it = f_message_cache.erase(it);
        }
        else
        {
            ++it;
        }
    }
}


void cache::process_messages(std::function<bool(ed::message & msg)> callback)
{
    time_t const now(time(nullptr));
    auto it(f_message_cache.begin());
    while(it != f_message_cache.end())
    {
        if(callback(it->f_message)
        || now > it->f_timeout_timestamp)
        {
            it = f_message_cache.erase(it);
        }
        else
        {
            ++it;
        }
    }
}



} // namespace scd
// vim: ts=4 sw=4 et
