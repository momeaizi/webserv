# include "../includes/Client.hpp"

void Client::runCGI()
{
    std::string filename = "/tmp/" + initializeupload();
    serve = &Client::writeInCGI;

    Rfd = open(filename.c_str(), O_RDWR);
    uploadFile.open(filename);

    childPID = fork();
    dup2(Rfd, 0);
    dup2(Rfd, 1);
    if (!childPID)
    {
        // execve();
        sleep(60);
        exit(1);
    }
    else if (childPID < 0)
        throw "Fork failed.";
    writeInCGI();
}


void Client::CGIHeaders()
{
    std::list<std::string>              lines;
    std::list<std::string>::iterator    it;

    lines = getlines(this->buffer);
    if (resourceSize > CHUNK_SIZE)
        response += "Transfer-Encoding: chunked\r\n";
    for (it = lines.begin(); it != lines.end(); it++)
    {
        std::string &str = *it;

        if (str.empty())
        {
            response += "\r\n";
            serve = &Client::GetFromFile;
            return ;
        }
        response += str + "\r\n";
    }
}