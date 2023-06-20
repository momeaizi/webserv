# ifndef __AUTO_INDEX__HPP 
# define __AUTO_INDEX__HPP
# include "../includes/filesCont.hpp"
# include <unistd.h>
# include <fstream>
# include <list>
# include <fcntl.h>
# include <dirent.h>
# include <sstream>
# include <cstdio>
# include <string>
# include <iostream>
# include <vector>
# include <ctime>

void StringOfCurrentContent(const std::string &path, const std::string &filename);

#endif