#include "../includes/Server.hpp"


void        Server::openSocket()
{
    struct addrinfo hints;
    struct addrinfo *bind_address;

    std::cerr << "Configuring address..." << std::endl;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(hostName.c_str(), port.c_str(), &hints, &bind_address);



    std::cerr << "Creating socket..." << std::endl;

    socket_listen = socket(bind_address->ai_family,
            bind_address->ai_socktype, bind_address->ai_protocol);

    if (socket_listen < 0)
        throw "socket() failed. " + std::to_string(errno);

    int yes = 1;
    setsockopt(socket_listen, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    int flags = fcntl(socket_listen, F_GETFL);
    fcntl(socket_listen, F_SETFL, flags | O_NONBLOCK);


    std::cerr << "Binding socket to local address..." << std::endl;

    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen))
        throw "bind() failed. " + std::to_string(errno);

    freeaddrinfo(bind_address);

    FD_SET(socket_listen, &readMaster);
}





void         Server::startListening()
{
    std::cerr << "Listening..." << std::endl;

    if (listen(socket_listen, 10) < 0)
        throw "listen() failed. " + std::to_string(errno);
}


int         Server::acceptClient(std::list<Client> &clients)
{
    struct sockaddr_storage client_address;
    socklen_t               client_len = sizeof(client_address);
    int                     socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
    char                    address_buffer[100];

    if (socket_client < 0)
    {
        std::cerr << "accept() failed. " << errno << std::endl;
        return 1;
    }

    getnameinfo((struct sockaddr*)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);

    clients.push_back(Client(socket_client, *this, address_buffer));

    FD_SET(socket_client, &readMaster);
    FD_SET(socket_client, &writeMaster);

    return 0;
}



Server::Server() : socket_listen(-1) {}

Server::Server(const Server &serv)
{
    *this = serv;
}

Server  &Server::operator= (const Server& serv)
{
    clear();
    socket_listen = serv.socket_listen;
    port = serv.port;
    hostName = serv.hostName;
    errorPages = serv.errorPages;
    clientMaxBodySize = serv.clientMaxBodySize;
    locations = serv.locations;

    return *this;
}




Server::~Server() {}

void         Server::clear()
{
    errorPages.clear();
    locations.clear();
    clientMaxBodySize = 0;
    socket_listen = -1;
    port.clear();
    hostName.clear();
}

void    Server::attributeExaminer()
{
    if (!port.length())
        throw "port is missing!";
    if (!hostName.length())
        throw "host is missing!";
}


std::pair<std::string, Location*>    Server::getMatchedLocation(const std::string &uri)
{
    size_t                                          max_len = 0;
    size_t                                          i = 0;
    std::pair<std::string, Location*>               location;

    std::map<std::string, Location>::iterator       it = locations.begin();

    for (; it != locations.end(); ++it)
    {
        const std::string &locationName = it->first;

        for (i = 0; i < locationName.length() && i < uri.length(); ++i)
        {
            if (locationName[i] != uri[i])
                break ;
        }

        if (i == locationName.length() && i > max_len)
        {
            max_len = i;
            location.first = it->first;
            location.second = &it->second;
        }
    }
    std::cout << location.first << std::endl;
    return location;
}


void    Server::setHostName(std::vector<std::string> &tokens, unsigned int lineNumber)
{
    if (tokens.size() != 2)
        throw "invalid number of arguments in \"host\" directive in serv.conf:" + std::to_string(lineNumber);

    hostName = tokens[1];
}

void    Server::setPort(std::vector<std::string> &tokens, unsigned int lineNumber)
{
    if (tokens.size() != 2)
        throw "invalid number of arguments in \"port\" directive in serv.conf:" + std::to_string(lineNumber);

    if (!containsOnlyDigits(tokens[1]))
        throw "invalid port number \"" + tokens[1] + "\"";
    port = tokens[1];
}

void        Server::setSocket(int socket_listen)
{
    this->socket_listen = socket_listen;
}

void    Server::setClientMaxBodySize(std::vector<std::string> &tokens, unsigned int lineNumber)
{
    if (tokens.size() != 2)
        throw "invalid number of arguments in \"client_max_body_size\" directive in serv.conf:" + std::to_string(lineNumber);

    if (!containsOnlyDigits(tokens[1]))
        throw "invalid client_max_body_size number \"" + tokens[1] + "\"";
    clientMaxBodySize = atoll(tokens[1].c_str());
}

void    Server::setErrorPages(std::vector<std::string> &tokens, unsigned int lineNumber)
{
    if (tokens.size() != 3)
        throw "invalid number of arguments in \"error_page\" directive in serv.conf:" + std::to_string(lineNumber);

    if (!containsOnlyDigits(tokens[1]))
        throw "invalid error code number \"" + tokens[1] + "\"";
    errorPages[atoi(tokens[1].c_str())] = tokens[2];
}


// void        Server::addConfigAttr(const ConfigAttr &configAttr)
// {
//     configAttrs[hostName] = configAttr;
// }

const std::string                       &Server::getHostName() const
{
    return hostName;
}
const std::string                       &Server::getPort() const
{
    return port;
}

const int                               &Server::getSocket() const
{
    return socket_listen;
}



const std::map<int, std::string>        &Server::getErrorPages() const
{
    return errorPages;
}

const long long                         &Server::getClientMaxBodySize() const
{
    return clientMaxBodySize;
}

const std::map<std::string, Location>   &Server::getLocations() const
{
    return locations;
}
