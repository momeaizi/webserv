# ifndef CLIENT_HPP
# define CLIENT_HPP
# include "Location.hpp"
# include "string.hpp"
# include "errors.hpp"
# include "filesCont.hpp"
# include <sys/socket.h>
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
        size_t                              seekg;
        int                                 clSocker;
        int                                 phase;
        int                                 fd;
        unsigned int                        serverId;
        std::string                         methodType;
        std::string                         URI;
        std::string                         resources;
        std::map<std::string, std::string>  headerFields;
        Location                            *location;
    
    // member func
    Client():seekg(0), phase(1), methodType(""){}
    void    parse();
    void    uploadFile();
    void    PostHandler();
    void    DeleteHandler();
};

#endif