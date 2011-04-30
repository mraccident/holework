// main.cpp

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

#include <boost/asio.hpp>
#include <boost/python.hpp>
#include <boost/python/detail/wrap_python.hpp>

#include "events.h"
#include "network/tcpserver.h"  
#include "handlers.h"

void test()
{
    std::cout << "Timer expired!\n";
}

int main()
{
    using namespace boost::asio::ip;
    using namespace boostcraft;
    using namespace boostcraft::network;

    namespace py = boost::python;

    // Whee, Python!
    Py_InitializeEx(0);
    try {
        py::object main_module = py::import("__main__");
        py::object main_namespace = main_module.attr("__dict__");
        py::exec_file("py/test.py", main_namespace);
    }
    catch(py::error_already_set& e)
    {
        PyErr_Print();
    }


    schedule(3000, test);

    listen(loginHandler);
    listen(logHandler);
    listen(lookHandler);
    listen(positionHandler);
    listen(ongroundHandler);

    try
    {
        tcp::endpoint endpoint(tcp::v4(), 25565);
        TcpServer server(io_service(), endpoint);

        io_service().run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
