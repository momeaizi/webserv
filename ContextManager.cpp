#include "ContextManager.hpp"



ContextManager::ContextManager(const char *configFileName) : configFIle(configFileName)
{
    if (!configFIle.is_open())
        throw "config file can't be opened!";
    
    lineNumber = 0;
    parseConfigFIle();
    
}

int    ContextManager::parseLocation(Location &location)
{


    while (std::getline(configFIle, buff))
    {
        ++lineNumber;

        if (!buff.length() || containsOnlyWhitespaces(buff))
            continue ;


        tokens = splitString(buff, ' ');

        if (tokens[0] == "\t\troot")
        {
            if (tokens.size() != 2)
                throw "invalid number of arguments in \"root\" directive in serv.conf:" + std::to_string(lineNumber);
            location.root = tokens[1];
        }   // SET ROOT ATTRIBUTE OF THE SERVER

        else if (tokens[0] == "\t\tindex")
        {
            if (tokens.size() != 2)
                throw "invalid number of arguments in \"index\" directive in serv.conf:" + std::to_string(lineNumber);
            location.index = tokens[1];
        }   // SET INDEX ATTRIBUTE OF THE SERVER

        else if (tokens[0] == "\t\tupload_pass")
        {
            if (tokens.size() != 2)
                throw "invalid number of arguments in \"upload_pass\" directive in serv.conf:" + std::to_string(lineNumber);
            location.upload = tokens[1];
        }   // SET UPLOAD ATTRIBUTE OF THE SERVER

        else if (tokens[0] == "\t\tcgi_pass")
        {
            if (tokens.size() != 3)
                throw "invalid number of arguments in \"cgi_pass\" directive in serv.conf:" + std::to_string(lineNumber);
            location.cgi[tokens[1]] = tokens[2];
        }   // SET CGI ATTRIBUTE OF THE SERVER

        else if (tokens[0] == "\t\tautoindex")
        {
            if (tokens.size() != 2)
                throw "invalid number of arguments in \"tautoindex\" directive in serv.conf:" + std::to_string(lineNumber);
            if (tokens[1] != "on" && tokens[1] != "off")
                throw "argumnet of autoindex should be on or off";
            location.autoindex = (tokens[1].size() == 2) ? true : false;
        }   // SET AUTOINDEX ATTRIBUTE OF THE SERVER

        else if (tokens[0] == "\t\tallow_methods")
        {
            if (tokens.size() < 2)
                throw "invalid number of arguments in \"client_max_body_size\" directive in serv.conf:" + std::to_string(lineNumber);
            for (size_t  i = 1; i < tokens.size(); ++i)
                location.allowedMethods.insert(tokens[i]);
        }   // SET ALLOWEDMETHODS ATTRIBUTE OF THE SERVER

        else if (tokens[0] == "\t\treturn")
        {
            if (tokens.size() != 3)
                throw "invalid number of arguments in \"client_max_body_size\" directive in serv.conf:" + std::to_string(lineNumber);
            location.redirection = make_pair(atoi(tokens[1].c_str()), tokens[2]);
        }   // SET REDIRECCTION  ATTRIBUTE OF THE SERVER

        else
            return 1;
    }
    return 0;

}

int     ContextManager::parseServer()
{
    if (buff == "server")
    {
        servers.push_back(Server());
        return 1;
    }
    
    if (!servers.size())
        throw "unknown directive in serv.conf:" + std::to_string(lineNumber);
    else if (tokens[0] == "\tlocation")
    {
        if (tokens.size() != 2)
            throw "invalid number of arguments in \"location\" directive in serv.conf:" + std::to_string(lineNumber);

        if (!servers.back().host.length())
            throw "provide a host first";

        if (!parseLocation(servers.back().locations[tokens[1]]))
            return 0;
        parseServer();
        return 1;
    }

    if (tokens[0] == "\thost")
    {
        if (tokens.size() != 2)
            throw "invalid number of arguments in \"host\" directive in serv.conf:" + std::to_string(lineNumber);
        servers.back().host = tokens[1];
    }
    else if (tokens[0] == "\tport")
    {
        if (tokens.size() != 2)
            throw "invalid number of arguments in \"port\" directive in serv.conf:" + std::to_string(lineNumber);
        servers.back().port = tokens[1];
    }
    else if (tokens[0] == "\tclient_max_body_size")
    {
        if (tokens.size() != 2)
            throw "invalid number of arguments in \"client_max_body_size\" directive in serv.conf:" + std::to_string(lineNumber);
        servers.back().clientMaxBodySize = atol(tokens[1].c_str());
    }
    else if (tokens[0] == "\terror_page")
    {
        if (tokens.size() != 3)
            throw "invalid number of arguments in \"error_page\" directive in serv.conf:" + std::to_string(lineNumber);
        servers.back().errorPages[atoi(tokens[1].c_str())] = tokens[1];
    }
    else
        throw "unknown directive in serv.conf:" + std::to_string(lineNumber);
    return 1;
}


void    ContextManager::parseConfigFIle()
{
    while (std::getline(configFIle, buff))
    {
        ++lineNumber;

        if (!buff.length() || containsOnlyWhitespaces(buff))
            continue ;

        tokens = splitString(buff, ' ');


        if (!parseServer())
            return ;
    }

}
