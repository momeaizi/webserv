# include "../includes/Client.hpp"
# include <dirent.h>
# include <cstdio>



void    InitReasonPhrase()
{
    statusCodes[100] = "Continue";
    statusCodes[101] = "Switching Protocols";
    statusCodes[200] = "OK";
    statusCodes[201] = "Created";
    statusCodes[204] = "No Content";
    statusCodes[301] = "Moved Permanently";
    statusCodes[400] = "Bad Request";
    statusCodes[401] = "Unauthorized";
    statusCodes[403] = "Forbidden";
    statusCodes[404] = "Not Found";
    statusCodes[405] = "Method Not Allowed";
    statusCodes[409] = "Conflict";
    statusCodes[413] = "Request Entity Too Large";
    statusCodes[414] = "Request_URI Too Long";
    statusCodes[500] = "Internal Server Error";
    statusCodes[501] = "Not Implemented";
    statusCodes[505] = "HTTP Version Not Supported";
}

void    InitMimeTypes()
{
    std::ifstream mimeFile("mime.types");
    std::string   line;

    if (!mimeFile.is_open())
		throw "mime.types File can't be opened!";

    while (getline(mimeFile, line))
    {

        line = trimString(line);
    
        if (line.empty())
            continue;

        size_t loc = line.find(' ');
        loc = std::min(loc , line.find('\t'));

        if (loc != std::string::npos)
        {
            std::string ext = "." + line.substr(0, loc);
            std::string type = trimString(line.substr(loc));

            mimeTypes[ext] = type;
            mimeTypes[type] = ext;
        }
		else
            throw "the line is not valid!";
    }
}

void    Client::redirect(int statusCode)
{
    std::pair<int, std::string> redirection = location->getRedirection();


    if (redirection.first == statusCode)
    {
        if (redirection.second[0] == '/')
            response += "Location: http://" + server.getHostName() + ":" + server.getPort() + redirection.second + "/\r\n";
        else
            response += "Location: " + redirection.second + "\r\n";

    }
    else
        response += "Location: http://" + server.getHostName() + ":" + server.getPort() + URI + "/\r\n";
}



void Client::setHeader(int statusCode)
{

    response = "HTTP/1.1 " + to_string(statusCode) + " " + statusCodes[statusCode] + "\r\n";
    if (statusCode != 200)
    {
        if (server.getErrorPages().count(statusCode))
            resource = server.getErrorPages().at(statusCode);
        else
            resource = "errorPages/" + to_string(statusCode) + ".html";
    }

    if (ft::isFile(resource.data()))
    {
        std::string key;
        size_t      found = resource.find_last_of('.');

        if (found != std::string::npos)
            key = resource.substr(found, resource.length());

        if (found != std::string::npos && mimeTypes.count(key))
            response += "Content-Type: " + mimeTypes[key] + "\r\n";
        else
            response += "Content-Type: text/plain\r\n";


        resourceSize = ft::GetFileSize(resource.data());

        if (resourceSize > CHUNK_SIZE)
            response += "Transfer-Encoding: chunked\r\n";
        else
            response += "Content-Length: " + to_string(resourceSize) + "\r\n";


        if (headerFields.count("connection") and headerFields["connection"] != "Keep-Alive")
            response += "Connection: Keep-Alive\r\n";


        if (statusCode >= 301 && statusCode <= 302)
            redirect(statusCode);

        serve = &Client::serveStaticFIle;
    }
    else
        serve = NULL;
    response += "\r\n";

}


bool hasSlash(const std::string &resource)
{
    int index;

    index = resource.length() - 1;
    return (resource[index] == '/');
}

bool hasIndex(const std::string &index)
{
    return !index.empty();
}

void Client::serveStaticFIle()
{
    char    buff[CHUNK_SIZE];

    if (uploadFd == -1)
    {
        uploadFd = open(resource.c_str(), O_RDONLY /*| O_BINARY*/);
        if (uploadFd < 0)
        {
            serve = NULL;
            return ;
        }
    }
    else if (resourceSize > CHUNK_SIZE)
        response += "\r\n";


    int bytesRead = read(uploadFd, buff, CHUNK_SIZE);

    if (bytesRead <= 0)
    {
        if (resourceSize > CHUNK_SIZE)
            this->response += "0\r\n\r\n";
        serve = NULL;
        return ;
    }
    if (resourceSize > CHUNK_SIZE)
    {
        std::stringstream stream;
        stream << std::hex << bytesRead;
        this->response +=  stream.str() + "\r\n";
    }
    this->response += std::string(buff, bytesRead);
}

void    Client::drop()
{
    clear();
    close(clSocket);
    FD_CLR(clSocket, &readMaster);
    FD_CLR(clSocket, &writeMaster);
}

void    Client::clear()
{
    bytesUploaded = 0;
    resourceSize = 0;
    if (uploadFd != -1)
    {
        if (methodType == "POST" && bytesUploaded != resourceSize)
            remove(uploadFileName.c_str());
        close(uploadFd);
        uploadFd = -1;
    }
    if (cgi_fd != -1)
    {
        close(cgi_fd);
        cgi_fd = -1;
    }
    methodType.clear();
    URI.clear();
    resource.clear();
    headerFields.clear();
    location = NULL;
    serve = &Client::parse;
}


Client::Client(int clSocket, Server &server, const std::string &ipAddress) : 
                clSocket(clSocket),  chunked(0), server(server), bytesUploaded(0), 
                    resourceSize(0), cgi_fd(-1), uploadFd(-1), methodType(""), resource(""),
                        ipAddress(ipAddress), location(NULL), lastActivity(time(NULL)), serve(&Client::parse)
{
    fcntl(clSocket, F_SETFL, O_NONBLOCK);
    // int set = 1;
    // setsockopt(clSocket, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int)); 
}


Client  &Client::operator= (const Client &cl)
{
    clSocket = cl.clSocket;
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