#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Location.hpp"

class   Server
{
    public:
        int                                                     socket;
        std::string                                             host;
        std::string                                             port;
        std::map<int, std::string>                              errorPages;
        unsigned int                                            clientMaxBodySize;
        std::map<std::string, std::map<std::string, Location> > host_loc;
        std::set<std::string>                                   allowedMethods;
        std::pair<int, std::string>                             redirection;


        int         create_socket();
        int         listen();
        int         accept();
        Location    match_location(std::string &uri);

};