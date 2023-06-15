#include "../includes/ContextManager.hpp"




ContextManager::ContextManager()
{
	ConfigParser	configparser(servers);
	FD_ZERO(&readMaster);
	FD_ZERO(&writeMaster);
}


void    ContextManager::openAndListen()
{
	for (size_t i = 0 ; i < servers.size(); ++i)
	{
		servers[i].openSocket();
	}

	for (size_t i = 0 ; i < servers.size(); ++i)
	{
		servers[i].startListening();
	}
}


void    ContextManager::ioMultiplexer()
{
	fd_set	reads;
	fd_set	writes;

	while (26)
	{
		reads = readMaster;
		writes = writeMaster;

		if (select(servers.size() + clients.size() + 4, &reads, &writes, 0, 0) < 0)
			throw "select() failed. " + std::to_string(errno);


		for (size_t i = 0; i < servers.size(); ++i)
		{
			if (FD_ISSET(servers[i].getSocket(), &reads))
			{
				servers[i].acceptClient(clients);
				std::cout << "socket : " << clients.back().getClSocket() << std::endl;
			}
		}

		for (std::list<Client>::iterator it = clients.begin(); it != clients.end();)
		{
			if (FD_ISSET(it->getClSocket(), &reads))
			{
				std::cout << it->getIpAddress() << std::endl;
				char    read[1024];
				int     bytes_received = recv(it->getClSocket(), read, 1024, 0);
				if (bytes_received <= 0)
				{
					close(it->getClSocket());
    				FD_CLR(it->getClSocket(), &readMaster);
					clients.erase(it++);
					continue ;
				}

				std::cout << " ---- Request Begin ---" <<  std::endl;
				std::cout << read << std::endl;
				std::cout << " ---- Request End  ---" <<  std::endl;
	
				char buff[] =   "HTTP/1.1 200 OK\r\n"
								"Server: Allah Y7ssen L3wan\r\n"
								"Content-Length: 12\r\n"
								"Content-Type: text/plain\r\n\r\n"
								"HELLO WORLD!";
				if (send(it->getClSocket(), buff, sizeof(buff), 0) < 0)
					perror("Send -> ");

			}
			++it;
		}
	}
}