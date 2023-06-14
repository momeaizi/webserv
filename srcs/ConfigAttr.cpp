#include "../includes/ConfigAttr.hpp"



ConfigAttr::ConfigAttr() : clientMaxBodySize(0)
{
    clear();
}

ConfigAttr::ConfigAttr(const ConfigAttr &configAttr)
{
    *this = configAttr;
}

ConfigAttr    &ConfigAttr::operator= (const ConfigAttr &configAttr)
{
    errorPages = configAttr.errorPages;
    clientMaxBodySize = configAttr.clientMaxBodySize;
    locations = configAttr.locations;

    return *this;
}

void    ConfigAttr::clear()
{
    errorPages.clear();
    locations.clear();
    clientMaxBodySize = 0;
}


void    ConfigAttr::setClientMaxBodySize(std::vector<std::string> &tokens, unsigned int lineNumber)
{
    if (tokens.size() != 2)
        throw "invalid number of arguments in \"client_max_body_size\" directive in serv.conf:" + std::to_string(lineNumber);

    if (!containsOnlyDigits(tokens[1]))
        throw "invalid client_max_body_size number \"" + tokens[1] + "\"";
    clientMaxBodySize = atoll(tokens[1].c_str());
}

void    ConfigAttr::setErrorPages(std::vector<std::string> &tokens, unsigned int lineNumber)
{
    if (tokens.size() != 3)
        throw "invalid number of arguments in \"error_page\" directive in serv.conf:" + std::to_string(lineNumber);

    if (!containsOnlyDigits(tokens[1]))
        throw "invalid error code number \"" + tokens[1] + "\"";
    errorPages[atoi(tokens[1].c_str())] = tokens[2];
}

const std::map<int, std::string>        &ConfigAttr::getErrorPages() const
{
    return errorPages;
}

const long long                         &ConfigAttr::getClientMaxBodySize() const
{
    return clientMaxBodySize;
}

const std::map<std::string, Location>   &ConfigAttr::getLocations() const
{
    return locations;
}

