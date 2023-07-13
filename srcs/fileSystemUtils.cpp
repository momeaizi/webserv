#include "../includes/fileSystemUtils.hpp"

bool    ft::isDirectory(const std::string &path)
{
    DIR* dir = opendir(path.data());
    if (!dir)
        return false;
    closedir(dir);
    return true;
}

bool    ft::isPathExists(const std::string &path)
{
    struct stat pathSt;
    return (stat(path.data(), &pathSt) == 0);
}

bool    ft::isFile(const std::string &path)
{
    DIR* dir = opendir(path.data());
    if (dir)
    {
        closedir(dir);
        return false;
    }
    
    struct stat buffer;
    return (stat(path.data(), &buffer) == 0);
}

long    ft::GetFileSize(const char* filename)
{
    struct stat st;
    stat(filename, &st);

    return st.st_size;
}