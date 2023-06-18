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
# include <fcntl.h>
# include <dirent.h>
# include <cstdio>
# include <string>
# include <iostream>
# include <ctime>

# define MAX 2043

extern fd_set          master;


std::string     trimString(const std::string &str);
int deleteDir(const char* path);

class Server;

class Client
{
    private:
        int                                 clSocket;
        int                                 phase;
        int                                 fd;
        int                                 chunked;
        Server                              &server;
        size_t                              bytesUploaded;
        size_t                              seekg;
        std::ofstream                       uploadFile;
        std::string                         methodType;
        std::string                         URI;
        std::string                         buffer;
        std::string                         resource;
        std::map<std::string, std::string>  headerFields;
        std::string                         ipAddress;
        std::string                         respnse;
        std::string                         boundary;
        Location                            *location;
    

    public:

        Client(int clSocket, Server &server, const std::string &ipAddress) : 
                    clSocket(clSocket), phase(1), chunked(0), server(server), bytesUploaded(0), seekg(0), methodType(""), resource(""), ipAddress(ipAddress), location(NULL) {}
        Client(){};
        Client  &operator= (const Client &cl)
        {
            clSocket = cl.clSocket;
            phase = cl.phase;
            fd = cl.fd;
            bytesUploaded = cl.bytesUploaded;
            seekg = cl.seekg;
            methodType = cl.methodType;
            URI = cl.URI;
            buffer = cl.buffer;
            resource = cl.resource;
            headerFields = cl.headerFields;
            location = cl.location;
            ipAddress = cl.ipAddress;
        
            return *this;
        }

        Client(const Client &cl) : server(cl.server)
        {
            *this = cl;
        }

        ~Client() {};

        void                parse();
        void                upload();
        void                chunkedUpload();
        void                boundaryUpload();
        void                PostHandler();
        void                DeleteHandler();
        void                GetHandler();
        void                GetFromFile();
        std::string         initializeupload();
        void                drop();


        /*                              setters                                         */
        // void    setResource();
        // void    setLocation();
        // void    setIpAddress();

        /*                              getters                                         */
        int                 getClSocket() {return clSocket; }
        const std::string   &getResource() {return resource; }
        const std::string   &getIpAddress() { return ipAddress; }
};

#endif