#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <ctype.h>


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Location.hpp"


fd_set          master;
int             max_socket = 0;

class   Server
{
    public:
        int                                                     socket_listen;
        std::string                                             host;
        std::string                                             port;
        std::map<int, std::string>                              errorPages;
        long                                                    clientMaxBodySize;
        std::set<std::string>                                   allowedMethods;
        std::pair<int, std::string>                             redirection;
        std::map<std::string, Location>                         locations;


        void        createSocket();
        void        startListening();
        // int         accept();
        // Location    match_location(std::string &uri);

};



#endif