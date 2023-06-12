#include <string>
#include <vector>

bool containsOnlyWhitespaces(const std::string& str)
{

    for (size_t i = 0; i < str.length(); ++i)
        if (!std::isspace(str[i]))
            return false;
    return true;
}

std::string trim(const std::string& str, const std::string t)
{
    size_t first = str.find_first_not_of(t);

    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(t);
    return str.substr(first, (last - first + 1));
}

std::string trimString(const std::string &str)
{

    size_t first = str.find_first_not_of(str);

    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(str);
    return str.substr(first, (last - first + 1));
}


std::vector<std::string> splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> substrs;
    std::string substr;

    std::size_t start = 0;
    std::size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        substr = str.substr(start, end - start);
        if (substr.length())
            substrs.push_back(substr);

        start = end + 1;
        end = str.find(delimiter, start);
    }


    substr = str.substr(start);
    if (substr.length())
        substrs.push_back(substr);

    return substrs;
}