# include "../includes/Client.hpp"

void    Client::DeleteHandler()
{
    if (access(resource.data(), W_OK))
        setHeader(404);
    else if (ft::isFile(resource))
    {
        remove(resource.data());
        setHeader(204);
    }
    else if (deleteDir(resource.data()))
        setHeader(204);
    else if (access(resource.data(), W_OK))
        setHeader(500);
    else 
        setHeader(403);
}

int deleteDir(const char* path)
{
    DIR* dir = opendir(path);

    dirent* entry;
    while ((entry = readdir(dir)) != NULL)
    {
        const char* filename = entry->d_name;
        std::string strfile = std::string(filename);
        if (strfile == ".." or strfile == ".")
            continue;
        strfile = std::string(path) + "/" + strfile;
        if (ft::isDirectory(strfile.data()))
            if (!deleteDir(strfile.data()))
                return 0;

        if (remove(strfile.data()))
            return 0;
    }
    closedir(dir);
    return 1;
}