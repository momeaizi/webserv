#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include "ContextManager.hpp"
#include "Server.hpp"
#include "Client.hpp"


fd_set          master;
int             max_socket;

void    testParsing()
{
    try
    {
        ContextManager  manager("serv.conf"); 
        std::vector<Server> servers = manager.servers;

        std::cout << servers.size() << std::endl;
        for (size_t i = 0; i < servers.size(); ++i)
        {
            std::cout << "host " << servers[i].hostName << std::endl;
            std::cout << "port " << servers[i].port << std::endl;
            std::cout << "size : " << servers[i].hosts.size() << std::endl;
            std::map<std::string, Host>::iterator it = servers[i].hosts.begin();
            for (; it != servers[i].hosts.end(); ++it)
            {
                std::cout << "Host host " << it->first << std::endl;
                std::cout << "clientMaxBodySize " << it->second.clientMaxBodySize << std::endl;

                std::map<std::string, Location>::iterator it_ = it->second.locations.begin();

                for (; it_ != it->second.locations.end(); ++it_)
                {
                    std::cout << "location " << it_->first << std::endl;
                    std::cout << "\tautoindex " << it_->second.autoindex << std::endl;
                    std::cout << "\troot " << it_->second.root << std::endl;
                    std::cout << "\tindex " << it_->second.index << std::endl;
                    std::cout << "\tupload " << it_->second.upload << std::endl;
                    std::cout << "\tredirection " << it_->second.redirection.first << ", " << it->second.redirection.first << std::endl;
                    std::cout << "\tallowed methods " << std::endl;

                    std::set<std::string>::iterator it__ = it->second.allowedMethods.begin();
                    for (; it__ != it->second.allowedMethods.end(); ++it__)
                        std::cout << "\t\t" << *it__ << std::endl;

                    
                    std::cout << "\tCGI" << std::endl;
                    std::map<std::string, std::string>::iterator itt = it_->second.cgi.begin();
                    for (; itt != it_->second.cgi.end(); ++itt)
                        std::cout << "\t\t" << itt->first << " " << itt->second << std::endl;


                    std::cout << "\tError Pages" << std::endl;
                    std::map<int, std::string>::iterator it___ = it->second.errorPages.begin();
                    for (; it___ != it->second.errorPages.end(); ++it___)
                        std::cout << "\t\t" << it___->first << " " << it___->second << std::endl;
                }
                std::cout << "*************************Host-End*********************" << std::endl;
            }
            std::cout << "----------------------------Server-End------------------------------------------------------" << std::endl;
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


    try
    {
        ContextManager  contextManager("serv.conf");
        std::vector<Server> &server = contextManager.servers;
        std::list<Client>   clients;
        fd_set  reads;
        fd_set  writes;


        FD_ZERO(&master);

        for (size_t i = 0 ; i < server.size(); ++i)
        {
            server[i].createSocket();
        }

        for (size_t i = 0 ; i < server.size(); ++i)
        {
            server[i].startListening();
        }

        while (26)
        {
            reads = master;
            writes = master;

            if (select(max_socket + 1, &reads, &writes, 0, 0) < 0)
                throw "select() failed. " + std::to_string(errno);

    
            for (size_t i = 0; i < server.size(); ++i)
            {
                if (FD_ISSET(server[i].socket_listen, &reads))
                {
                    server[i].acceptClient(clients, i);
                    std::cout << "socket : " << clients.back().clSocket << std::endl;
                }
            }

            for (std::list<Client>::iterator it = clients.begin(); it != clients.end();)
            {

                if (FD_ISSET(it->clSocket, &reads))
                {
                    std::cout << it->ipAddress << std::endl;
                    char    read[1024];
                    int     bytes_received = recv(it->clSocket, read, 1024, 0);
                    if (bytes_received < 0)
                    {
                        FD_CLR(it->clSocket, &master);
                        close(it->clSocket);
                        clients.erase(it++);
                        ++it;
                        continue ;
                    }

                    std::cout << " ---- Request Begin ---" <<  std::endl;
                    std::cout << read << std::endl;
                    std::cout << " ---- Request End  ---" <<  std::endl;

                }
                else if (FD_ISSET(it->clSocket, &writes))
                {

                    char buff[] =    "HTTP/1.1 200 OK\r\n"
                                "Server: Allah Y7ssen L3wan\r\n"
                                "Content-Length: 12\r\n"
                                "Content-Type: text/plain\r\n\r\n"
                                "HELLO WORLD!";
                    if (send(it->clSocket, buff, sizeof(buff), 0) < 0)
                        perror("Send -> ");
                }
                ++it;
            }
        }



    }
    catch(const char *e)
    {
        std::cerr << e << std::endl;
    }
    catch(std::string e)
    {
        std::cerr << e << std::endl;
    }

    return 0;
}