#ifndef CONFIGATTR_HPP
#define CONFIGATTR_HPP

#include <map>
#include <set>
#include "Location.hpp"


struct ConfigAttr
{
    std::map<int, std::string>                              errorPages;
    long                                                    clientMaxBodySize;
    std::set<std::string>                                   allowedMethods;
    std::pair<int, std::string>                             redirection;
    std::map<std::string, Location>                         locations;

    ConfigAttr();
    ConfigAttr(const ConfigAttr &configAttr);
    ConfigAttr    &operator= (const ConfigAttr &configAttr);
    void    clear();
};


#endif
