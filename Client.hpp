# ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Location.hpp"
// #include <vector>
std::string     trimString(const std::string &str);

class Client
{
    public:
        int                                 clSocket;
        int                                 phase;
        int                                 fd;
        unsigned int                        serverId;
        std::string                         methodType;
        std::string                         URI;
        std::string                         resources;
        std::map<std::string, std::string>  headerFields;
        Location                            *location;
        std::string                         ipAddress;
    
    // member func
    Client(int clSocket, unsigned int serverId, const std::string &ipAddress) : clSocket(clSocket), phase(1), serverId(serverId), methodType(""), ipAddress(ipAddress) {}
    void parse();


};

#endif