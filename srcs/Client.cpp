# include "../includes/Client.hpp"
# include <dirent.h>
# include <cstdio>


std::map<int, std::string>  errorMes;

void    InitErrorMessage()
{
    errorMes[100] = "Continue";
    errorMes[101] = "Switching Protocols";
    errorMes[200] = "OK";
    errorMes[201] = "Created";
    errorMes[204] = "No Content";
    errorMes[301] = "Moved Permanently";
    errorMes[400] = "Bad Request";
    errorMes[401] = "Unauthorized";
    errorMes[403] = "Forbidden";
    errorMes[404] = "Not Found";
    errorMes[405] = "Method Not Allowed";
    errorMes[409] = "Conflict";
    errorMes[413] = "Request Entity Too Large";
    errorMes[414] = "Request_URI Too Long";
    errorMes[500] = "Internal Server Error";
    errorMes[501] = "Not Implemented";
    errorMes[505] = "HTTP Version Not Supported";
}

void Client::send_error(int error_status)
{
    response = "HTTP/1.1 " + std::to_string(error_status);
    response += errorMes[error_status];
}

int IsUriValid(std::string str)
{
    const std::string allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~!$&'()*+,;=:@/?#[]";
    for(size_t i = 0; i < str.size(); i++)
        if (allowed.find(str[i]) ==std::string::npos)
            return 0;
    return 1; 
}

int IsMethodValid(std::string method)
{
    std::set<std::string> allmethods;
    allmethods.insert("GET");
    allmethods.insert("DELETE");
    allmethods.insert("POSTE");
    if (!allmethods.count(method))
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
    char    buff[2000];
    if (Rfd == -1)
        Rfd = open(resource.data(), O_RDONLY);
    int  len = read(Rfd, buff, 2000);
    std::stringstream stream;
    stream << std::hex << len;
    this->response += stream.str();
    this->response += std::string(buff);
    if (len < 2000)
    {
        this->response += "0";
        phase = -1;
        close(Rfd);
    }
}

std::string  Client::initializeupload()
{
    std::string FileName;

    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    FileName = std::to_string(gmtm->tm_mday) + ":";
    FileName += std::to_string(gmtm->tm_mon + 1) + ":";
    FileName += std::to_string(1900 + gmtm->tm_year) + "_";
    FileName += std::to_string(gmtm->tm_hour + 5) + ":";
    FileName += std::to_string(gmtm->tm_min + 30) + ":";
    FileName += std::to_string(gmtm->tm_sec);
    // this->uploadFile.open(FileName);
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
        std::cout << "lines.size()" << lines.size() << " lines[0] : " << *it;
        std::string &str = *it;

        if (str == "")
        {
            std::cout << "parse is finished" << std::endl;
            this->phase = 0; // request is finished
            std::cout << "phase is changed -> " << this->phase << std::endl;
            return ;
        }
        if (this->methodType == "") 
        {
            this->methodType = tok(str, " ");
            if (!IsMethodValid(methodType)) send_error(405);
            first = str.find_first_not_of(' ');
            str = str.substr(first);
            URI = tok(str, " ");
            if (URI.size() > MAX)
            {
                send_error(414); // 
                return ;
            }
            if (!IsUriValid(URI)) send_error(400);
            first = str.find_first_not_of(' ');
            str = str.substr(first);
            if (tok(str, "\r\n") != "HTTP/1.1")
            {
                send_error(505);
                return ;
            }
        }
        else
        {
            int index = str.find(":");
            int len   = str.length();
            std::string   name = str.substr(0, index);

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
        send_error(201);
        upload();
    }
    else if (!ft::isPathExists(resource))
        send_error(404);
    if (ft::isDirectory(resource)) // create func
    {
        if (!hasSlash(resource))
        {
            send_error(301);
            return ;
        }
        std::string filePath = resource;
        if (hasIndex(location->getIndex()))
            filePath += location->getIndex();
        else
            filePath += "index.html";
        if (!ft::isFile(filePath))
        {
            send_error(403);
            return ;
        }
        resource = filePath;
    }
    if (!location->locationHasCgi())
        send_error(403);
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
        send_error(204);
    }
    else if (deleteDir(resource.data()))
        send_error(204);
    else if (access(resource.data(), W_OK))
        send_error(500);
    else 
        send_error(403);
}

void    Client::GetHandler()
{
    if (this->buffer == "")
    {
        send_error(404);
        return ;
    }
    if (ft::isDirectory(resource))
    {
        if (!hasSlash(resource))
        {
            send_error(301);
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
                send_error(200);
            else
                send_error(403);
            return ;
        }
        resource = filePath;
    }
    if (!location->locationHasCgi())
        send_error(200);
    else runCGI();
}

void    Client::drop()
{
    // close(clSocket);
    // FD_CLR(clSocket, &readmaster);
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