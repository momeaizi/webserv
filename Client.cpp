#include "Client.hpp"
#include <sys/socket.h>
#include <fstream> // remove
#include <string>
#include <iostream>


#define MAX 2043
#define buf 1024


void send_414()
{
    std::cout << "error  414 Request_URI Too Long!!!" << std::endl;
    exit(0);
}

void send_505()
{
    std::cout << "error  505 !!!" << std::endl;
    exit(0);
}

void send_400()
{
    std::cout << "error  400 Bad Request !!!" << std::endl;
    exit(0);
}

std::string tok(std::string &str, std::string sep)
{
    std::string sepstring;
    int loc = str.find(sep);
    sepstring = str.substr(0, loc);
    str = str.substr(loc + sep.size());
    return sepstring;
}

std::vector<std::string> getlines(int phase)
{
    static std::string        str;
    static size_t             seekg = 0;                
    std::string               sep;
    std::vector<std::string>  lines;
    char                      buffer[1024];
    std::size_t               loc = 0;
    int                       bytes;
    int                       fd;

    if (phase)
    {
        lines.push_back(str);
        return lines;
    }
    // bytes  = recv(fd, buffer, (size_t)buf);
    std::ifstream inputFile("filename.txt");
    bytes = buf;
    inputFile.seekg(seekg, std::ios::cur);
    inputFile.read(buffer, bytes);
    seekg += bytes;
    str   += std::string(buffer, bytes);
    sep   = "\\r\n";
    loc   = str.find(sep);
    while (loc != std::string::npos)
    {
        lines.push_back(tok(str, sep));
        if (lines.back() == "")
            break ;
        loc = str.find(sep);
    }

    return lines;
}

void IsUriValid(std::string str)
{
    const std::string allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~!$&'()*+,;=:@/?#[]";
    for(int i = 0; i < str.size(); i++)
        if (allowed.find(str[i]) == -1)
            send_400(); 
}


std::string getRemainder()
{
    return getlines(1)[0];
}

void Client::parse()
{

    std::string str;
    std::string buffer;
    std::vector<std::string> lines;
    std::vector<std::string>::iterator it;

    lines = getlines(0);
    if (lines.empty())
        return ;
    for (it = lines.begin(); it != lines.end(); it++)
    {
        str = *it;
    std::cout << str << std::endl;
        if (str == "")
        {
            buffer = getRemainder();
            phase = 0; // request is finished
            return ;
        }
        if (this->methodType == "") 
        {
            this->methodType = tok(str, " ");
            URI = tok(str, " ");
            if (URI.size() > MAX)
                send_414(); // 
            IsUriValid(URI);
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
            headerFields [name] = trim(val, " ");
        }
    }
}
int main()
{
    Client obj;
    int i = 0;
    while (obj.phase)
        obj.parse();
    std:: cout << std::endl << "RESPONS" << std::endl;
    std:: cout << "_________________" << std::endl;
    std::cout << "method is : " <<  obj.methodType << std::endl << "URI: " << obj.URI << " " << std::endl;
    std:: cout << "_________________" << std::endl;
    for(auto& el:obj.headerFields)
        std::cout << el.first << "\n" << el.second << std::endl<< std::endl;
}