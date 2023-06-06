#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

class   Context
{
    public:
        std::pair<std::string, std::string>                     serverAddress;
        std::string                                             serverName;
        std::map<unsigned int, std::string>                     errorPages;
        unsigned int                                            clientMaxBodySize;
        int                                                     socket;
        std::map<std::string, std::map<std::string, Location> > host;


        int         create_socket();
        int         listen();
        int         accept();
        Location    match_location(std::string &uri);

    // public:
};