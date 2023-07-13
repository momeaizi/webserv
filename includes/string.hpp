# ifndef STRING_HPP
# define STRING_HPP
# include <string>
# include <vector>
# include <list>
#include <iostream>
#include <sys/socket.h>
#include <fstream> // remove


#define buf 1024

std::string                 to_lower(const std::string &str);
std::string                 tok(std::string &str, std::string sep);
bool                        containsOnlyWhitespaces(const std::string& str);
bool                        containsOnlyDigits(const std::string& str);
std::vector<std::string>    splitString(const std::string& str, char delimiter);
std::string                 trimString(const std::string &str);
std::list<std::string>      getlines(std::string  &str);


#endif