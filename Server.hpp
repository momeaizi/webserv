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
#include <list>
#include "Location.hpp"
#include "Client.hpp"




extern fd_set          master;
extern int             max_socket;


struct Host
{
    std::map<int, std::string>                              errorPages;
    long                                                    clientMaxBodySize;
    std::set<std::string>                                   allowedMethods;
    std::pair<int, std::string>                             redirection;
    std::map<std::string, Location>                         locations;

    Host();
    Host(const Host &host);
    void    clear();
};

class   Server
{
    public:

        int                                                     socket_listen;
        std::string                                             port;
        std::string                                             hostName;
        Host                                                    host;
        std::map<std::string, Host>                             hosts;


        Server();
        Server(const Server &serv);
        ~Server();



        void        createSocket();
        void        startListening();
        int         acceptClient(std::list<Client> &clients, size_t serverId);
        void        clear();
        Server  &operator+= (const Server& serv);

};



#endif