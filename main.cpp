#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "Server.hpp"
#include "Location.hpp"








std::string trimString(const std::string &str)
{

    std::string::const_iterator     start = str.begin();
    std::string::const_iterator     end = str.end();

    do
        --end;
    while (end != start && std::isspace(*end));

    return std::string(start, end + 1);
}


std::vector<std::string> splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> substrings;
    std::string substring;

    std::size_t start = 0;
    std::size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        if (start != end)
        {
            substring = str.substr(start, end - start);
            substrings.push_back(substring);
        }
        start = end + 1;
        end = str.find(delimiter, start);
    }


    substring = str.substr(start);
    substrings.push_back(substring);

    return substrings;
}

void    parseLocation(std::ifstream &configFIle, std::string &buff, Location &location)
{
    std::vector<std::string>    tokens;



    while (!configFIle.eof())
    {
        std::getline(configFIle, buff);
        if (!buff.length())
            continue ;

        buff = trimString(buff); // temp



        tokens = splitString(buff, ' ');


    }


}


void    parseConfigFIle(std::ifstream &configFIle, std::vector<Server> &servers)
{
    std::string                 buff;
    std::vector<std::string>    tokens;
    Location                    locaton;


    while (!configFIle.eof())
    {
        std::getline(configFIle, buff);
        if (!buff.length())
            continue ;

        buff = trimString(buff); // temp



        tokens = splitString(buff, ' ');

        if (servers.size())
        {
            if (tokens[0] == "\tlocation")
            {
                if (servers.back().host.length())
                    parseLocation(configFIle, buff, locaton);
            }

            if (tokens[0] == "\thost")
                servers.back().host = tokens[1];
            else if (tokens[0] == "\tport")
                servers.back().port = tokens[1];
            else if (tokens[0] == "\tclient_max_body_size")
                servers.back().clientMaxBodySize = atoi(tokens[1].c_str());
        }



        if (buff == "server")
        {
            servers.push_back(Server());
            continue ;
        }
    }

}




int main()
{
    std::ifstream               configFIle("serv.conf");
    std::vector<Server>         servers;

    parseConfigFIle(configFIle, servers);

    for (int  i = 0; i < servers.size(); ++i)
        std::cout << servers[i].host << std::endl;

    return 0;
}