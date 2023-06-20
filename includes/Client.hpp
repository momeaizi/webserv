# ifndef CLIENT_HPP
# define CLIENT_HPP
# include "Location.hpp"
# include "string.hpp"
# include "errors.hpp"
# include "filesCont.hpp"
# include "Server.hpp"
# include <sys/socket.h>
# include <unistd.h>
# include <fstream>
# include <list>
# include <fcntl.h>
# include <dirent.h>
# include <sstream>
# include <cstdio>
# include <string>
# include <iostream>
# include <ctime>

# define MAX 2043


std::string     trimString(const std::string &str);
int deleteDir(const char* path);

class Server;

class Client
{
    public:
        int                                 clSocket;
        int                                 phase;
        int                                 fd;
        int                                 Rfd;
        Server                              &server;
        size_t                              bytesUploaded;
        std::ofstream                       uploadFile;
        std::string                         methodType;
        std::string                         URI;
        std::string                         buffer;
        std::string                         response;
        std::string                         resource;
        std::map<std::string, std::string>  headerFields;
        std::string                         ipAddress;
        Location                            *location;
        time_t                              lastActivity;
        void                                (Client::*serve)( void );
    

    public:

        Client(int clSocket, Server &server, const std::string &ipAddress) : 
                    clSocket(clSocket), phase(1), Rfd(-1), server(server), bytesUploaded(0), methodType(""), resource(""), ipAddress(ipAddress), location(NULL), lastActivity(time(NULL)), serve(&Client::parse) {}

        Client  &operator= (const Client &cl)
        {
            clSocket = cl.clSocket;
            phase = cl.phase;
            fd = cl.fd;
            bytesUploaded = cl.bytesUploaded;
            methodType = cl.methodType;
            URI = cl.URI;
            buffer = cl.buffer;
            resource = cl.resource;
            headerFields = cl.headerFields;
            location = cl.location;
            ipAddress = cl.ipAddress;
            lastActivity = time(NULL);
            serve = cl.serve;
        
            return *this;
        }

        Client(const Client &cl) : server(cl.server)
        {
            *this = cl;
        }

        ~Client() {};
        void                parse();
        void                upload();
        void                GetFromFile();
        void                PostHandler();
        void                DeleteHandler();
        void                GetHandler();
        std::string         initializeupload();
        void                drop(fd_set &readMaster, fd_set &writeMaster);
        void                clear();
        void                send_error(int error_status);


        /*                              setters                                         */
        // void    setResource();
        // void    setLocation();
        // void    setIpAddress();

        /*                              getters                                         */
        int                 getClSocket() {return clSocket; }
        int                 getPhase() {return phase; }
        const std::string   &getResource() {return resource; }
        const std::string   &getIpAddress() { return ipAddress; }
};

#endif