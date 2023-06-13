# ifndef CLIENT_HPP
# define CLIENT_HPP
# include "Location.hpp"
# include "string.hpp"
# include "errors.hpp"
# include "filesCont.hpp"
# include <sys/socket.h>
# include <unistd.h>
# include <fstream>
# include <list>
# include <dirent.h>
# include <cstdio>
# include <string>
# include <iostream>
# include <ctime>

# define MAX 2043


std::string     trimString(const std::string &str);

class Client
{
    public:
<<<<<<< HEAD
        int                                 clSocket;
=======
        size_t                              lenUpload;
        size_t                              seekg;
        int                                 clSocker;
>>>>>>> 2a5b7396c573af1a56a27a309332ee3c68dafeaa
        int                                 phase;
        int                                 fd;
        unsigned int                        serverId;
        std::string                         methodType;
        std::string                         URI;
        std::string                         buffer;
        std::string                         resources;
        std::map<std::string, std::string>  headerFields;
        Location                            *location;
        std::string                         ipAddress;
    
    // member func
<<<<<<< HEAD
    Client(int clSocket, unsigned int serverId, const std::string &ipAddress) : clSocket(clSocket), phase(1), serverId(serverId), methodType(""), ipAddress(ipAddress) {}
    void parse();


=======
    Client():lenUpload(0), seekg(0), phase(1), methodType(""), resources(""){}
    void    parse();
    void    uploadFile();
    void    PostHandler();
    void    DeleteHandler();
    void    GetHandler();
    std::string getRsouces() {return resources;}
>>>>>>> 2a5b7396c573af1a56a27a309332ee3c68dafeaa
};

#endif