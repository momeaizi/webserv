# include "../includes/Client.hpp"
# include <dirent.h>
# include <cstdio>


std::map<int, std::string>          statusCodes;
std::map<std::string, std::string>  mimeTypes;

bool hasSlash(const std::string &resource);



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
    mimeTypes[".aac"]    =  "audio/aac";
    mimeTypes[".abw"]    =  "application/x-abiword";
    mimeTypes[".arc"]    =  "application/x-freearc";
    mimeTypes[".avi"]    =  "video/x-msvideo";
    mimeTypes[".azw"]    =  "application/vnd.amazon.ebook";
    mimeTypes[".bin"]    =  "application/octet-stream";
    mimeTypes[".bmp"]    =  "image/bmp";
    mimeTypes[".bz"]     =  "application/x-bzip";
    mimeTypes[".bz2"]    =  "application/x-bzip2";
    mimeTypes[".csh"]    =  "application/x-csh";
    mimeTypes[".css"]    =  "text/css";
    mimeTypes[".csv"]    =  "text/csv";
    mimeTypes[".doc"]    =  "application/msword";
    mimeTypes[".docx"]   =  "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mimeTypes[".eot"]    =  "application/vnd.ms-fontobject";
    mimeTypes[".epub"]   =  "application/epub+zip";
    mimeTypes[".gz"]     =  "application/gzip";
    mimeTypes[".gif"]    =  "image/gif";
    mimeTypes[".htm"]    =  "text/html";
    mimeTypes[".html"]   =  "text/html";
    mimeTypes[".ico"]    =  "image/vnd.microsoft.icon";
    mimeTypes[".ics"]    =  "text/calendar";
    mimeTypes[".jar"]    =  "application/java-archive";
    mimeTypes[".jpeg"]   =  "image/jpeg";
    mimeTypes[".jpg"]    =  "image/jpeg";
    mimeTypes[".js"]     =  "text/javascript  ";
    mimeTypes[".json"]   =  "application/json";
    mimeTypes[".jsonld"] =  "application/ld+json";
    mimeTypes[".mid"]    =  "audio/midi audio/x-midi";
    mimeTypes[".midi"]   =  "audio/x-midi";
    mimeTypes[".mjs"]    =  "text/javascript";
    mimeTypes[".mp3"]    =  "audio/mpeg";
    mimeTypes[".mp4"]    =  "video/mp4";
    mimeTypes[".mpeg"]   =  "video/mpeg";
    mimeTypes[".mpkg"]   =  "application/vnd.apple.installer+xml";
    mimeTypes[".odp"]    =  "application/vnd.oasis.opendocument.presentation";
    mimeTypes[".ods"]    =  "application/vnd.oasis.opendocument.spreadsheet";
    mimeTypes[".odt"]    =  "application/vnd.oasis.opendocument.text";
    mimeTypes[".oga"]    =  "audio/ogg";
    mimeTypes[".ogv"]    =  "video/ogg";
    mimeTypes[".ogx"]    =  "application/ogg";
    mimeTypes[".opus"]   =  "audio/opus";
    mimeTypes[".otf"]    =  "font/otf";
    mimeTypes[".png"]    =  "image/png";
    mimeTypes[".pdf"]    =  "application/pdf";
    mimeTypes[".php"]    =  "application/x-httpd-php";
    mimeTypes[".ppt"]    =  "application/vnd.ms-powerpoint";
    mimeTypes[".pptx"]   =  "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mimeTypes[".rar"]    =  "application/vnd.rar";
    mimeTypes[".rtf"]    =  "application/rtf";
    mimeTypes[".sh"]     =  "application/x-sh";
    mimeTypes[".svg"]    =  "image/svg+xml";
    mimeTypes[".swf"]    =  "application/x-shockwave-flash";
    mimeTypes[".tar"]    =  "application/x-tar";
    mimeTypes[".tif"]    =  "image/tiff";
    mimeTypes[".tiff"]   =  "image/tiff";
    mimeTypes[".ts"]     =  "video/mp2t";
    mimeTypes[".ttf"]    =  "font/ttf";
    mimeTypes[".txt"]    =  "text/plain";
    mimeTypes[".vsd"]    =  "application/vnd.visio";
    mimeTypes[".wav"]    =  "audio/wav";
    mimeTypes[".weba"]   =  "audio/webm";
    mimeTypes[".webm"]   =  "video/webm";
    mimeTypes[".webp"]   =  "image/webp";
    mimeTypes[".woff"]   =  "font/woff";
    mimeTypes[".woff2"]  =  "font/woff2";
    mimeTypes[".xhtml"]  =  "application/xhtml+xml";
    mimeTypes[".xls"]    =  "application/vnd.ms-excel";
    mimeTypes[".xlsx"]   =  "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mimeTypes[".xml"]    =  "application/xml";
    mimeTypes[".xul"]    =  "application/vnd.mozilla.xul+xml";
    mimeTypes[".zip"]    =  "archive  application/zip";
    mimeTypes[".3gp"]    =  "audio/video container  video/3gpp";
    mimeTypes[".3g2"]    =  "audio/video ";
    mimeTypes[".7z"]     =  "application/x-7z-compressed";

    /*---------------------------------------------------------------------------------------------------------------------------------------------------*/

    mimeTypes["audio/aac"]                                                                       =   ".aac";
    mimeTypes["application/x-abiword"]                                                           =   ".abw";
    mimeTypes["application/x-freearc"]                                                           =   ".arc";
    mimeTypes["video/x-msvideo"]                                                                 =   ".avi";
    mimeTypes["application/vnd.amazon.ebook"]                                                    =   ".azw";
    mimeTypes["application/octet-stream"]                                                        =   ".bin";
    mimeTypes["image/bmp"]                                                                       =   ".bmp";
    mimeTypes["application/x-bzip"]                                                              =   ".bz";
    mimeTypes["application/x-bzip2"]                                                             =   ".bz2";
    mimeTypes["application/x-csh"]                                                               =   ".csh";
    mimeTypes["text/css"]                                                                        =   ".css";
    mimeTypes["text/csv"]                                                                        =   ".csv";
    mimeTypes["application/msword"]                                                              =   ".doc";
    mimeTypes["application/vnd.ms-fontobject"]                                                   =   ".eot";
    mimeTypes["application/epub+zip"]                                                            =   ".epub";
    mimeTypes["application/gzip"]                                                                =   ".gz";
    mimeTypes["image/gif"]                                                                       =   ".gif";
    mimeTypes["text/html"]                                                                       =   ".htm";
    mimeTypes["text/html"]                                                                       =   ".html";
    mimeTypes["image/vnd.microsoft.icon"]                                                        =   ".ico";
    mimeTypes["text/calendar"]                                                                   =   ".ics";
    mimeTypes["application/java-archive"]                                                        =   ".jar";
    mimeTypes["image/jpeg"]                                                                      =   ".jpeg";
    mimeTypes["image/jpeg"]                                                                      =   ".jpg";
    mimeTypes["text/javascript  "]                                                               =   ".js";
    mimeTypes["application/json"]                                                                =   ".json";
    mimeTypes["application/ld+json"]                                                             =   ".jsonld";
    mimeTypes["audio/midi audio/x-midi"]                                                         =   ".mid";
    mimeTypes["audio/x-midi"]                                                                    =   ".midi";
    mimeTypes["text/javascript"]                                                                 =   ".mjs";
    mimeTypes["audio/mpeg"]                                                                      =   ".mp3";
    mimeTypes["video/mpeg"]                                                                      =   ".mpeg";
    mimeTypes["video/mp4"]                                                                       =   ".mp4";
    mimeTypes["audio/ogg"]                                                                       =   ".oga";
    mimeTypes["video/ogg"]                                                                       =   ".ogv";
    mimeTypes["application/ogg"]                                                                 =   ".ogx";
    mimeTypes["audio/opus"]                                                                      =   ".opus";
    mimeTypes["font/otf"]                                                                        =   ".otf";
    mimeTypes["image/png"]                                                                       =   ".png";
    mimeTypes["application/pdf"]                                                                 =   ".pdf";
    mimeTypes["application/x-httpd-php"]                                                         =   ".php";
    mimeTypes["application/vnd.ms-powerpoint"]                                                   =   ".ppt";
    mimeTypes["application/vnd.rar"]                                                             =   ".rar";
    mimeTypes["application/rtf"]                                                                 =   ".rtf";
    mimeTypes["application/x-sh"]                                                                =   ".sh";
    mimeTypes["image/svg+xml"]                                                                   =   ".svg";
    mimeTypes["application/x-shockwave-flash"]                                                   =   ".swf";
    mimeTypes["application/x-tar"]                                                               =   ".tar";
    mimeTypes["image/tiff"]                                                                      =   ".tif";
    mimeTypes["image/tiff"]                                                                      =   ".tiff";
    mimeTypes["video/mp2t"]                                                                      =   ".ts";
    mimeTypes["font/ttf"]                                                                        =   ".ttf";
    mimeTypes["text/plain"]                                                                      =   ".txt";
    mimeTypes["application/vnd.visio"]                                                           =   ".vsd";
    mimeTypes["audio/wav"]                                                                       =   ".wav";
    mimeTypes["audio/webm"]                                                                      =   ".weba";
    mimeTypes["video/webm"]                                                                      =   ".webm";
    mimeTypes["image/webp"]                                                                      =   ".webp";
    mimeTypes["font/woff"]                                                                       =   ".woff";
    mimeTypes["font/woff2"]                                                                      =   ".woff2";
    mimeTypes["application/xhtml+xml"]                                                           =   ".xhtml";
    mimeTypes["application/vnd.ms-excel"]                                                        =   ".xls";
    mimeTypes["application/xml"]                                                                 =   ".xml";
    mimeTypes["application/vnd.mozilla.xul+xml"]                                                 =   ".xul";
    mimeTypes["archive  application/zip"]                                                        =   ".zip";
    mimeTypes["audio/video container  video/3gpp"]                                               =   ".3gp";
    mimeTypes["audio/video "]                                                                    =   ".3g2";
    mimeTypes["application/x-7z-compressed"]                                                     =   ".7z";
    mimeTypes["application/vnd.apple.installer+xml"]                                             =   ".mpkg";
    mimeTypes["application/vnd.oasis.opendocument.text"]                                         =   ".odt";
    mimeTypes["application/vnd.oasis.opendocument.presentation"]                                 =   ".odp";
    mimeTypes["application/vnd.oasis.opendocument.spreadsheet"]                                  =   ".ods";
    mimeTypes["application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"]               =   ".xlsx";
    mimeTypes["application/vnd.openxmlformats-officedocument.wordprocessingml.document"]         =   ".docx";
    mimeTypes["application/vnd.openxmlformats-officedocument.presentationml.presentation"]       =   ".pptx";
}

