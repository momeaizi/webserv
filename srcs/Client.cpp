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
