#include "../includes/Client.hpp"

# include <dirent.h>
# include <cstdio>


void IsUriValid(std::string str)
{
    const std::string allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~!$&'()*+,;=:@/?#[]";
    for(size_t i = 0; i < str.size(); i++)
        if (allowed.find(str[i]) ==std::string::npos)
            send_400(); 
}

void IsMethodValid(std::string method)
{
    std::set<std::string> allmethods;
    allmethods.insert("GET");
    allmethods.insert("DELETE");
    allmethods.insert("POSTE");
    if (!allmethods.count(method)) send_405(); 
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
    return FileName;
}

void Client::upload()
{
    if (!this->bytesUploaded)
        this->uploadFile.open(initializeupload());

    std::string                         str;
    size_t ContentLength = stoi(this->headerFields["Content-Length"]);
    if (bytesUploaded >= ContentLength)
    {
        uploadFile.close();
        phase = 2;
        return ;
    }
    if (this->buffer.size() + bytesUploaded <= ContentLength)
        str = buffer;
    else
        str = buffer.substr(0, ContentLength - bytesUploaded);
    uploadFile << str;
    buffer = buffer.substr(str.size());
}

void Client::GetFromFile()
{
    char    buff[1024];
    int     Rfd = open(resource.data(), O_RDONLY);
    int  len = read(Rfd, buff, 1024);
    if (len == -1) write(fd, buff, len);
}


void Client::parse()
{
    std::string str;
    std::list<std::string> lines;
    std::list<std::string>::iterator it;
    size_t first;

    lines = getlines(this->buffer);
    if (lines.empty())
        return ;
    for (it = lines.begin(); it != lines.end(); it++)
    {
        str = *it;
        this->seekg += str.size() + 2;
        if (str == "")
        {
            phase = 0; // request is finished
            return ;
        }
        if (this->methodType == "") 
        {
            this->methodType = tok(str, " ");
            IsMethodValid(methodType);
            first = str.find_first_not_of(' ');
            str = str.substr(first);
            URI = tok(str, " ");
            if (URI.size() > MAX)
                send_414(); // 
            IsUriValid(URI);
            first = str.find_first_not_of(' ');
            str = str.substr(first);
            if (tok(str, "\r\n") != "HTTP/1.1")
                send_505();
        }
        else
        {
            int index = str.find(":");
            int len = str.length();
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
        upload();
        send_201();
    }
    if (!ft::isPathExists(resource))
        send_404();
    if (ft::isDirectory(resource)) // create func
    {
        if (!hasSlash(resource))
            send_301();
        std::string filePath = resource;
        if (hasIndex(location->getIndex()))
            filePath += location->getIndex();
        else
            filePath += "index.html";
        if (!ft::isFile(filePath))
            send_403();
        resource = filePath;
    }
    if (!location->locationHasCgi())
        send_403();
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
        send_204();
    }
    if (deleteDir(resource.data()))
        send_204();
    if (access(resource.data(), W_OK))
        send_500();
    send_403();
}

void    Client::GetHandler()
{
    if (getResource() == "") send_404();
    if (ft::isDirectory(resource))
    {
        if (!hasSlash(resource))
            send_301();
        std::string filePath = resource;
        if(hasIndex(location->getIndex()))
                filePath += location->getIndex();
        else
                filePath += "index.html";
        if (!ft::isFile(filePath))
        {
            if (location->getAutoindex())
                send_200();
            send_403();
        }
        resource = filePath;
    }
    if (!location->locationHasCgi())
        send_200();
    runCGI();
}

void    Client::drop()
{
    close(clSocket);
    FD_CLR(clSocket, &master);
}

    // resource = "/Users/mskerba/Desktop/tes.cpp";
    // fd = open("/Users/mskerba/Desktop/b",O_WRONLY);

// int main()
// {
//     Client obj;
//     obj.GetFromFile();
// }