# include "../includes/Client.hpp"


// int get_fd(std::fstream &file)
// {
//     int             fd = -1;
//     std::filebuf    *fbuf = file.rdbuf();
//     if (fbuf)
//     {
//         fd = ::fileno(fbuf->native_handle());
//     }
//     return fd;
// }

void    Client::fillCgiEnv()
{
    // std::string env;

    // env = std::string("REQUEST_METHOD") + "=" + methodType + ";";
    // if (!querieString.empty())
    //     env += std::string("QUERY_STRING") + "=" + querieString + ";";
    // if (!headerFields["content-type"].empty())
    //     env += std::string("CONTENT_TYPE") + "=" + headerFields["content-type"] + ";";
    // if (!headerFields["content-length"].empty())
    //     env += std::string("CONTENT_LENGTH") + "=" + headerFields["content-length"] + ";";
    // if (!headerFields["cookie"].empty())
    //     env += std::string("HTTP_COOKIE") + "=" + headerFields["cookie"] + ";";
    // if (!headerFields["user-agent"].empty())
    //     env += std::string("HTTP_USER_AGENT") + "=" + headerFields["user-agent"] + ";";
    // env += std::string("REMOTE_ADDR") + "=" + ipAddress + ";";
    // env += std::string("SERVER_NAME") + "=" + server.getHostName() + ";";
    // env += std::string("SERVER_PORT") + "=" + server.getPort() + ";";

    // std::cout << env << std::endl;

}


void Client::runCGI()
{
    // std::string filename = "/tmp/" + initializeupload();
    // serve = &Client::writeInCGI;

    // Rfd = open(filename.c_str(), O_RDWR);
    // uploadFile.open(filename);

    // childPID = fork();
    // dup2(Rfd, 0);
    // dup2(Rfd, 1);
    // if (!childPID)
    // {
    //     // execve();
    //     sleep(60);
    //     exit(1);
    // }
    // else if (childPID < 0)
    //     throw "Fork failed.";
    // writeInCGI();
}


void Client::CGIHeaders()
{
    // std::list<std::string>              lines;
    // std::list<std::string>::iterator    it;

    // lines = getlines(this->buffer);
    // if (resourceSize > CHUNK_SIZE)
    //     response += "Transfer-Encoding: chunked\r\n";
    // for (it = lines.begin(); it != lines.end(); it++)
    // {
    //     std::string &str = *it;

    //     if (str.empty())
    //     {
    //         response += "\r\n";
    //         serve = &Client::GetFromFile;
    //         return ;
    //     }
    //     response += str + "\r\n";
    // }
}