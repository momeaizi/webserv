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
        std::string                 buff;
        std::vector<std::string>    tokens;
        std::ifstream               configFIle;
        std::vector<Server>         servers;


        ContextManager(const char *configFileName);

        void    parseConfigFIle();
        void    parseLocation(Location &location);

};



#endif