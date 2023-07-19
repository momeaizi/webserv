#include "../includes/Location.hpp"


bool       	Location::locationHasCgi()
{
	return cgi.size();
}

void    Location::setAutoindex(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() != 2)
		throw "invalid number of arguments in \"tautoindex\" directive in serv.conf:" + std::to_string(lineNumber);

	if (tokens[1] != "on" && tokens[1] != "off")
		throw "invalid value \"" + tokens[1] + "\" in \"autoindex\" directive, it must be \"on\" or \"off\"";

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
	
	if (!containsOnlyDigits(tokens[1]))
        throw "invalid return code \"" + tokens[1] + "\" in serv.conf:" + std::to_string(lineNumber);
	int	code = atoi(tokens[1].c_str());

	if (code > 302 || code < 301)
        throw "return code must be 301 or 302 in serv.conf:" + std::to_string(lineNumber);;
	
	redirection = make_pair(code, tokens[2]);
}

void    Location::setCgi(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() != 3)
		throw "invalid number of arguments in \"cgi_pass\" directive in serv.conf:" + std::to_string(lineNumber);
	
	if (tokens[1] != "py" && tokens[1] != "php")
		throw "\"" + tokens[1] + "\" not supported";

	cgi[tokens[1]] = tokens[2];
}

void    Location::setAllowedMethods(std::vector<std::string> &tokens, unsigned int lineNumber)
{
	if (tokens.size() < 2)
		throw "invalid number of arguments in \"allow_methods\" directive in serv.conf:" + std::to_string(lineNumber);

	for (size_t  i = 1; i < tokens.size(); ++i)
	{
		if (tokens[1] != "GET" && tokens[1] != "POST" && tokens[1] != "DELETE")
			throw "method \"" + tokens[1] + "\" not supported";
		allowedMethods.insert(tokens[i]);
	}
}


bool                                        Location::getAutoindex() const
{
	return autoindex;
}

const std::string                           &Location::getRoot() const
{
	return root;
}

const std::string                           &Location::getIndex() const
{
	return index;
}

const std::string                           &Location::getUpload() const
{
	return upload;
}

const std::pair<int, std::string>           &Location::getRedirection() const
{
	return redirection;
}

const std::map<std::string, std::string>    &Location::getCgi() const
{
	return cgi;
}

const std::string   &Location::getCgiVal(std::string key)
{
	if (!cgi.count(key))
		return "";
	return cgi[key];
}

const std::set<std::string>                 &Location::getAllowedMethods() const
{
	return allowedMethods;
}
