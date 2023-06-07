#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>


class   Location
{
    public:
        bool                            autoindex;
        std::string                     root;
        std::string                     index;
        std::string                     upload;
        std::string                     cgi;
        std::pair<int, std::string>     redirect;
        std::set<std::string>           acceptedMethods;

};

