#include <array>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

#include "cat_posix.hpp"

constexpr size_t BUFFER_SIZE = 8192;

void copy_fd(int fd)
{
    std::array<std::byte, BUFFER_SIZE> buffer;

    while (true)
    {
        ssize_t bytes_read = read(fd, buffer.data(), buffer.size());

        if (bytes_read == 0)
        {
            return;
        }

        if (bytes_read < 0)
        {
            perror("read");
            return;
        }

        ssize_t bytes_written = 0;

        while (bytes_written < bytes_read)
        {
            ssize_t n =
                write(STDOUT_FILENO, buffer.data() + bytes_written, bytes_read - bytes_written);

            if (n < 0)
            {
                perror("write");
                return;
            }

            bytes_written += n;
        }
    }
}
