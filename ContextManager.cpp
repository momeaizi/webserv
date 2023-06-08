#include "ContextManager.hpp"



ContextManager::ContextManager(const char *configFileName) : configFIle(configFileName)
{
    if (!configFIle.is_open())
        throw "config file can't be opened!";
    
    parseConfigFIle();
    
}

void    ContextManager::parseLocation(Location &location)
{


    while (!configFIle.eof())
    {
        std::getline(configFIle, buff);
        if (!buff.length())
            continue ;


        tokens = splitString(buff, ' ');

        if (tokens[0] == "\t\troot")
        {
            location.root = tokens[1];
        }
        else if (tokens[0] == "\t\tindex")
        {
            location.index = tokens[1];
        }
        else if (tokens[0] == "\t\tupload_pass")
        {
            location.upload = tokens[1];
        }
        else if (tokens[0] == "\t\tcgi_pass")
        {
            location.cgi[tokens[1]] = tokens[2];
        }
        else if (tokens[0] == "\t\tautoindex")
        {
            if (tokens[1] != "on" && tokens[1] != "off")
                throw "argumnet of autoindex should be on or off";
            location.autoindex = (tokens[1].size() == 2) ? true : false;
        }
        else if (tokens[0] == "\t\tallow_methods")
        {
            for (int  i = 1; i < tokens.size(); ++i)
                location.allowedMethods.insert(tokens[i]);
        }
        else if (tokens[0] == "\t\treturn")
        {
            if (tokens.size() != 3)
                throw "wrong nummber of arguments";
            location.redirection = make_pair(atoi(tokens[1].c_str()), tokens[2]);
        }
    }

}


void    ContextManager::parseConfigFIle()
{
    while (!configFIle.eof())
    {
        std::getline(configFIle, buff);



        if (!buff.length())
            continue ;



        tokens = splitString(buff, ' ');

        if (servers.size())
        {
            if (tokens[0] == "\tlocation")
            {
                if (!servers.back().host.length())
                    throw "provide a host first";

                parseLocation(servers.back().locations[tokens[1]]);
            }

            if (tokens[0] == "\thost")
                servers.back().host = tokens[1];
            else if (tokens[0] == "\tport")
                servers.back().port = tokens[1];
            else if (tokens[0] == "\tclient_max_body_size")
                servers.back().clientMaxBodySize = atol(tokens[1].c_str());
        }



        if (buff == "server")
        {
            servers.push_back(Server());
            continue ;
        }
    }

}
