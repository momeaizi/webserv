#include "Client.hpp"
#include <sys/socket.h>

#define MAX 2043
#define buf 1024

std::vector<std::string> getline(int phase)
{

    static                    std::string str;
    char                      buffer[1024];
    std::vector<std::string>  lines;
    int                       loc;
    int                       bytes;
    int                       fd;

    if (phase) return {str};
    bytes  = recv(fd, buffer, (size_t)buf);
    str   += std::string(buffer, bytes);
    loc  = str.find("\r\n");

    while (loc != -1)
    {
        loc = str.find("\r\n");
        lines.push_back(std::string(str, loc));
        str.erase(0, loc);
        // str = std::string(str.ptr + loc + 2, str.size() - loc);
        if (lines.back() == "")
            break ;
    }
    return lines;
}

std::string tok(std::string &str, std::string sep)
{
    std::string sepstring;
    int loc = str.find(sep);
    sepstring = std::string(str, loc);
    str = str.substr(loc);
    return sepstring;
}

void Client::parse()
{
    std::string str;
    std::string buffer;
    std::vector<std::string> lines;
    std::vector<std::string>::iterator it;

    lines = getline(0);
    if (lines.empty())
        return ;
    for (it = lines.begin(); it != lines.end(); it++)
    {
        str = *it;
        if (str == "")
        {
            buffer = getline(1)[0];
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
              if (this->headerFields.count(name))
                  send_400();
              std::string   val = str.substr(index, len);
              headerFields [name] = val;//val.trim(" ");
        }
    }
}