long GetFileSize(const char* filename)
{
    struct stat st;
    stat(filename, &st);

    return st.st_size;
}


std::string URLDecode(const std::string &url)
{
    std::string decoded;
    
    for (std::size_t i = 0; i < url.length(); ++i)
    {
        if (url[i] == '%')
        {
            int hexValue = stoi(url.substr(i + 1, 2), nullptr, 16);
            decoded += static_cast<char>(hexValue);
            i += 2;
        }
        else if (url[i] == '+')
            decoded += ' ';
        else
            decoded += url[i];
    }
    
    return decoded;
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

    if (resource.length())
    {
        std::string key;
        size_t      found = resource.find_last_of('.');

        if (found != std::string::npos)
            key = resource.substr(found, resource.length());

        if (found != std::string::npos && mimeTypes.count(key))
            response += "Content-Type: " + mimeTypes[key] + "\r\n";
        else
            response += "Content-Type: text/plain\r\n";


        resourceSize = GetFileSize(resource.data());

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
    response += "\r\n";

}

int IsUriValid(std::string &str)
{
    const std::string &allowed = ALLOWED_CHAR_IN_URI;
    for(size_t i = 0; i < str.size(); ++i)
        if (allowed.find(str[i]) == std::string::npos)
            return 0;
    try
    {
        str = URLDecode(str);
    }
    catch (...)
    {
        return 0;
    }
    return 1; 
}

int IsMethodValid(const std::string &method, const std::set<std::string> &allowedMethods)
{
    if (!allowedMethods.count(method))
        return 0;
    return 1; 
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

void runCGI()
{
    std::cout << "CGI\n" << std::endl;
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
    return FileName;
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
                this->chunked = std::stol(str, nullptr, 16);
                this->buffer = this->buffer.substr(loc + 2);
                if(!chunked)
                {
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
        uploadFile << str;
        loc = str.size();
        if (buffer.size() > this->chunked) loc += 2;
        if (buffer.size() < loc) loc = buffer.size();
        this->buffer = this->buffer.substr(loc);
        this->chunked -= str.size();
        this->bytesUploaded += str.size();
    }
}

void Client::boundaryUpload()
{
    std::string str;
    size_t loc;

    if (this->boundary == "")
        this->boundary = "--" + this->headerFields["content-type"].substr(30);

    if (buffer.substr(0, boundary.size()) == boundary)
    {
        if(buffer.substr(0, boundary.size() + 2) == boundary + "--")
        {
            uploadFile.close();
            setHeader(201);
            return ;
        }
        if (uploadFile.is_open())
            uploadFile.close();
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
        // std::cout << name << std::endl;
        loc = name.find("\"");
        this->uploadFile.open(this->location->getUpload() + name.substr(0, loc));
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
    uploadFile << str;
    buffer = buffer.substr(str.size() + loc);
    this->bytesUploaded += str.size();
}

void Client::upload()
{
    if (this->headerFields["content-type"].substr(0, 20) == "multipart/form-data;")
        return boundaryUpload();

    if (!this->bytesUploaded)
    {
        chunked = 0;
        std::string extention = initializeupload() + mimeTypes[this->headerFields["content-type"]];
        this->uploadFile.open(this->location->getUpload() + extention);
    }
    if (this->headerFields["transfer-encoding"] == "chunked")
        return chunkedUpload();
    std::string str;
    size_t ContentLength = stoi(this->headerFields["content-length"]);
    if (bytesUploaded == ContentLength)
    {
        setHeader(201);
        return ;
    }
    if (this->buffer.size() + bytesUploaded <= ContentLength)
        str = buffer;
    else
        str = buffer.substr(0, ContentLength - bytesUploaded);
    uploadFile << str;
    buffer = buffer.substr(str.size());
    this->bytesUploaded += str.size();
}

void Client::parse()
{
    std::list<std::string>              lines;
    std::list<std::string>::iterator    it;
    size_t                              first;

    lines = getlines(this->buffer);
    if (lines.empty())
        return ;

    for (it = lines.begin(); it != lines.end(); it++)
    {
        std::string &str = *it;

        if (str == "")
        {
            if (methodType == "GET")
                this->serve = &Client::GetHandler;
            else if (methodType == "POST")
                this->serve = &Client::PostHandler;
            else
                this->serve = &Client::DeleteHandler;

            return ;
        }
        if (this->methodType == "") 
        {
            int errorCode = 0;


            this->methodType = tok(str, " ");
            first = str.find_first_not_of(' ');
            str = str.substr(first);
            URI = tok(str, " ");


            if (!IsUriValid(URI))
                errorCode = 400;

            std::pair<std::string, Location*> loc = server.getMatchedLocation(URI);
            this->location = loc.second;


            if (!errorCode && !location)
                errorCode = 404;
            else
                this->resource = location->getRoot() + URI;
            if (!errorCode && location->getRedirection().first)
                errorCode = location->getRedirection().first;
            if (!errorCode && !IsMethodValid(methodType, location->getAllowedMethods()))
                errorCode = 405;
            if (!errorCode && URI.length() > MAX)
                errorCode = 414;


            first = str.find_first_not_of(' ');
            str = str.substr(first);
            if (!errorCode && tok(str, "\r\n") != "HTTP/1.1")
                errorCode = 505;
            if (errorCode)
            {
                setHeader(errorCode);
                return ;
            }
        }
        else
        {
            int             index = str.find(":");
            int             len   = str.length();
            std::string     name  = to_lower(str.substr(0, index));

            if (this->headerFields.count(name) or index == -1)
            {
                setHeader(400);
                return ;
            }
            std::string   val = str.substr(index + 1, len);
            headerFields [name] = trimString(val);
        }
    }
}

void Client::PostHandler()
{
    if (location->getUpload() != "")
    {
        serve = &Client::upload;
        
        return;
    }
    else if (!ft::isPathExists(resource))
        setHeader(404);
    if (ft::isDirectory(resource)) // create func
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

int deleteDir(const char* path)
{
    DIR* dir = opendir(path);

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        const char* filename = entry->d_name;
        if (ft::isDirectory(filename))
            if (!deleteDir(filename))
                return 0;
        if (std::remove(filename) != 0)
            return 0;
    }
    closedir(dir);
    return 1;
}

void    Client::DeleteHandler()
{
    if (ft::isFile(resource))
    {
        remove(resource.data());
        setHeader(204);
    }
    else if (deleteDir(resource.data()))
        setHeader(204);
    else if (access(resource.data(), W_OK))
        setHeader(500);
    else 
        setHeader(403);
}

void    Client::GetHandler()
{
    if (access(resource.data(), W_OK))
    {
        setHeader(404);
        return ;
    }
    if (ft::isDirectory(resource))
    {
        if (!hasSlash(resource))
        {
            setHeader(301);
            return ;
        }
        std::string filePath = resource;
        if(hasIndex(location->getIndex()))
                filePath += location->getIndex();
        if (!ft::isFile(filePath))
        {
            if (location->getAutoindex())
            {
                std::string name = "/tmp/" + initializeupload() + ".html";
                StringOfCurrentContent(resource, name, URI);
                resource = name;
                setHeader(200);
            }
            else
                setHeader(403);
            return ;
        }
        resource = filePath;
    }
    if (!location->locationHasCgi())
        setHeader(200);
    else
        runCGI();
}

void    Client::drop(fd_set &readMaster, fd_set &writeMaster)
{
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

