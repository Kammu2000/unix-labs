#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include "parser.hpp"
#include "xargs.hpp"

void xargs(const XargsOption& options)
{
    std::vector<std::string> command = std::move(options.command);
    std::vector<char*> args;

    std::string token;

    while (std::cin >> token)
    {
        command.push_back(token);
    }

    pid_t pid = fork();

    if (pid == 0)
    {
        for (auto& word : command)
        {
            args.push_back(const_cast<char*>(word.c_str()));
        }

        execvp(args[0], args.data());
        perror("Could not execute command");
        exit(1);
    }

    waitpid(pid, nullptr, 0);
}
