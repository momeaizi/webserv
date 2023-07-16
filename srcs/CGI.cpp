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
    int p[2];


    if (pipe(p) < 0)
    {
        phase = -1;
        return ;
    }

    cgi_fd = p[1];
    uploadFd = p[0];

    childPID = fork();
    if (!childPID)
    {
        dup2(uploadFd, 0);
        dup2(cgi_fd, 1);

        close(uploadFd);
        close(cgi_fd);



        char    **argv = new char*[3];

        argv[0] = new char[4];
        memcpy(argv[0], "php", 3);
        argv[0][3] = '\0';

        argv[1] = new char[42];
        memcpy(argv[1], "/Users/momeaizi/goinfre/webserv/index.php", 41);
        argv[1][41] = '\0';

        argv[2] = NULL;

        if (execve("/usr/bin/php", argv, NULL/*env*/) < 0)
            std::cerr << "execve failed!" << std::endl;

        exit(1);
    }
    else if (childPID < 0)
    {
        std::cerr <<  "Fork failed!" << std::endl;
        phase = -1;
        return ;
    }

    serve = &Client::writeInCGI;
}

void    Client::writeInCGI()
{
    int     status;

    if (methodType == "POST")
        upload();

    waitpid(childPID, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        // int exitStatus = WEXITSTATUS(status);
        int exitStatus = 200;

        response = "HTTP/1.1 " + std::to_string(exitStatus) + " " + statusCodes[exitStatus] + "\r\n"; // change exitSatus by the satus header
        serve = &Client::CGIHeaders;
    }
}

void Client::CGIHeaders()
{
    std::cout << "CGIHeaders ____"<< std::endl;
    char    buff[CHUNK_SIZE];
    int  bytesRead = read(cgi_fd, buff, CHUNK_SIZE);

    std::cout << "111      " << bytesRead<< std::endl;
    if (bytesRead <= 0)
    {
        phase = -1;
        return ;
    }
    this->response += std::string(buff, bytesRead);
    std::cout << this->response << std::endl;
}