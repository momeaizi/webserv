#include "../includes/string.hpp"

bool containsOnlyWhitespaces(const std::string& str)
{

    for (size_t i = 0; i < str.length(); ++i)
        if (!std::isspace(str[i]))
            return false;
    return true;
}

bool containsOnlyDigits(const std::string& str)
{

    for (size_t i = 0; i < str.length(); ++i)
        if (!std::isdigit(str[i]))
            return false;
    return true;
}

std::string to_lower(const std::string &str)
{
    std::string lower_str(str);

    for (size_t i = 0; i < str.length(); ++i)
        lower_str[i] = std::tolower(str[i]);

    return lower_str;
}


std::list<std::string> getlines(std::string  &str)
{              
    std::string             sep;
    std::size_t             loc = 0;
    std::list<std::string>  lines;

    sep   = "\r\n";
    loc   = str.find(sep);
    while (loc != std::string::npos)
    {
        lines.push_back(tok(str, sep));
        if (lines.back() == "")
            break ;
        loc = str.find(sep);
    }

    return lines;
}


std::string trimString(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");

    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}


std::string tok(std::string &str, std::string sep)
{
    std::string sepstring;
    int loc = str.find(sep);
    sepstring = str.substr(0, loc);
    str = str.substr(loc + sep.size());
    return sepstring;
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
