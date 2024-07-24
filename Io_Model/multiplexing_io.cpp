#include <fcntl.h>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_RDONLY | O_NONBLOCK);

    if (fd == -1) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    fd_set readfds;
    char buffer[1024];
    ssize_t bytesRead;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        int result = select(fd + 1, &readfds, NULL, NULL, NULL);

        if (result == -1) {
            std::cerr << "Select error.\n";
            close(fd);
            return 1;
        } else if (result > 0) {
            if (FD_ISSET(fd, &readfds)) {
                bytesRead = read(fd, buffer, sizeof(buffer) - 1);
                if (bytesRead == 0) {
                    // EOF
                    break;
                } else if (bytesRead == -1) {
                    std::cerr << "Read error.\n";
                    close(fd);
                    return 1;
                }

                buffer[bytesRead] = '\0';
                std::cout << buffer;
            }
        }
    }

    close(fd);
    return 0;
}
