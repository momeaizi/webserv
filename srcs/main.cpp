
#include "../includes/ContextManager.hpp"

fd_set  readMaster;
fd_set  writeMaster;
int     maxFds;







int main()
{
    InitstatusCodesage();
    mimeTypesInitializer();

    try
    {
        ContextManager  http;


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