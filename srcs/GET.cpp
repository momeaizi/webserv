# include "../includes/Client.hpp"

void    Client::GetHandler()
{
    if (access(resource.data(), W_OK))
    {
        setHeader(404);
        return ;
    }
    if (ft::isDirectory(resource))
    {
        if (!hasSlash(resource))
        {
            setHeader(301);
            return ;
        }
        std::string filePath = resource;
        if(hasIndex(location->getIndex()))
                filePath += location->getIndex();
        if (!ft::isFile(filePath))
        {
            if (location->getAutoindex())
            {
                std::string name = "/tmp/" + generateFileNameFromDate() + ".html";
                StringOfCurrentContent(resource, name, URI);
                resource = name;
                setHeader(200);
            }
            else
                setHeader(403);
            return ;
        }
        resource = filePath;
    }
    if (!location->locationHasCgi())
        setHeader(200);
    else
        serveCGI();
}