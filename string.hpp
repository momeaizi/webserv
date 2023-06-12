# ifndef STRING_HPP
# define STRING_HPP
# include <string>
# include <vector>
#include <iostream>


std::string trim(const std::string& str, const std::string t);
bool containsOnlyWhitespaces(const std::string& str);
std::vector<std::string> splitString(const std::string& str, char delimiter);
std::string trimString(const std::string &str);

#endif