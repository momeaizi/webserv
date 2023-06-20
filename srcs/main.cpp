
#include "../includes/ContextManager.hpp"

fd_set  readMaster;
fd_set  writeMaster;
// void    testParsing()
// {
//     try
//     {
//         ContextManager  manager; 
//         std::vector<Server> servers = manager.servers;

//         std::cout << servers.size() << std::endl;
//         for (size_t i = 0; i < servers.size(); ++i)
//         {
//             std::cout << "host " << servers[i].getHostName() << std::endl;
//             std::cout << "port " << servers[i].getPort() << std::endl;
//             std::cout << "size : " << servers[i].getConfigAttrs().size() << std::endl;
//             std::map<std::string, ConfigAttr>::const_iterator it = servers[i].getConfigAttrs().begin();
//             for (; it != servers[i].getConfigAttrs().end(); ++it)
//             {
//                 std::cout << "Host host " << it->first << std::endl;
//                 std::cout << "clientMaxBodySize " << it->second.getClientMaxBodySize() << std::endl;

//                 std::map<std::string, Location>::const_iterator it_ = it->second.getLocations().begin();

//                 for (; it_ != it->second.getLocations().end(); ++it_)
//                 {
//                     std::cout << "location " << it_->first << std::endl;
//                     std::cout << "\tautoindex " << it_->second.getAutoindex() << std::endl;
//                     std::cout << "\troot " << it_->second.getRoot() << std::endl;
//                     std::cout << "\tindex " << it_->second.getIndex() << std::endl;
//                     std::cout << "\tupload " << it_->second.getUpload() << std::endl;
//                     std::cout << "\tredirection " << it_->second.getRedirection().first << ", " << it_->second.getRedirection().second << std::endl;
//                     std::cout << "\tallowed methods " << std::endl;

//                     std::set<std::string>::iterator it__ = it_->second.getAllowedMethods().begin();
//                     for (; it__ != it_->second.getAllowedMethods().end(); ++it__)
//                         std::cout << "\t\t" << *it__ << std::endl;

                    
//                     std::cout << "\tCGI" << std::endl;
//                     std::map<std::string, std::string>::const_iterator itt = it_->second.getCgi().begin();
//                     for (; itt != it_->second.getCgi().end(); ++itt)
//                         std::cout << "\t\t" << itt->first << " " << itt->second << std::endl;


//                     std::cout << "\tError Pages" << std::endl;
//                     std::map<int, std::string>::const_iterator it___ = it->second.getErrorPages().begin();
//                     for (; it___ != it->second.getErrorPages().end(); ++it___)
//                         std::cout << "\t\t" << it___->first << " " << it___->second << std::endl;
//                 }
//                 std::cout << "*************************Host-End*********************" << std::endl;
//             }
//             std::cout << "----------------------------Server-End------------------------------------------------------" << std::endl;
//         }
        
//     }
//     catch(const char *e)
//     {
//         std::cerr << e << '\n';
//     }
//     catch(std::string e)
//     {
//         std::cerr << e << '\n';
//     }
// }















int main()
{
    // testParsing();

    InitstatusCodesage();
    mimeTypesInitializer();
    try
    {
        ContextManager  http;


        http.openAndListen();
        http.ioMultiplexer();




    }
    catch(const char *e)
    {
        std::cerr << e << std::endl;
    }
    catch(std::string e)
    {
        std::cerr << e << std::endl;
    }

    return errno;
}