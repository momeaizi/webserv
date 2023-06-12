# ifndef CLIENT_HPP
# define CLIENT_HPP
# include "Location.hpp"
# include "string.hpp"
# include "errors.hpp"
# include <sys/socket.h>
# include <fstream> // remove
# include <filesystem> // remove
# include <string>
# include <iostream>

# define MAX 2043


std::string     trimString(const std::string &str);
class Client
{
    public:
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
    Client():phase(1), methodType(""){}
    void    parse();
    void    uploadFile();
    void    PostHandler();
};

#endif