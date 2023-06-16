#include "../includes/ContextManager.hpp"




ContextManager::ContextManager()
{
<<<<<<< HEAD
	if (tokens.size() != 2)
		throw "invalid number of arguments in \"location\" directive in serv.conf:" + std::to_string(lineNumber);

	while (std::getline(configFIle, buff))
	{
		++lineNumber;

		if (!buff.length() || containsOnlyWhitespaces(buff)) // SKIP EMPTY LINE
			continue ;

		tokens = splitString(buff, ' ');

		if (tokens[0] == "\t\troot")
			location.setRoot(tokens, lineNumber);  // SET ROOT
		else if (tokens[0] == "\t\tindex")
			location.setIndex(tokens, lineNumber); // SET INDEX
		else if (tokens[0] == "\t\tupload_pass")
			location.setUpload(tokens, lineNumber); // SET UPLOAD
		else if (tokens[0] == "\t\tcgi_pass")
			location.setCgi(tokens, lineNumber); // SET CGI
		else if (tokens[0] == "\t\tautoindex")
			location.setAutoindex(tokens, lineNumber); // SET AUTOINDEX
		else if (tokens[0] == "\t\tallow_methods")
			location.setAllowedMethods(tokens, lineNumber); // SET ALLOWEDMETHODS
		else if (tokens[0] == "\t\treturn")
			location.setRedirection(tokens, lineNumber); // SET REDIRECCTION 
		else
			return 1; // DIRECTIVE DOESN'T BELONGS TO THE LOCATION DIRECTIVE

	} // GETTING LINES FROM THE FILE

	return 0; // THE END OF THE FILE

=======
	ConfigParser	configparser(servers);
	FD_ZERO(&readMaster);
	FD_ZERO(&writeMaster);
>>>>>>> master
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