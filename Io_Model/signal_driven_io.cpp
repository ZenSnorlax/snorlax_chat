#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

volatile sig_atomic_t dataReady = 0;

void signalHandler(int signum) {
    dataReady = 1;
}

int main() {
    int fd = open("example.txt", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGIO, &sa, NULL) == -1) {
        std::cerr << "Failed to set signal handler.\n";
        close(fd);
        return 1;
    }

    if (fcntl(fd, F_SETOWN, getpid()) == -1 || fcntl(fd, F_SETFL, O_NONBLOCK | O_ASYNC) == -1) {
        std::cerr << "Failed to set file descriptor flags.\n";
        close(fd);
        return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;

    while (true) {
        if (dataReady) {
            dataReady = 0;
            while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
                buffer[bytesRead] = '\0';
                std::cout << buffer;
            }

            if (bytesRead == -1 && errno != EAGAIN) {
                std::cerr << "Read error.\n";
                close(fd);
                return 1;
            }
        }

        // Do other work here...
    }

    close(fd);
    return 0;
}
