#include "../includes/ContextManager.hpp"



ContextManager::ContextManager(const char *configFileName) : configFIle(configFileName)
{
	if (!configFIle.is_open())
		throw "config file can't be opened!";
		
	lineNumber = 0;
	parseConfigFIle();

	tokens.clear();
	buff.clear();
	configFIle.close();
	configFIle.clear();
		
}

int	ContextManager::parseLocation(Location &location)
{
	if (tokens.size() != 2)
		throw "invalid number of arguments in \"location\" directive in serv.conf:" + std::to_string(lineNumber);

	while (std::getline(configFIle, buff))
	{
		++lineNumber;

		if (!buff.length() || containsOnlyWhitespaces(buff)) // SKIP EMPTY LINE
			continue ;

		tokens = splitString(buff, ' ');

		if (tokens[0] == "\t\troot")
			location.setRoot(tokens, lineNumber);  // SET ROOT ATTRIBUTE OF THE SERVER
		else if (tokens[0] == "\t\tindex")
			location.setIndex(tokens, lineNumber); // SET INDEX ATTRIBUTE OF THE SERVER
		else if (tokens[0] == "\t\tupload_pass")
			location.setUpload(tokens, lineNumber); // SET UPLOAD ATTRIBUTE OF THE SERVER
		else if (tokens[0] == "\t\tcgi_pass")
			location.setCgi(tokens, lineNumber); // SET CGI ATTRIBUTE OF THE SERVER
		else if (tokens[0] == "\t\tautoindex")
			location.setAutoindex(tokens, lineNumber); // SET AUTOINDEX ATTRIBUTE OF THE SERVER
		else if (tokens[0] == "\t\tallow_methods")
			location.setAllowedMethods(tokens, lineNumber); // SET ALLOWEDMETHODS ATTRIBUTE OF THE SERVER
		else if (tokens[0] == "\t\treturn")
			location.setRedirection(tokens, lineNumber); // SET REDIRECCTION  ATTRIBUTE OF THE SERVER
		else
			return 1; // DIRECTIVE DOESN'T BELONGS TO THE LOCATION DIRECTIVE

	} // GETTING LINES FROM THE FILE

	return 0; // THE END OF THE FILE

}

void	ContextManager::addServer()
{

	if (servers.size()) // fill out the last server with its config attributes
	{
		servers.back().addConfigAttr(configAttr);
		servers.back().attributeExaminer();
	}

	if (servers.size() > 1 && portServer.count(servers.back().getPort())) // if a server is already using the same port as this server then merge them
	{
		unsigned int	index = portServer[servers.back().getPort()];
		if (servers[index].getHostName() == servers.back().getHostName())
			throw "\"" + servers.back().getHostName() + "\" already exist on the same port!";
		servers[index] += servers.back();
		servers.pop_back();
	}
	else if (servers.size()) // if no server is using the same port as this server then save its index in the memo "portServer"
		portServer[servers.back().getPort()] = servers.size() - 1;


}

int	 ContextManager::parseServer()
{
	if (trimString(buff) == "server")
	{

		addServer();
		servers.push_back(Server()); // push the server to the set
		configAttr.clear();
		return 1;
	}



	if (!servers.size())
		throw "unknown directive in serv.conf:" + std::to_string(lineNumber);
	else if (tokens[0] == "\tlocation")
	{
		if (!parseLocation(configAttr.locations[tokens[1]]))
			return 0;
		parseServer();
		return 1;
	}

	if (tokens[0] == "\thost")
		servers.back().setHostName(tokens, lineNumber);
	else if (tokens[0] == "\tport")
		servers.back().setPort(tokens, lineNumber);
	else if (tokens[0] == "\tclient_max_body_size")
		configAttr.setClientMaxBodySize(tokens, lineNumber);

	else if (tokens[0] == "\terror_page")
		configAttr.setErrorPages(tokens, lineNumber);
	else
		throw "unknown directive in serv.conf:" + std::to_string(lineNumber);


	return 1;
}


void	ContextManager::parseConfigFIle()
{
	while (std::getline(configFIle, buff))
	{
		++lineNumber;

		if (!buff.length() || containsOnlyWhitespaces(buff))
			continue ;

		tokens = splitString(buff, ' ');


		if (!parseServer())
			return ;
	}

	addServer();

}
