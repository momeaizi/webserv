# include "../includes/Client.hpp"


std::vector<std::string>  listOfCurrentContent(std::string path)
{
    DIR                         *dir = opendir(path.data());
    dirent                      *entry;
    std::vector<std::string>    currentContent;

    while ((entry = readdir(dir)))
    {
        std::string filepath(path + "/" + std::string(entry->d_name));

        currentContent.push_back(std::string(entry->d_name));
        if (ft::isDirectory(filepath))
            currentContent[currentContent.size() - 1] += "/";
    }
    closedir(dir);
    return currentContent;
}

void StringOfCurrentContent(const std::string &path, const std::string &filename, const std::string &uri)
{
    std::string                 autoindex_content = "<!DOCTYPE html><html><body><h1>Index of " + uri + "</h1> <hr><ul>";
    std::vector<std::string>    currentContent = listOfCurrentContent(path);
    std::ofstream               autoindex_file(filename.c_str());

    autoindex_file << autoindex_content;

    for(size_t i = 0; i < currentContent.size(); i++)
    {
        if (currentContent[i] == "./")
            continue;

        autoindex_content = "<li><a href=\"" + uri + currentContent[i] +"\">";

        if (currentContent[i].size() > 50)
            autoindex_content += currentContent[i].substr(49) + "..>";
        else
            autoindex_content += currentContent[i];
        autoindex_content += "</a> <l/i>\n";

        autoindex_file << autoindex_content;
    }
    autoindex_content += "</ul><hr> </body>";

    autoindex_file.close();
}
