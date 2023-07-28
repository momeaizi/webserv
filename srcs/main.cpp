
#include "../includes/ContextManager.hpp"

fd_set                              readMaster;
fd_set                              writeMaster;
std::set<int>                       fds;
std::map<int, std::string>          statusCodes;
std::map<std::string, std::string>  mimeTypes;







int main()
{
    InitReasonPhrase();

    try
    {
        InitMimeTypes();
        ContextManager  http;

        if (!http.getServers().size())
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