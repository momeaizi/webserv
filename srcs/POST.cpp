# include "../includes/Client.hpp"

extern std::map<int, std::string>          statusCodes;
extern std::map<std::string, std::string>  mimeTypes;

void Client::PostHandler()
{
    if (!location->getUpload().empty())
    {
        if (!ft::isPathExists(location->getUpload()))
            setHeader(404);
        else
            serve = &Client::upload;
        return;
    }
    else if (!ft::isPathExists(resource))
    {
        setHeader(404);
        return ;
    }
    if (ft::isDirectory(resource))
    {
        if (!hasSlash(URI))
        {
            setHeader(301);
            return ;
        }
        std::string filePath = resource;
        if (hasIndex(location->getIndex()))
            filePath += location->getIndex();
        if (!ft::isFile(filePath))
        {
            setHeader(403);
            return ;
        }
        resource = filePath;
    }
    if (!location->locationHasCgi())
        setHeader(403);
    else
        runCGI();
}

void Client::upload() 
{
    if (this->headerFields["content-type"].substr(0, 20) == "multipart/form-data;")
        return boundaryUpload();

    if (!this->bytesUploaded)
    {
        chunked = 0;
        std::string extention = initializeupload() + mimeTypes[this->headerFields["content-type"]];
        if (uploadFd == -1) // if is already opened in CGi
        {
            uploadFd = open(std::string(this->location->getUpload() + "/" + extention).c_str(), O_RDWR  | O_CREAT/*| O_BINARY*/ ,0660);
            if (uploadFd < 0)
            {
                phase = -1;
                return ;
            }
        }
    }
    if (this->headerFields["transfer-encoding"] == "chunked")
        return chunkedUpload();


    std::string str;
    size_t      ContentLength;
    size_t      max_body_size = static_cast<size_t>(server.getClientMaxBodySize());
    try
    {
        ContentLength = stol(this->headerFields["content-length"]);
    }
    catch (...)
    {
        phase = -1;
        return ;
    }
    if (server.getClientMaxBodySize() != -1 && ContentLength > max_body_size)
    {
        close(uploadFd);
        uploadFd = -1;
        return setHeader(413);
    }
    if (bytesUploaded == ContentLength)
    {
        close(uploadFd);
        uploadFd = -1;
        if (serve != &Client::writeInCGI)
            setHeader(201);
        return ;
    }
    if (this->buffer.size() + bytesUploaded <= ContentLength)
        str = buffer;
    else
        str = buffer.substr(0, ContentLength - bytesUploaded);

    if (write(uploadFd, str.data(), str.length()) <= 0)
        phase = -1;

    buffer = buffer.substr(str.length());
    this->bytesUploaded += str.length();
}

void    Client::boundaryUpload()
{
    std::string str;
    size_t loc;

    if (this->boundary == "")
        this->boundary = "--" + this->headerFields["content-type"].substr(30);

    if (buffer.substr(0, boundary.size()) == boundary)
    {
        if(buffer.substr(0, boundary.size() + 2) == boundary + "--")
        {
            close(uploadFd);
            uploadFd = -1;
            setHeader(201);
            return ;
        }
        if (uploadFd != -1)
        {
            close(uploadFd);
            uploadFd = -1;
        }
        std::list<std::string> lines = getlines(buffer);
        std::list<std::string>::iterator it;
        std::string name;

        for (it = lines.begin(); it != lines.end(); it++)
        {
            str = *it;
            if(str == "")
                break;
            loc = str.find("filename=");
            if (loc != std::string::npos)
                name = str.substr(loc + 10);
            else
            {
                loc = str.find("name=");
                if (loc != std::string::npos)
                    name = str.substr(loc + 10);
            }
        }
        loc = name.find("\"");
        uploadFd = open(std::string(this->location->getUpload() + "/" + name.substr(0, loc)).c_str(), O_WRONLY | O_CREAT , 0660);
        if (uploadFd < 0)
        {
            phase = -1;
            return ;
        }
    }

    loc = buffer.find("\r\n" + boundary);
    if (loc == std::string::npos)
    {
        str = buffer;
        loc = 0;
    }
    else
    {
        str = buffer.substr(0, loc);
        loc = 2;
    }
    if (write(uploadFd, str.data(), str.length()) < 0)
        phase = -1;
    buffer = buffer.substr(str.size() + loc);
    this->bytesUploaded += str.size();
}

void Client::chunkedUpload()
{
    std::string str;
    size_t loc;
    while (buffer.size())
    {
        if (!this->chunked)
        {
            loc = this->buffer.find("\r\n");
            if (!loc)
            {
                this->buffer = this->buffer.substr(loc + 2);
                loc = this->buffer.find("\r\n");
            }
            if (loc != std::string::npos)
            {
                str = this->buffer.substr(0, loc);
                try
                {
                    this->chunked = std::stol(str, nullptr, 16);
                }
                catch (...)
                {
                    phase = -1;
                    return ;
                }
                this->buffer = this->buffer.substr(loc + 2);
                size_t  max_body_size = static_cast<size_t>(server.getClientMaxBodySize());
                if (server.getClientMaxBodySize() != -1 && chunked > max_body_size)
                {
                    return setHeader(413);
                }
                if(!chunked)
                {
                    close(uploadFd);
                    uploadFd = -1;
                    if (serve != &Client::writeInCGI)
                        setHeader(201);
                    return ;
                }
            }
            else
                return ;
        }

        if (buffer.size() < this->chunked)
            str = this->buffer.substr(0, buffer.size());
        else
            str = this->buffer.substr(0, this->chunked);
        if (write(uploadFd, str.data(), str.length()) < 0)
            phase = -1;
        loc = str.size();
        if (buffer.size() > this->chunked) loc += 2;
        if (buffer.size() < loc) loc = buffer.size();
        this->buffer = this->buffer.substr(loc);
        this->chunked -= str.size();
        this->bytesUploaded += str.size();
    }
}

std::string  Client::initializeupload()
{
    std::string FileName;

    time_t now = time(NULL);
    tm *gmtm = gmtime(&now);
    FileName  = std::to_string(gmtm->tm_mday) + "_";
    FileName += std::to_string(gmtm->tm_mon + 1) + "_";
    FileName += std::to_string(1900 + gmtm->tm_year) + "_";
    FileName += std::to_string(gmtm->tm_hour + 5) + "_";
    FileName += std::to_string(gmtm->tm_min + 30) + "_";
    FileName += std::to_string(gmtm->tm_sec);
	srand((unsigned) time(NULL));
    FileName += std::to_string(rand());
    return FileName;
}