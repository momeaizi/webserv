#ifndef CONFIGATTR_HPP
#define CONFIGATTR_HPP

#include <map>
#include <set>
#include "Location.hpp"
#include "string.hpp"


class ConfigParser;

class ConfigAttr
{
    private:
        long long                                               clientMaxBodySize;
        std::map<int, std::string>                              errorPages;
        std::map<std::string, Location>                         locations;


    public:

        friend class ConfigParser;

        ConfigAttr();
        ConfigAttr(const ConfigAttr &configAttr);
        ConfigAttr    &operator= (const ConfigAttr &configAttr);
        
        
        void    clear();

        /*                              setters                                         */
        void    setErrorPages(std::vector<std::string> &tokens, unsigned int lineNumber);
        void    setClientMaxBodySize(std::vector<std::string> &tokens, unsigned int lineNumber);


        /*                              getters                                         */
        const std::map<int, std::string>        &getErrorPages() const;
        const long long                         &getClientMaxBodySize() const;
        const std::map<std::string, Location>   &getLocations() const;

};


#endif
