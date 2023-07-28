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
		servers[i].openSocket();

	for (size_t i = 0 ; i < servers.size(); ++i)
		servers[i].startListening();
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
			throw "select() failed. " + to_string(errno);


		for (size_t i = 0; i < servers.size(); ++i)
		{
			if (FD_ISSET(servers[i].getSocket(), &reads))
			{
				servers[i].acceptClient(clients);
			}
		}

		for (std::list<Client>::iterator it = clients.begin(); it != clients.end();)
		{
			Client	&client = *it;


			(client.*client.serve)();
			if (FD_ISSET(client.getClSocket(), &reads))
			{

				bytes = recv(client.getClSocket(), buffer, 1024, 0);
				if (bytes <= 0)
				{
					if (client.methodType == "POST")
            			remove(client.uploadFileName.c_str());
					DROPCLIENT;
				}

				client.lastActivity = time(NULL);

				client.buffer += std::string(buffer, bytes);
			}
			else if (FD_ISSET(client.getClSocket(), &writes))
			{
				if (client.response.length())
				{
					bytes = send(client.getClSocket(), client.response.data(), client.response.length(), 0);
					if (bytes < 0)
					{
						DROPCLIENT;
					}
					else if (bytes)
						client.lastActivity = time(NULL);

					client.response = client.response.substr(bytes);
				}
				
			}

			if (time(NULL) - client.lastActivity > TIMEOUT)
			{
				DROPCLIENT;
			}
			else if (!client.serve)
			{
				if (client.headerFields.count("connection") and client.headerFields["connection"] == "Keep-Alive")
					client.clear();
				else
				{
					DROPCLIENT;
				}
			}
			++it;
		}
	}
}