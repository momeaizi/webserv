# ifndef CLIENT_HPP
# define CLIENT_HPP
# include "fileSystemUtils.hpp"
# include "autoindex.hpp"
# include "Location.hpp"
# include "string.hpp"
# include "Server.hpp"
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <list>
# include <cstdio>
# include <ctime>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAX 2048
# define CHUNK_SIZE 2048
# define BUFFER_SIZE 2048
# define ALLOWED_CHAR_IN_URI     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~!$&'()*+,;=:@/?#[]%"

extern fd_set  readMaster;
extern fd_set  writeMaster;
extern int     maxFds;

extern std::map<int, std::string>          statusCodes;
extern std::map<std::string, std::string>  mimeTypes;

std::string     trimString(const std::string &str);
int             deleteDir(const char* path);
void            InitstatusCodesage();
void            mimeTypesInitializer();
bool            hasSlash(const std::string &resource);
bool            hasIndex(const std::string &index);

class Server;
class ContextManager;

class Client
{
    private:
        pid_t                               childPID;
        int                                 clSocket;
        int                                 phase;
        size_t                              chunked;
        Server                              &server;
        size_t                              bytesUploaded;
        size_t                              resourceSize;
        int                                 cgi_fd;
        int                                 uploadFd;
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
        friend class ContextManager;
        Client(int clSocket, Server &server, const std::string &ipAddress) : 
                clSocket(clSocket), phase(1), chunked(0), server(server), bytesUploaded(0), 
                resourceSize(0), cgi_fd(-1), uploadFd(-1), methodType(""), resource(""), ipAddress(ipAddress),
                location(NULL), lastActivity(time(NULL)), serve(&Client::parse)
        {
            fcntl(clSocket, F_SETFL, O_NONBLOCK);
            int set = 1;
            setsockopt(clSocket, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int)); 
        }

        Client  &operator= (const Client &cl)
        {
            clSocket = cl.clSocket;
            phase = cl.phase;
            bytesUploaded = cl.bytesUploaded;
            resourceSize = cl.resourceSize;
            methodType = cl.methodType;
            uploadFd = cl.uploadFd;
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
        void                setQuerieString();
        void                upload();
        void                chunkedUpload();
        void                boundaryUpload();
        void                GetFromFile();
        void                PostHandler();
        void                DeleteHandler();
        void                GetHandler();
        std::string         initializeupload();
        void                drop();
        void                clear();
        void                redirect(int statusCode);
        void                setHeader(int error_status);
        void                runCGI();
        void                writeInCGI();
        void                CGIHeaders();
        char                **CgiEnv();


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
