#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP


#include "ConfigAttr.hpp"
#include "Server.hpp"
#include "Location.hpp"

class ConfigParser
{
    private:
        unsigned int                        lineNumber;
        std::string                         buff;
        std::vector<std::string>            tokens;
        std::ifstream                       configFIle;
        std::map<std::string, unsigned int> portServer;
        ConfigAttr                          configAttr;
        std::vector<Server>                 &servers;

        void                                parseConfigFIle();
        int                                 parseServer();
        int                                 parseLocation(Location &location);
        void	                            addServer();

    public:
        ConfigParser(std::vector<Server> &servers);

};


#endif