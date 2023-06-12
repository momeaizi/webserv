#include <string>
#include <vector>

bool containsOnlyWhitespaces(const std::string& str)
{

    for (size_t i = 0; i < str.length(); ++i)
        if (!std::isspace(str[i]))
            return false;
    return true;
}


std::string trimString(const std::string &str)
{

<<<<<<< HEAD
    size_t first = str.find_first_not_of(str);

    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(str);
    return str.substr(first, (last - first + 1));
=======
    std::string::const_iterator     start = str.begin();
    std::string::const_iterator     end = str.end();

    while (start != end && std::isspace(*start))
        ++start;

    do
        --end;
    while (end != start && std::isspace(*end));

    return std::string(start, end + 1);
>>>>>>> 8592abf20ec9499633abe6ef7191ed965d468919
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