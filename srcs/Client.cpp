# include "../includes/Client.hpp"
# include <dirent.h>
# include <cstdio>


std::map<int, std::string>          statusCode;
std::map<std::string, std::string>  mimeTypes;


void    InitstatusCodesage()
{
    statusCode[100] = "Continue";
    statusCode[101] = "Switching Protocols";
    statusCode[200] = "OK";
    statusCode[201] = "Created";
    statusCode[204] = "No Content";
    statusCode[301] = "Moved Permanently";
    statusCode[400] = "Bad Request";
    statusCode[401] = "Unauthorized";
    statusCode[403] = "Forbidden";
    statusCode[404] = "Not Found";
    statusCode[405] = "Method Not Allowed";
    statusCode[409] = "Conflict";
    statusCode[413] = "Request Entity Too Large";
    statusCode[414] = "Request_URI Too Long";
    statusCode[500] = "Internal Server Error";
    statusCode[501] = "Not Implemented";
    statusCode[505] = "HTTP Version Not Supported";
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
    FILE* file = fopen(filename, "rb"); // Open the file in binary mode

    if (file != NULL)
    {
        fseek(file, 0, SEEK_END); // Seek to the end of the file
        long size = ftell(file);  // Get the current position, which is the size of the file
        fclose(file);             // Close the file
        return size;
    }

    return -1; // Return -1 to indicate an error occurred
}


void Client::setHeader(int error_status)
{
    response = "HTTP/1.1 " + std::to_string(error_status) + " " + statusCode[error_status] + "\r\n";

    // if (error_status >= 300)
    // {
    //     resource = path/error_status.html;
    // }

    if (resource.length())
    {
        size_t  found = resource.find_last_of('.');
        if (found != std::string::npos)
            response += "Content-Type: " + mimeTypes[resource.substr(found, resource.length())] + "\r\n";
        else
            response += "Content-Type: text/plain\r\n";


        long    fileSize = GetFileSize(resource.data());
        std::cout << "************* " << fileSize << std::endl;
        std::cout << "************* " << resource << std::endl;
        if (fileSize < 2048)
            response += "Content-Length: " + std::to_string(fileSize) + "\r\n";
        else
            response += "Transfer-Encoding: chunked\r\n";
        


    }


}

int IsUriValid(std::string str)
{
    const std::string allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~!$&'()*+,;=:@/?#[]";
    for(size_t i = 0; i < str.size(); i++)
        if (allowed.find(str[i]) ==std::string::npos)
            return 0;
    return 1; 
}

int IsMethodValid(const std::string &method, const std::set<std::string> &allowedMethods)
{
    if (!allowedMethods.count(method))
        return 0;
    return 1; 
}

bool hasSlash(std::string resource)
{
    int index;

    index = resource.length() - 1;
    return (resource[index] == '/');
}

bool hasIndex(std::string index)
{
    return (index == "");
}

void runCGI()
{

}


void Client::GetFromFile()
{
    char    buff[BUFFER_SIZE];
    if (Rfd == -1)
        Rfd = open(resource.data(), O_RDONLY);
    struct stat st;
    stat(resource.data(), &st);
    int  len = read(Rfd, buff, 2048);
    if (st.st_size > BUFFER_SIZE)
    {
        std::stringstream stream;
        stream << std::hex << len;
        this->response += stream.str();
    }
    this->response += "\r\n"+std::string(buff);
    if (len < BUFFER_SIZE)
    {
        if (st.st_size > BUFFER_SIZE)
            this->response += "0";
        phase = -1;
        close(Rfd);
    }
}

std::string  Client::initializeupload()
{
    std::string FileName;

    time_t now = time(NULL);
    tm *gmtm = gmtime(&now);
    FileName = std::to_string(gmtm->tm_mday) + ":";
    FileName += std::to_string(gmtm->tm_mon + 1) + ":";
    FileName += std::to_string(1900 + gmtm->tm_year) + "_";
    FileName += std::to_string(gmtm->tm_hour + 5) + ":";
    FileName += std::to_string(gmtm->tm_min + 30) + ":";
    FileName += std::to_string(gmtm->tm_sec);
    return FileName;
}

