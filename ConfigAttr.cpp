#include "ConfigAttr.hpp"



ConfigAttr::ConfigAttr()
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
    allowedMethods = configAttr.allowedMethods;
    redirection = configAttr.redirection;
    locations = configAttr.locations;

    return *this;
}

void    ConfigAttr::clear()
{
    errorPages.clear();
    allowedMethods.clear();
    locations.clear();
    redirection.first = 0;
    redirection.second.clear();
    clientMaxBodySize = 0;
}