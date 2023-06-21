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
	int		bytes;

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

		// std::cout << "size -> " << clients.size() << std::endl;
		for (std::list<Client>::iterator it = clients.begin(); it != clients.end();)
		{
			Client	&client = *it;

			if (FD_ISSET(client.getClSocket(), &reads))
			{
				// std::cout << "FD_ISSET read" <<std::endl;

				bytes = recv(client.clSocket, buffer, 1024, 0);
				if (bytes <= 0)
				{
					client.drop(readMaster, writeMaster);
					clients.erase(it++);
					continue ;
				}

				client.buffer += std::string(buffer, bytes);
			}

			(client.*client.serve)();
	
			if (FD_ISSET(client.getClSocket(), &writes))
			{
				// std::cout << "FD_ISSET write" <<std::endl;
				if (client.response.length())
					if (send(client.getClSocket(), client.response.data(), client.response.length(), 0) < 0)
						perror("Send -> ");
				client.response.clear();
				
			}

			if (client.getPhase() == -1 || time(NULL) - client.lastActivity > TIMEOUT)
			{
				if (client.headerFields["connection"] == "Keep-Alive")
					client.clear();
				else
				{
					client.drop(readMaster, writeMaster);
					clients.erase(it++);
					continue ;
				}
			}
			++it;
		}
	}
}