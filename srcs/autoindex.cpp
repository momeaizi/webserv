# include "../includes/autoindex.hpp"
# include <sys/stat.h>


std::vector<std::string>  ListOfCurrentContent(std::string path)
{
    DIR* dir = opendir(path.data());

    dirent* entry;
    std::vector<std::string> currentContent;
    while ((entry = readdir(dir)) != nullptr)
    {
        std::string filepath(path+"/" + std::string(entry->d_name));

        currentContent.push_back(std::string(entry->d_name));
        if (ft::isDirectory(filepath))
            currentContent[currentContent.size() - 1] += "/";
    }
    closedir(dir);
    return currentContent;
}

void StringOfCurrentContent(const std::string &path, const std::string &filename)
{
    std::string response = "<!DOCTYPE html><html><body><h1>Index of " + path + "/</h1> <hr><ul>";
    std::vector<std::string> currentContent = ListOfCurrentContent(path);
    std::ofstream HTMLFILE(filename);

    HTMLFILE << response;
    for(size_t i = 0; i < currentContent.size(); i++)
    {
        response = "<li><a href=\"" + currentContent[i] +"\">";
        if (currentContent[i].size() > 50)
            response += currentContent[i].substr(49) + "..>";
        else
            response += currentContent[i];
        response += "</a> <l/i>\n";

        HTMLFILE << response;
    }
    response += "</ul><hr> </body>";
    HTMLFILE.close();
}
