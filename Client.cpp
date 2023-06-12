#include "Client.hpp"
#include "string.hpp"
#include "errors.hpp"
#include <sys/socket.h>
#include <fstream> // remove
#include <string>
#include <iostream>


#define MAX 2043




void IsUriValid(std::string str)
{
    const std::string allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~!$&'()*+,;=:@/?#[]";
    for(int i = 0; i < str.size(); i++)
        if (allowed.find(str[i]) == -1)
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


void Client::parse()
{

    std::string str;
    std::string buffer;
    std::vector<std::string> lines;
    std::vector<std::string>::iterator it;
    size_t first;

    lines = getlines(0);
    if (lines.empty())
        return ;
    for (it = lines.begin(); it != lines.end(); it++)
    {
        str = *it;
        if (str == "")
        {
            buffer = getRemainder();
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

void PostMetod()
{

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