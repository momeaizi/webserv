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
#include "ConfigAttr.hpp"




extern fd_set          master;



class   Server
{
    public:

        int                                                     socket_listen;
        std::string                                             port;
        std::string                                             hostName;
        std::map<std::string, ConfigAttr>                       configAttrs;


        Server();
        Server(const Server &serv);
        Server  &operator= (const Server& serv);
        Server  &operator+= (const Server& serv);
        ~Server();



        void        createSocket();
        void        startListening();
        int         acceptClient(std::list<Client> &clients, size_t serverId);
        void        clear();

};



#endif