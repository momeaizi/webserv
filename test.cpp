
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>

int main()
{
    int in = open("test.txt", O_RDWR);
    int out = open("test1.txt", O_RDWR);


    int     status;
    int childPID = fork();

    if (childPID < 0)
        std::cerr <<  "Fork failed!" << std::endl;
    else if (!childPID)
    {
        dup2(in, 0);
        dup2(out, 1);
        close(in);
        close(out);



        char    **argv = new char*[3];

        argv[0] = new char[4];
        memcpy(argv[0], "php", 3);
        argv[0][3] = '\0';

        argv[1] = new char[42];
        memcpy(argv[1], "/Users/momeaizi/goinfre/webserv/index.php", 41);
        argv[1][41] = '\0';

        argv[2] = NULL;

        if (execve("/usr/bin/php", argv, NULL) < 0)
            std::cerr << "execve failed!" << std::endl;

        exit(1);
    }
    write(in, "tahameaizi", 10);
    while (1)
    { 

        waitpid(childPID, &status, WNOHANG);
        if (WIFEXITED(status))
        {
            int exitstatus = WEXITSTATUS(status);

            std::cout << exitstatus << std::endl;

            char buff[10];
            while (read(out, buff, 10))
            {
                std::cout << std::string(buff, 10);
            }
            std::cout << std::endl;
            break ;
        }
    }
    close(in);
    close(out);
}