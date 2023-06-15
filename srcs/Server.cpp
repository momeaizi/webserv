#include "../includes/Server.hpp"


void        Server::createSocket()
{
    struct addrinfo hints;
    struct addrinfo *bind_address;

    std::cerr << "Configuring address..." << std::endl;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, port.c_str(), &hints, &bind_address);



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

    FD_SET(socket_listen, &master);
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

    FD_SET(socket_client, &master);

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
    configAttrs = serv.configAttrs;
    socket_listen = serv.socket_listen;
    port = serv.port;
    hostName = serv.hostName;

    return *this;
}


Server  &Server::operator+= (const Server& serv)
{
    std::pair<std::string, ConfigAttr>    val = 
                                    make_pair(serv.configAttrs.begin()->first, serv.configAttrs.begin()->second);
    configAttrs.insert(val);
    return *this;
}


Server::~Server()
{
    clear();
}

void         Server::clear()
{

    socket_listen = -1;
    port.clear();
    hostName.clear();
    configAttrs.clear();
}

void        Server::attributeExaminer()
{
    if (!port.length())
        throw "port is missing!";
    if (!hostName.length())
        throw "host is missing!";
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
void        Server::addConfigAttr(const ConfigAttr &configAttr)
{
    configAttrs[hostName] = configAttr;
}

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

const std::map<std::string, ConfigAttr> &Server::getConfigAttrs() const
{
    return configAttrs;
}
