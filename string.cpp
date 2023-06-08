#include <string>
#include <vector>

std::string trimString(const std::string &str)
{

    std::string::const_iterator     start = str.begin();
    std::string::const_iterator     end = str.end();

    do
        --end;
    while (end != start && std::isspace(*end));

    return std::string(start, end + 1);
}


std::vector<std::string> splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> substrings;
    std::string substring;

    std::size_t start = 0;
    std::size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        if (start != end)
        {
            substring = str.substr(start, end - start);
            substrings.push_back(substring);
        }
        start = end + 1;
        end = str.find(delimiter, start);
    }


    substring = str.substr(start);
    substrings.push_back(substring);

    return substrings;
}