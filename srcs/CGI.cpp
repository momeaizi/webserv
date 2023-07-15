# include "../includes/Client.hpp"
# include <string.h>

char    **Client::CgiEnv()
{
    std::set<std::string>   cgi_env;

    cgi_env.insert(std::string("REQUEST_METHOD") + "=" + methodType);
    if (!querieString.empty())
        cgi_env.insert(std::string("QUERY_STRING") + "=" + querieString);
    if (!headerFields["content-type"].empty())
        cgi_env.insert(std::string("CONTENT_TYPE") + "=" + headerFields["content-type"]);
    if (!headerFields["content-length"].empty())
        cgi_env.insert(std::string("CONTENT_LENGTH") + "=" + headerFields["content-length"]);
    if (!headerFields["cookie"].empty())
        cgi_env.insert(std::string("HTTP_COOKIE") + "=" + headerFields["cookie"]);
    if (!headerFields["user-agent"].empty())
        cgi_env.insert(std::string("HTTP_USER_AGENT") + "=" + headerFields["user-agent"]);
    cgi_env.insert(std::string("REMOTE_ADDR") + "=" + ipAddress);
    cgi_env.insert(std::string("SERVER_NAME") + "=" + server.getHostName());
    cgi_env.insert(std::string("SERVER_PORT") + "=" + server.getPort());


    char    **env = new char*[cgi_env.size() + 1];

    std::set<std::string>::iterator it = cgi_env.begin();

    for (size_t i = 0; i < cgi_env.size(); ++i, ++it)
    {
        env[i] = new char[it->length() + 1];
        memcpy(env[i], it->c_str(), it->length() + 1);
    }
    env[cgi_env.size()] = NULL;

    return env;
}


void Client::runCGI()
{
    std::string filename = "/tmp/" + initializeupload();
    char        **env = CgiEnv();
    std::cout << filename << std::endl;
    
    serve = &Client::writeInCGI;

    int Rfd = open(filename.c_str(), O_RDWR);

    childPID = fork();
    if (!childPID)
    {
        dup2(Rfd, 0);
        dup2(Rfd, 1);


        char    **argv = new char*[3];

        argv[0] = new char[4];
        memcpy(argv[0], "php", 3);
        argv[0][3] = '\0';

        argv[1] = new char[42];
        memcpy(argv[1], "/Users/momeaizi/goinfre/webserv/index.php", 41);
        argv[1][41] = '\0';

        argv[1] = NULL;

        execve("/usr/bin/php", argv, env);
        exit(1);
    }
    else if (childPID < 0)
        std::cerr <<  "Fork failed!" << std::endl;;
    writeInCGI();
}

void    Client::writeInCGI()
{
    // int     status;

    // upload();
    // waitpid(childPID, &status, 0);
    // if (WIFEXITED(status))
    // {
    //     int exitStatus = WEXITSTATUS(status);

    //     response = "HTTP/1.1 " + std::to_string(exitStatus) + " " + statusCodes[exitStatus] + "\r\n"; // change exitSatus by the satus header
    //     serve = &Client::CGIHeaders;
    // }
}

void Client::CGIHeaders()
{
    // char    buff[BUFFER_SIZE];
    // int  len = read(Rfd, buff, CHUNK_SIZE);

    // if (len <= 0)
    // {
    //     phase = -1;
    //     return ;
    // }
    // this->response += std::string(buff, len);
}