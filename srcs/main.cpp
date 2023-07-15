
#include "../includes/ContextManager.hpp"

fd_set  readMaster;
fd_set  writeMaster;
int     maxFds;
std::map<int, std::string>          statusCodes;
std::map<std::string, std::string>  mimeTypes;







int main()
{
    InitstatusCodesage();

    try
    {
        mimeTypesInitializer();
        ContextManager  http;

        if (!http.servers.size())
            return 1;

        http.openAndListen();
        http.ioMultiplexer();

    }
    catch(const char *e)
    {
        std::cerr << e << std::endl;
    }
    catch(std::string e)
    {
        std::cerr << e << std::endl;
    }

    return errno;
}