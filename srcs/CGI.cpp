# include "../includes/Client.hpp"
# include <string.h>


char    **Client::fillCgiEnvVars()
{
    std::set<std::string>   cgi_env;

    cgi_env.insert(std::string("REQUEST_METHOD=") + methodType);
    cgi_env.insert(std::string("QUERY_STRING=") + querieString);
    if (!headerFields["content-type"].empty())
        cgi_env.insert(std::string("CONTENT_TYPE=") + headerFields["content-type"]);
    if (!headerFields["content-length"].empty())
        cgi_env.insert(std::string("CONTENT_LENGTH=") + headerFields["content-length"]);
    if (!headerFields["cookie"].empty())
        cgi_env.insert(std::string("HTTP_COOKIE=") + headerFields["cookie"]);
    if (!headerFields["user-agent"].empty())
        cgi_env.insert(std::string("HTTP_USER_AGENT=") + headerFields["user-agent"]);
    cgi_env.insert(std::string("REMOTE_ADDR=") + ipAddress);
    cgi_env.insert(std::string("SERVER_NAME=") + server.getHostName());
    cgi_env.insert(std::string("SERVER_PORT=") + server.getPort());
    cgi_env.insert(std::string("PATH_INFO=" + resource));
    cgi_env.insert(std::string("SCRIPT_FILENAME=" + resource));
    cgi_env.insert(std::string("SCRIPT_NAME="+ resource));
    cgi_env.insert("REDIRECT_STATUS=200");
    cgi_env.insert("SERVER_PROTOCOL=HTTP/1.1");
    cgi_env.insert("GATEWAY_INTERFACE=CGI/1.1");



    char    **env = new char*[cgi_env.size() + 1];


    std::set<std::string>::iterator it = cgi_env.begin();
    for (size_t i = 0; i < cgi_env.size(); ++i, ++it)
        env[i] = strdup(it->c_str());

    env[cgi_env.size()] = NULL;

    return env;
}

char    **fillArgs(const std::string &ext, const std::string &path)
{
        char    **argv = new char*[3];

        argv[0] = strdup(ext.c_str());

        argv[1] = strdup(path.c_str());

        argv[2] = NULL;
        return argv;
}

void Client::serveCGI()
{
    size_t          pos = resource.find_last_of(".");
    std::string     ext;
    std::string     cgi_bin;
    std::string     filename = "/tmp/" + generateFileNameFromDate();

    if (pos != std::string::npos)
    {
        ext = resource.substr(pos + 1);
        cgi_bin = location->getCgiBin(ext);

        if (cgi_bin.empty())
            return setHeader(200);
    }
    else
        return setHeader(200);

    childPID = fork();
    if (!childPID)
    {
        char        **env = fillCgiEnvVars();
        char        **args = fillArgs(ext, resource);

        uploadFd = open(std::string(filename + "_in").c_str(), O_RDWR | O_CREAT, 0660);
        cgi_fd = open(std::string(filename + "_out").c_str(), O_RDWR | O_CREAT, 0660);

        if (cgi_fd < 0 || uploadFd < 0)
            exit(1);
    
        dup2(uploadFd, 0);
        dup2(cgi_fd, 1);
        
        close(uploadFd);
        close(cgi_fd);



        if (execve(cgi_bin.c_str(), args, env) < 0)
            std::cerr << "execve failed!" << std::endl;

        exit(1);

    }
    else if (childPID < 0)
    {
        std::cerr <<  "Fork failed!" << std::endl;
        serve = NULL;
        return ;
    }

    uploadFd = open(std::string(filename + "_in").c_str(), O_RDWR | O_CREAT, 0660);
    cgi_fd = open(std::string(filename + "_out").c_str(), O_RDWR | O_CREAT, 0660);

    if (cgi_fd < 0 || uploadFd < 0)
    {
        serve = NULL;
        return ;
    }
    serve = &Client::passRequestBodyAndWait;
}

void    Client::passRequestBodyAndWait()
{
    int     status;

    if (methodType == "POST")
        upload();

    waitpid(childPID, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        int exitStatus = WEXITSTATUS(status);

        if (exitStatus)
        {
            close(uploadFd);
            uploadFd = -1;
            return setHeader(500);
        }

        response = "HTTP/1.1 200 OK\r\n";
        serve = &Client::receiveCGIOuput;
    }
}

void Client::receiveCGIOuput()
{
    char    buff[CHUNK_SIZE];
    int     bytesRead = read(cgi_fd, buff, CHUNK_SIZE);

    if (bytesRead <= 0)
    {
        serve = NULL;
        return ;
    }
    this->response += std::string(buff, bytesRead);
}