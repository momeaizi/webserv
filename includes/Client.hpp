# ifndef CLIENT_HPP
# define CLIENT_HPP
# include "Location.hpp"
# include "string.hpp"
# include "errors.hpp"
# include "filesCont.hpp"
# include "autoindex.hpp"
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

# define MAX 2048
# define CHUNK_SIZE 2048
# define BUFFER_SIZE 2048
# define ALLOWED_CHAR_IN_URI     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~!$&'()*+,;=:@/?#[]%"



std::string     trimString(const std::string &str);
int             deleteDir(const char* path);
void            InitstatusCodesage();
void            mimeTypesInitializer();

class Server;

class Client
{
    public:
        int                                 clSocket;
        int                                 phase;
        int                                 Rfd;
        size_t                              chunked;
        Server                              &server;
        size_t                              bytesUploaded;
        size_t                              resourceSize;
        std::ofstream                       uploadFile;
        std::string                         methodType;
        std::string                         URI;
        std::string                         querieString;
        std::string                         buffer;
        std::string                         response;
        std::string                         resource;
        std::map<std::string, std::string>  headerFields;
        std::string                         ipAddress;
        Location                            *location;
        std::string                         boundary;
        time_t                              lastActivity;
        void                                (Client::*serve)( void );
    

    public:

        Client(int clSocket, Server &server, const std::string &ipAddress) : 
                clSocket(clSocket), phase(1), Rfd(-1), chunked(0), server(server), bytesUploaded(0), resourceSize(0), methodType(""), resource(""), ipAddress(ipAddress), location(NULL), lastActivity(time(NULL)), serve(&Client::parse)
        {
            fcntl(clSocket, F_SETFL, O_NONBLOCK);
            int set = 1;
            setsockopt(clSocket, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int)); 
        }

        Client  &operator= (const Client &cl)
        {
            clSocket = cl.clSocket;
            phase = cl.phase;
            Rfd = cl.Rfd;
            bytesUploaded = cl.bytesUploaded;
            resourceSize = cl.resourceSize;
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
        void                chunkedUpload();
        void                boundaryUpload();
        void                GetFromFile();
        void                PostHandler();
        void                DeleteHandler();
        void                GetHandler();
        std::string         initializeupload();
        void                drop(fd_set &readMaster, fd_set &writeMaster);
        void                clear();
        void                redirect(int statusCode);
        void                setHeader(int error_status);


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
