#ifndef CONFIGATTR_HPP
#define CONFIGATTR_HPP

#include <map>
#include <set>
#include "Location.hpp"


struct ConfigAttr
{
    std::map<int, std::string>                              errorPages;
    long long                                               clientMaxBodySize;
    std::map<std::string, Location>                         locations;

    ConfigAttr();
    ConfigAttr(const ConfigAttr &configAttr);
    ConfigAttr    &operator= (const ConfigAttr &configAttr);
    
    
    void    clear();
    void    setErrorPages(std::vector<std::string> &tokens, unsigned int lineNumber);
    void    setClientMaxBodySize(std::vector<std::string> &tokens, unsigned int lineNumber);
    // void    setAllowedMethods(std::vector<std::string> &tokens, unsigned int lineNumber);
    void    setRedirection(std::vector<std::string> &tokens, unsigned int lineNumber);
    // void    setLocations(std::vector<std::string> &tokens, unsigned int lineNumber);
};


#endif
