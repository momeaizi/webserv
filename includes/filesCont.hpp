# ifndef __FILESCONT_HPP
# define __FILESCONT_HPP
# include <dirent.h>
# include <sys/stat.h>
# include <string>

namespace ft
{
    bool isDirectory(const std::string& path);
    bool isPathExists(const std::string& path);
    bool isFile(const std::string& path);
}

#endif
