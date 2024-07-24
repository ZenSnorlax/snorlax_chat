#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_RDONLY | O_NONBLOCK);

    if (fd == -1) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) != 0) {
        if (bytesRead == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // No data available, continue or sleep
                continue;
            } else {
                std::cerr << "Read error.\n";
                close(fd);
                return 1;
            }
        }

        buffer[bytesRead] = '\0';
        std::cout << buffer;
    }

    close(fd);
    return 0;
}
