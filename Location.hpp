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


    std::string     GetUpload();
    std::string     GetIndex();
    bool            LocationHasCgi();

    void    setAutoindex(std::vector<std::string> &tokens, unsigned int lineNumber);
    void    setRoot(std::vector<std::string> &tokens, unsigned int lineNumber);
    void    setIndex(std::vector<std::string> &tokens, unsigned int lineNumber);
    void    setUpload(std::vector<std::string> &tokens, unsigned int lineNumber);
    void    setRedirection(std::vector<std::string> &tokens, unsigned int lineNumber);
    void    setCgi(std::vector<std::string> &tokens, unsigned int lineNumber);
    void    setAllowedMethods(std::vector<std::string> &tokens, unsigned int lineNumber);

};

#endif