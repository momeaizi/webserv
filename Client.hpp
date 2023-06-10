# ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Location.hpp"
// #include <vector>

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
    void parse();


};

#endif