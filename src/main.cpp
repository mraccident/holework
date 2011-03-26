// server.cpp

/***********************************************************************
* Copyright (C) 2011 Holework Project
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
* 
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*************************************************************************/

#include <iostream>
#include <string>
#include <vector>

#include <boost/asio.hpp>

#include "events.h"
#include "network/tcpserver.h"

using namespace boostcraft;

/*
 * Log event handler
 */
void logMessage(LogEvent& event)
{
    std::cout << "LOGGED: " << event.source_name << " "  << event.message << "\n";
    // Now we sneakily cancel the event!
//    event.canceled = true;
}


void handler2(LogEvent& event)
{
    std::cout << "This is the second handler!\n";
}



int main()
{
    using namespace boost::asio::ip;
    using namespace boostcraft::network;

    boostcraft::listen<LogEvent>(logMessage);
    boostcraft::listen<LogEvent>(handler2);


    LogEvent event("THIS IS A TEST");
    LogEvent::signal(event);

    try
    {
        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), 25565);
        TcpServer server(io_service, endpoint);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
