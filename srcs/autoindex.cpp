# include "../includes/Client.hpp"
# include "../includes/filesCont.hpp"
# include <sys/stat.h>

std::string strTime(std::string filepath)
{
    struct stat directorInf;
    int j = stat(filepath.data(), &directorInf);
    struct tm *timeptr = gmtime(&directorInf.st_mtime);
    std::string monthNames[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    std::string time(std::to_string(timeptr->tm_mday) + "-");

    time += monthNames[timeptr->tm_mon] + "-";
    time += std::to_string(timeptr->tm_year + 1900) + " ";
    time += std::to_string(timeptr->tm_hour) + ":" + std::to_string(timeptr->tm_sec);
    return time;
}

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

std::string StringOfCurrentContent(std::string path)
{
    std::string response = "<!DOCTYPE html><html><body><h1>Index of " + path + "/</h1> <hr><ul>";
    std::vector<std::string> currentContent = ListOfCurrentContent(path);
    for(int i = 0; i < currentContent.size(); i++)
    {
        response += "<li><a href=\"" +  currentContent[i] +"\">";
        if (currentContent[i].size() > 50)
            response += currentContent[i].substr(49) + "..>";
        else
            response += currentContent[i];
        response += "</a> <l/i>\n";// + currentContent[i][1] + " \n";// + currentContent[i][2] + " \n";
    }
    response += "</ul><hr> </body>";
    return response;
}


int main()
{
    std::ofstream file("index.html");
    file << StringOfCurrentContent("/Users/mskerba/Desktop");
}