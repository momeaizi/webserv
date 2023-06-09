#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "ContextManager.hpp"




void    testParsing()
{
    try
    {
        ContextManager  manager("serv.conf"); 
        std::vector<Server> servers = manager.servers;

        for (int i = 0; i < servers.size(); ++i)
        {
            std::cout << "host " << servers[i].host << std::endl;
            std::cout << "port " << servers[i].port << std::endl;
            std::cout << "clientMaxBodySize " << servers[i].clientMaxBodySize << std::endl;

            std::map<std::string, Location>::iterator it = servers[i].locations.begin();

            for (; it != servers[i].locations.end(); ++it)
            {
                std::cout << "location " << it->first << std::endl;
                std::cout << "\tautoindex " << it->second.autoindex << std::endl;
                std::cout << "\troot " << it->second.root << std::endl;
                std::cout << "\tindex " << it->second.index << std::endl;
                std::cout << "\tupload " << it->second.upload << std::endl;
                std::cout << "\tredirection " << it->second.redirection.first << ", " << it->second.redirection.first << std::endl;
                std::cout << "allowed methods " << std::endl;

                std::set<std::string>::iterator it_ = it->second.allowedMethods.begin();
                for (; it_ != it->second.allowedMethods.end(); ++it_)
                    std::cout << '\t' << *it_ << std::endl;

                
                std::cout << "CGI" << std::endl;
                std::map<std::string, std::string>::iterator itt = it->second.cgi.begin();
                for (; itt != it->second.cgi.end(); ++itt)
                    std::cout << '\t' << itt->first << " " << itt->second << std::endl;
            }
            std::cout << "-----------------------------------------------------" << std::endl;
        }
        
    }
    catch(const char *e)
    {
        std::cerr << e << '\n';
    }
    catch(std::string e)
    {
        std::cerr << e << '\n';
    }
}

















int main()
{
    // testParsing();
    ContextManager  contextManager("serv.conf");
    std::vector<Server> &server = contextManager.servers;


    FD_ZERO(&master);

    for (int i = 0 ; i < server.size(); ++i)
    {
        server[i].createSocket();
    }

    for (int i = 0 ; i < server.size(); ++i)
    {
        server[i].startListening();
    }
    


    return 0;
}