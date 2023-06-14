#include "Location.hpp"

std::string	Location::GetUpload()
{
	return this->upload;
}

std::string	Location::GetIndex()
{
	return this->index;
}

bool       	Location::LocationHasCgi()
{
	return cgi.size();
}

void    Location::setAutoindex(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() != 2)
		throw "invalid number of arguments in \"tautoindex\" directive in serv.conf:" + std::to_string(lineNumber);
	if (tokens[1] != "on" && tokens[1] != "off")
		throw "argumnet of autoindex should be on or off";

	autoindex = (tokens[1].size() == 2) ? true : false;
}

void    Location::setRoot(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() != 2)
		throw "invalid number of arguments in \"root\" directive in serv.conf:" + std::to_string(lineNumber);
	root = tokens[1];
}

void    Location::setIndex(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() != 2)
		throw "invalid number of arguments in \"index\" directive in serv.conf:" + std::to_string(lineNumber);
	index = tokens[1];
}

void    Location::setUpload(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() != 2)
		throw "invalid number of arguments in \"upload_pass\" directive in serv.conf:" + std::to_string(lineNumber);
	upload = tokens[1];
}

void    Location::setRedirection(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() != 3)
		throw "invalid number of arguments in \"client_max_body_size\" directive in serv.conf:" + std::to_string(lineNumber);
	redirection = make_pair(atoi(tokens[1].c_str()), tokens[2]);
}

void    Location::setCgi(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() != 3)
		throw "invalid number of arguments in \"cgi_pass\" directive in serv.conf:" + std::to_string(lineNumber);
	cgi[tokens[1]] = tokens[2];
}

void    Location::setAllowedMethods(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() < 2)
		throw "invalid number of arguments in \"allow_methods\" directive in serv.conf:" + std::to_string(lineNumber);

	for (size_t  i = 1; i < tokens.size(); ++i)
		allowedMethods.insert(tokens[i]);
}