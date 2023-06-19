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

		std::cout << "size -> " << clients.size() << std::endl;
		for (std::list<Client>::iterator it = clients.begin(); it != clients.end();)
		{
			if (FD_ISSET(it->getClSocket(), &reads))
			{
				std::cout << "FD_ISSET read" <<std::endl;

				bytes = recv(it->clSocket, buffer, 1024, 0);
				std::cout << "after recv -> " << bytes << std::endl;
				if (bytes <= 0)
				{
					it->drop(readMaster, writeMaster);
					clients.erase(it++);
					continue ;
				}

				it->buffer += std::string(buffer, bytes);
				it->serve();
			}
	
			if (FD_ISSET(it->getClSocket(), &writes))
			{
				std::cout << "FD_ISSET write" <<std::endl;
				if (it->response.length())
					if (send(it->getClSocket(), it->response.data(), it->response.length(), 0) < 0)
						perror("Send -> ");
				it->response.clear();
				
			}

			if (it->getPhase() == -1 || time(NULL) - it->lastActivity > TIMEOUT)
			{
				if (it->headerFields["connection"] == "Keep-Alive")
					it->clear();
				else
				{
					it->drop(readMaster, writeMaster);
					clients.erase(it++);
					continue ;
				}
			}
			++it;
		}
	}
}