# include "../includes/Client.hpp"
# include <dirent.h>
# include <cstdio>


std::map<int, std::string>          statusCodes;
std::map<std::string, std::string>  mimeTypes;




void    InitstatusCodesage()
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

void    mimeTypesInitializer()
{
    std::ifstream mimeFile("mimeTypes");
    std::string   line;
    if (!mimeFile.is_open())
		throw "mimeTypes File can't be opened!";
    while (getline(mimeFile, line))
    {
        
        line = line.substr(find_first_not(" \t"), find_last_not(" \t"));
        if (line.empty())
            continue;
        int loc = line.find(" \t");
        if (loc != std::string::npos)
        {
            std::string ext = "." + line.substr(0, loc);
            std::string type = line.substr(loc + 1);
            type = type.substr(find_first_not(" \t"));

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

    response = "HTTP/1.1 " + std::to_string(statusCode) + " " + statusCodes[statusCode] + "\r\n";
    if (statusCode != 200)
    {
        if (server.getErrorPages().count(statusCode))
            resource = server.getErrorPages().at(statusCode);
        else
            resource = "errorPages/" + std::to_string(statusCode) + ".html";
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
        response += "Content-Length: " + std::to_string(resourceSize) + "\r\n";


        if (headerFields.count("connection") and headerFields["connection"] != "Keep-Alive")
            response += "Connection: Keep-Alive\r\n";


        if (statusCode >= 301 && statusCode <= 302)
            redirect(statusCode);

        serve = &Client::GetFromFile;
    }
    else
        phase = -1;
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

void Client::GetFromFile()
{
    char    buff[BUFFER_SIZE];

    if (Rfd == -1)
        Rfd = open(resource.data(), O_RDONLY);
    else if (resourceSize > CHUNK_SIZE)
        response += "\r\n";


    int  len = read(Rfd, buff, CHUNK_SIZE);
    if (len <= 0)
    {
        if (resourceSize > CHUNK_SIZE)
            this->response += "0\r\n\r\n";
        phase = -1;
        return ;
    }
    if (resourceSize > CHUNK_SIZE)
    {
        std::stringstream stream;
        stream << std::hex << len;
        this->response +=  stream.str() + "\r\n";
    }
    this->response += std::string(buff, len);
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
    phase = 0;
    if (Rfd != -1)
    {
        close(Rfd);
        Rfd = -1;
    }

    bytesUploaded = 0;
    resourceSize = 0;
    uploadFile.close();
    uploadFile.clear();
    methodType.clear();
    URI.clear();
    resource.clear();
    headerFields.clear();
    location = NULL;
    serve = &Client::parse;
}
