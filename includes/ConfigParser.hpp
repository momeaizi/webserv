#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include "Server.hpp"
#include "Location.hpp"

extern fd_set  readMaster;
extern fd_set  writeMaster;


class ConfigParser
{
    private:
        unsigned int                        lineNumber;
        std::string                         buff;
        std::vector<std::string>            tokens;
        std::ifstream                       configFIle;
        std::set<std::string>               ports;
        std::vector<Server>                 &servers;

        void                                parseConfigFIle();
        int                                 parseServer();
        int                                 parseLocation(Location &location);
        void	                            addServer();

    public:
        ConfigParser(std::vector<Server> &servers);

};


#endif