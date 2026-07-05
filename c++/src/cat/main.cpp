#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include "cat_posix.hpp"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        copy_fd(STDIN_FILENO);
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);

        if (fd < 0)
        {
            perror(argv[i]);
            continue;
        }

        copy_fd(fd);
        close(fd);
    }

    return 0;
}