void Client::upload()
{
    if (!this->bytesUploaded)
        this->uploadFile.open(initializeupload());

    std::ifstream inputFile("filename.txt"); // recv
    // inputFile.seekg(this->seekg + 6, std::ios::cur); // recv


    std::string                         str;
    char                                buffer[1024];
    size_t ContentLength = stoi(this->headerFields["Content-Length"]);
    size_t                              bytes = 1024;
    if (bytesUploaded >= ContentLength)
        return ;
    if (ContentLength - bytesUploaded < 1024) bytes = ContentLength -  str.size();
    inputFile.read(buffer, bytes);
    str   = std::string(buffer, bytes);
    bytesUploaded += bytes;
    if (bytesUploaded > ContentLength)
    {
        this->buffer = str.substr(ContentLength);
        str = str.substr(0, ContentLength);
    }
    uploadFile << str;
    uploadFile.close();
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
                serve = &Client::GetHandler;
            else if (methodType == "POST")
                serve = &Client::PostHandler;
            else
                serve = &Client::DeleteHandler;


            // this->phase = -1;









            return ;
        }

        
        if (this->methodType == "") 
        {
            this->methodType = tok(str, " ");
            first = str.find_first_not_of(' ');
            str = str.substr(first);
            URI = tok(str, " ");

            std::pair<std::string, Location*> loc = server.getMatchedLocation(URI);
            this->location = loc.second;
            if (!location)
            {
                setHeader(404);
                return ;
            }
            
            if (!IsMethodValid(methodType, location->getAllowedMethods()))
            {
                setHeader(405);
                return ;
            }

            if (URI.length() > MAX)
            {
                setHeader(414); // 
                return ;
            }
            if (!IsUriValid(URI))
            {
                setHeader(400);
                return ;
            }

            this->resource = location->getRoot() + URI;
            first = str.find_first_not_of(' ');
            str = str.substr(first);
            if (tok(str, "\r\n") != "HTTP/1.1")
            {
                setHeader(505);
                return ;
            }
        }
        else
        {
            int             index = str.find(":");
            int             len   = str.length();
            std::string     name  = to_lower(str.substr(0, index));

            if (this->headerFields.count(name) and index == -1)
                return ;// send_400();
            std::string   val = str.substr(index + 1, len);
            headerFields [name] = trimString(val);
        }
    }
}

void Client::PostHandler()
{
    if (location->getUpload() != "")
    {
        setHeader(201);
        upload();
    }
    else if (!ft::isPathExists(resource))
        setHeader(404);
    if (ft::isDirectory(resource)) // create func
    {
        if (!hasSlash(resource))
        {
            setHeader(301);
            return ;
        }
        std::string filePath = resource;
        if (hasIndex(location->getIndex()))
            filePath += location->getIndex();
        else
            filePath += "index.html";
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
    if (this->buffer == "")
    {
        // resource = 400.html;
        setHeader(404);
        return ;
    }
    if (ft::isDirectory(resource))
    {
        if (!hasSlash(resource))
        {
            // resource = 301.html;
            setHeader(301);
            return ;
        }
        std::string filePath = resource;
        if(hasIndex(location->getIndex()))
                filePath += location->getIndex();
        else
                filePath += "index.html";
        if (!ft::isFile(filePath))
        {
            if (location->getAutoindex())
            {
                std::string name = resource + initializeupload() +"autoindex.html";
                StringOfCurrentContent(resource, name);
                resource = name;
                send_error(200);
            }
            else
                setHeader(403);
            return ;
        }
        resource = filePath;
    }
    if (!location->locationHasCgi())
    {
        //getfrom file
        setHeader(200);
    }
    else runCGI();
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
    Rfd = -1;
    bytesUploaded = 0;
    uploadFile.close();
    uploadFile.clear();
    methodType.clear();
    URI.clear();
    resource.clear();
    headerFields.clear();
    location = NULL;
}


// int main()
// {
//     Client obj;
//     while (obj.phase)
//         obj.parse();
//     obj.upload();
//     std:: cout << std::endl << "RESPONS" << std::endl;
//     std:: cout << "_________________" << std::endl;
//     std::cout << "method is : " <<  obj.methodType << std::endl << "URI: " << obj.URI << " " << std::endl;
//     std:: cout << "_________________" << std::endl;
//     for(auto& el:obj.headerFields)
//         std::cout << el.first << "\n" << el.second << std::endl<< std::endl;
// }