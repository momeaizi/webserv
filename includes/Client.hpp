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

extern fd_set          master;


std::string     trimString(const std::string &str);

class Client
{
    public:
        int                                 clSocket;
        int                                 phase;
        int                                 fd;
        unsigned int                        serverId;
        size_t                              lenUpload;
        size_t                              seekg;
        std::ifstream                       UploadFile;
        std::string                         methodType;
        std::string                         URI;
        std::string                         buffer;
        std::string                         resources;
        std::map<std::string, std::string>  headerFields;
        Location                            *location;
        std::string                         ipAddress;
    

    Client(int clSocket, unsigned int serverId, const std::string &ipAddress) : 
                clSocket(clSocket), phase(1), serverId(serverId), lenUpload(0), seekg(0), methodType(""), resources(""), ipAddress(ipAddress) {}
    Client() 
        : phase(1), lenUpload(0), seekg(0), methodType(""), resources("") {}


    void    parse();
    void    uploadFile();
    void    PostHandler();
    void    DeleteHandler();
    void    GetHandler();
    void    drop();
    std::ifstream    initializeUploadFile();
    std::string getRsouces() {return resources;}
};

#endif