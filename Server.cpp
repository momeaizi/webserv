#include "Server.hpp"


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


    if (socket_listen > max_socket)
        max_socket = socket_listen;
}





void         Server::startListening()
{
    std::cerr << "Listening..." << std::endl;

    if (listen(socket_listen, 10) < 0)
        throw "listen() failed. " + std::to_string(errno);
}


int         Server::acceptClient(std::list<Client> &clients, size_t serverId)
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

    clients.push_back(Client(socket_client, serverId, address_buffer));

    FD_SET(socket_client, &master);
    if (socket_client > max_socket)
        max_socket = socket_client;


    return 0;
}


void         Server::clear()
{

    host.clear();
    socket_listen = -1;
    port.clear();
    hostName.clear();
    hosts.clear();
}


Server  &Server::operator+= (const Server& serv)
{
    std::pair<std::string, Host>    val = 
                                    make_pair(serv.hosts.begin()->first, serv.hosts.begin()->second);
    hosts.insert(val);
    return *this;
}


Server::Server()
{
    clear();
}

Server::Server(const Server &serv)
{
    clear();
    hosts = serv.hosts;
    socket_listen = serv.socket_listen;
    port = serv.port;
    hostName = serv.hostName;
}

Server::~Server()
{
    clear();
}



Host::Host()
{
    clear();
}

Host::Host(const Host &host)
{
    errorPages = host.errorPages;
    clientMaxBodySize = host.clientMaxBodySize;
    allowedMethods = host.allowedMethods;
    redirection = host.redirection;
    locations = host.locations;
}

void    Host::clear()
{
    errorPages.clear();
    allowedMethods.clear();
    locations.clear();
    redirection.first = 0;
    redirection.second.clear();
    clientMaxBodySize = 0;
}