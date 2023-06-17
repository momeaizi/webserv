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
				std::cout << "FD_ISSET" <<std::endl;

				bytes = recv(it->clSocket, buffer, 1024, 0);
				std::cout << "after recv -> " << bytes << std::endl;
				if (bytes <= 0)
				{
					close(it->clSocket);
				    FD_CLR(it->clSocket, &readMaster);
					// it->drop();
					clients.erase(it++);
					continue ;
				}

				it->buffer += std::string(buffer, bytes);
				std::cout << it->buffer << std::endl;

				if (it->getPhase() == 1)
				{
					std::cout << "phase = 1" <<std::endl;
					it->parse();
				}
				if (it->getPhase() == 0)
				{
					std::cout << "phase = 0" <<std::endl;
					std::cout << "************************************" << std::endl;
					std::cout << "uri -> " << it->URI << std::endl;
					std::cout << "method -> " << it->methodType << std::endl;
					std::map<std::string, std::string>::iterator	it_ = it->headerFields.begin();
					for (; it_ != it->headerFields.end(); ++it_)
						std::cout << it_->first << " : " << it_->second << std::endl;
					std::cout << "************************************" << std::endl;
					std::cout << std::endl;
					char buff[] =   "HTTP/1.1 200 OK\r\n"
									"Server: Allah Y7ssen L3wan\r\n"
									"Content-Length: 12\r\n"
									"Content-Type: text/plain\r\n\r\n"
									"HELLO WORLD!";
					if (send(it->getClSocket(), buff, sizeof(buff), 0) < 0)
						perror("Send -> ");
				}



			}
			++it;
		}
	}
}