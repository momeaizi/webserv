# ifndef __AUTO_INDEX__HPP 
# define __AUTO_INDEX__HPP
# include "../includes/fileSystemUtils.hpp"
# include <unistd.h>
# include <fstream>
# include <fcntl.h>
# include <dirent.h>
# include <sstream>
# include <cstdio>
# include <string>
# include <iostream>
# include <vector>

void StringOfCurrentContent(const std::string &path, const std::string &filename, const std::string &uri);

#endif