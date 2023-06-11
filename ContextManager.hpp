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


        ContextManager(const char *configFileName);

        void    parseConfigFIle();
        int     parseServer();
        int     parseLocation(Location &location);

};



#endif