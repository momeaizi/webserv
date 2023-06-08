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
        long                                                    clientMaxBodySize;
        std::set<std::string>                                   allowedMethods;
        std::pair<int, std::string>                             redirection;
        std::map<std::string, Location>                         locations;


        int         create_socket();
        int         listen();
        int         accept();
        Location    match_location(std::string &uri);

};