# include "../includes/Client.hpp"

std::string URLDecode(const std::string &url)
{
    std::string decoded;
    
    for (std::size_t i = 0; i < url.length(); ++i)
    {
        if (url[i] == '%')
        {
            int hexValue = stoi(url.substr(i + 1, 2), nullptr, 16);
            decoded += static_cast<char>(hexValue);
            i += 2;
        }
        else if (url[i] == '+')
            decoded += ' ';
        else
            decoded += url[i];
    }
    
    return decoded;
}


int IsUriValid(std::string &str)
{
    const std::string &allowed = ALLOWED_CHAR_IN_URI;
    for(size_t i = 0; i < str.size(); ++i)
        if (allowed.find(str[i]) == std::string::npos)
            return 0;
    try
    {
        str = URLDecode(str);
    }
    catch (...)
    {
        return 0;
    }
    return 1; 
}


void    Client::setQuerieString()
{
    size_t  i = URI.find('?');
    if (i == std::string::npos)
        return ;
    querieString = URI.substr(i + 1);
    URI = URI.substr(0, i);
}



int IsMethodValid(const std::string &method, const std::set<std::string> &allowedMethods)
{
    if (!allowedMethods.count(method))
        return 0;
    return 1; 
}



void Client::parse()
{
    std::list<std::string>              lines;
    std::list<std::string>::iterator    it;
    size_t                              first;

    lines = getlines(this->buffer);
    if (lines.empty())
        return ;

    for (it = lines.begin(); it != lines.end(); it++)
    {
        std::string &str = *it;

        if (str == "")
        {
            if (methodType == "GET")
                this->serve = &Client::GetHandler;
            else if (methodType == "POST")
                this->serve = &Client::PostHandler;
            else
                this->serve = &Client::DeleteHandler;

            return ;
        }
        if (this->methodType == "") 
        {
            int errorCode = 0;


            this->methodType = tok(str, " ");
            first = str.find_first_not_of(' ');
            str = str.substr(first);
            URI = tok(str, " ");


            if (!IsUriValid(URI))
                errorCode = 400;

            setQuerieString();
            std::cout << "Q -> " << querieString << std::endl;
            std::pair<std::string, Location*> loc = server.getMatchedLocation(URI);
            this->location = loc.second;


            if (!errorCode && !location)
                errorCode = 404;
            else
                this->resource = location->getRoot() + URI;
            if (!errorCode && location->getRedirection().first)
                errorCode = location->getRedirection().first;
            if (!errorCode && !IsMethodValid(methodType, location->getAllowedMethods()))
                errorCode = 405;
            if (!errorCode && URI.length() > MAX)
                errorCode = 414;


            first = str.find_first_not_of(' ');
            str = str.substr(first);
            if (!errorCode && tok(str, "\r\n") != "HTTP/1.1")
                errorCode = 505;
            if (errorCode)
            {
                setHeader(errorCode);
                return ;
            }
        }
        else
        {
            int             index = str.find(":");
            int             len   = str.length();
            std::string     name  = to_lower(str.substr(0, index));

            if (this->headerFields.count(name) or index == -1)
            {
                setHeader(400);
                return ;
            }
            std::string   val = str.substr(index + 1, len);
            headerFields [name] = trimString(val);
        }
    }
}