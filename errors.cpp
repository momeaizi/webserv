#include <iostream>
#include "errors.hpp"


void send_100()
{
    std::cout << "error  100 Continue!!!" << std::endl;
    exit(0);
}

void send_101()
{
    std::cout << "error  101 Switching Protocols!!!" << std::endl;
    exit(0);
}

void send_200()
{
    std::cout << "error  200 OK!!!" << std::endl;
    exit(0);
}

void send_201()
{
    std::cout << "error  201 Created!!!" << std::endl;
    exit(0);
}

void send_204()
{
    std::cout << "error  204 No Content!!!" << std::endl;
    exit(0);
}

void send_301()
{
    std::cout << "error  301 Moved Permanently!!!" << std::endl;
    exit(0);
}

void send_400()
{
    std::cout << "error  400 Bad Request!!!" << std::endl;
    exit(0);
}

void send_401()
{
    std::cout << "error  401 Unauthorized!!!" << std::endl;
    exit(0);
}

void send_403()
{
    std::cout << "error  403 Forbidden!!!" << std::endl;
    exit(0);
}

void send_404()
{
    std::cout << "error  404 Not Found!!!" << std::endl;
    exit(0);
}

void send_405()
{
    std::cout << "error  405 Method Not Allowed!!!" << std::endl;
    exit(0);
}

void send_409()
{
    std::cout << "error  409 Conflict!!!" << std::endl;
    exit(0);
}

void send_413()
{
    std::cout << "error  413 Request Entity Too Large!!!" << std::endl;
    exit(0);
}

void send_414()
{
    std::cout << "error  414 Request_URI Too Long!!!" << std::endl;
    exit(0);
}

void send_405()
{
    std::cout << "error  405 Method Not Allowed!!!" << std::endl;
    exit(0);
}

void send_500()
{
    std::cout << "error  500 Internal Server Error!!!" << std::endl;
    exit(0);
}

void send_501()
{
    std::cout << "error  501 Not Implemented!!!" << std::endl;
    exit(0);
}

void send_505()
{
    std::cout << "error  505 !!!" << std::endl;
    exit(0);
}
