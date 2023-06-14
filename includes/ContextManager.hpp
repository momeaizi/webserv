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

std::string                 trimString(const std::string &str);
std::vector<std::string>    splitString(const std::string& str, char delimiter);
bool                        containsOnlyWhitespaces(const std::string& str);


class   ContextManager
{
    public:
        unsigned int                        lineNumber;
        std::string                         buff;
        std::vector<std::string>            tokens;
        std::ifstream                       configFIle;
        std::vector<Server>                 servers;
        std::map<std::string, unsigned int> portServer;
        ConfigAttr                          configAttr;


        ContextManager(const char *configFileName);

        void    parseConfigFIle();
        int     parseServer();
        void	addServer();
        int     parseLocation(Location &location);

};



#endif