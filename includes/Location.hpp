#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "string.hpp"


struct   Location
{
    private:
        bool                                autoindex;
        std::string                         root;
        std::string                         index;
        std::string                         upload;
        std::pair<int, std::string>         redirection;
        std::map<std::string, std::string>  cgi;
        std::set<std::string>               allowedMethods;


    public:

        bool            locationHasCgi();

        /*                              setters                                         */
        void    setAutoindex(std::vector<std::string> &tokens, unsigned int lineNumber);
        void    setRoot(std::vector<std::string> &tokens, unsigned int lineNumber);
        void    setIndex(std::vector<std::string> &tokens, unsigned int lineNumber);
        void    setUpload(std::vector<std::string> &tokens, unsigned int lineNumber);
        void    setRedirection(std::vector<std::string> &tokens, unsigned int lineNumber);
        void    setCgi(std::vector<std::string> &tokens, unsigned int lineNumber);
        void    setAllowedMethods(std::vector<std::string> &tokens, unsigned int lineNumber);


        /*                              getters                                         */
        bool                                        getAutoindex() const;
        const std::string                           &getRoot() const;
        const std::string                           &getIndex() const;
        const std::string                           &getUpload() const;
        const std::pair<int, std::string>           &getRedirection() const;
        const std::map<std::string, std::string>    &getCgi() const;
        const std::set<std::string>                 &getAllowedMethods() const;

};

#endif