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

std::string trim(const std::string& str, const std::string t)
{
    size_t first = str.find_first_not_of(t);

    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(t);
    return str.substr(first, (last - first + 1));
}


std::list<std::string> getlines(int phase)
{
    static std::string        str;
    static size_t             seekg = 0;                
    std::string               sep;
    std::list<std::string>  lines;
    char                      buffer[1024];
    std::size_t               loc = 0;
    int                       bytes;
    // int                       fd;

    if (phase)
    {
        lines.push_back(str);
        return lines;
    }
    // bytes  = recv(fd, buffer, (size_t)buf);
    std::ifstream inputFile("filename.txt");
    bytes = buf;
    inputFile.seekg(seekg, std::ios::cur);
    inputFile.read(buffer, bytes);
    seekg += bytes;
    str   += std::string(buffer, bytes);
    sep   = "\\r\n";
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

std::string getRemainder()
{
    return getlines(1).back();
}

std::string trimString(const std::string &str)
{

    std::string::const_iterator     start = str.begin();
    std::string::const_iterator     end = str.end();

    while (start != end && std::isspace(*start))
        ++start;

    do
        --end;
    while (end != start && std::isspace(*end));

    return std::string(start, end + 1);
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