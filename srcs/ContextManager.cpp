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


		if (select(maxFds + 1, &reads, &writes, 0, 0) < 0)
			throw "select() failed. " + std::to_string(errno);


		for (size_t i = 0; i < servers.size(); ++i)
		{
			if (FD_ISSET(servers[i].getSocket(), &reads))
			{
				servers[i].acceptClient(clients);
				std::cout << "socket : " << clients.back().getClSocket() << std::endl;
				std::cout << "maxFds : " << maxFds << std::endl;
			}
		}

		// std::cout << "size -> " << clients.size() << std::endl;
		for (std::list<Client>::iterator it = clients.begin(); it != clients.end();)
		{
			Client	&client = *it;

			if (FD_ISSET(client.getClSocket(), &reads))
			{

				bytes = recv(client.clSocket, buffer, 1024, 0);
				if (bytes <= 0)
				{
					std::cout << "RECV" << std::endl;
					client.clear();
					client.drop(readMaster, writeMaster);
					clients.erase(it++);
					continue ;
				}

				client.lastActivity = time(NULL);

				client.buffer += std::string(buffer, bytes);
			}

			(client.*client.serve)();

			if (FD_ISSET(client.getClSocket(), &writes))
			{
				if (client.response.length())
				{
					bytes = send(client.getClSocket(), client.response.data(), client.response.length(), 0);
					if (bytes < 0)
					{
						std::cout << "SEND" << std::endl;
						client.clear();
						client.drop(readMaster, writeMaster);
						clients.erase(it++);
						continue ;
					}
					else if (bytes)
						client.lastActivity = time(NULL);



					if ((size_t)bytes != client.response.length())
						std::cout << "HERE!" << std::endl;
		
					client.response = client.response.substr(bytes);
				}
				
			}

			if (client.getPhase() == -1 || time(NULL) - client.lastActivity > TIMEOUT)
			{
				client.clear();

				if (!client.headerFields.count("connection") or client.headerFields["connection"] != "Keep-Alive")
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