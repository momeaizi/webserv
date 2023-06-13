#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>


class   Location
{
    public:
        bool                                autoindex;
        std::string                         root;
        std::string                         index;
        std::string                         upload;
        std::pair<int, std::string>         redirection;
        std::map<std::string, std::string>  cgi;
        std::set<std::string>               allowedMethods;
    //
    Location():upload(""){}
    std::string GetUpload() {return this->upload;}
    std::string GetIndex() {return this->index;}
    bool LocationHasCgi() {return cgi.size();}

};

#endif