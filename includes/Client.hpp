# ifndef CLIENT_HPP
# define CLIENT_HPP



# include "fileSystemUtils.hpp"
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
void            InitReasonPhrase();
void            InitMimeTypes();
bool            hasSlash(const std::string &resource);
bool            hasIndex(const std::string &index);
void            StringOfCurrentContent(const std::string &path, const std::string &filename, const std::string &uri);


class Server;
class ContextManager;

class Client
{
    private:
        pid_t                               childPID;
        int                                 clSocket;
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
        std::string                         uploadFileName;
        std::map<std::string, std::string>  headerFields;
        std::string                         ipAddress;
        Location                            *location;
        std::string                         boundary;
        time_t                              lastActivity;
        void                                (Client::*serve)( void );
    

    public:
        friend class ContextManager;


        Client(int clSocket, Server &server, const std::string &ipAddress);
        Client  &operator= (const Client &cl);
        Client(const Client &cl) : server(cl.server) { *this = cl; }

        void                parse();
        void                setQuerieString();
        void                upload();
        void                chunkedUpload();
        void                boundaryUpload();
        void                serveStaticFIle();
        void                PostHandler();
        void                DeleteHandler();
        void                GetHandler();
        std::string         generateFileNameFromDate();
        void                drop();
        void                clear();
        void                redirect(int statusCode);
        void                setHeader(int error_status);
        void                serveCGI();
        void                passRequestBodyAndWait();
        void                receiveCGIOuput();
        char                **fillCgiEnvVars();


        int                 getClSocket() {return clSocket; }
};


#endif
