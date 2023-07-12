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
#include "ConfigParser.hpp"
#include "string.hpp"

#define TIMEOUT 60
#define DROPCLIENT  client.drop();\
                    clients.erase(it++);\
                    continue ;\

extern fd_set  readMaster;
extern fd_set  writeMaster;
extern int     maxFds;

class   ContextManager
{
    public:
        char	                            buffer[1024];
        std::vector<Server>                 servers;
        std::list<Client>                   clients;

        ContextManager();
        void    openAndListen();
        void    ioMultiplexer();

};



#endif