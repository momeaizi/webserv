#ifndef CONTEXTMANAGER_HPP
#define CONTEXTMANAGER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "Server.hpp"
#include "Location.hpp"
#include "ConfigAttr.hpp"
#include "ConfigParser.hpp"
#include "string.hpp"

fd_set  readMaster;
fd_set  writeMaster;
class   ContextManager
{
    public:
        std::vector<Server>                 servers;
        std::list<Client>                   clients;
        fd_set  readMatser;
        fd_set  writeMatser;

        ContextManager();
        void    openAndListen();

};



#endif