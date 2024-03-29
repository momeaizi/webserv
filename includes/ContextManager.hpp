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
#define DROPCLIENT  fds.erase(client.getClSocket()); \
                    client.drop();\
                    clients.erase(it++);\
                    continue ;\

extern fd_set           readMaster;
extern fd_set           writeMaster;
extern std::set<int>	fds;

class   ContextManager
{
    private:
        char	                            buffer[1024];
        std::vector<Server>                 servers;
        std::list<Client>                   clients;

    public:

        ContextManager();
        void    openAndListen();
        void    ioMultiplexer();
        const std::vector<Server>   &getServers() { return servers; }

};



#endif