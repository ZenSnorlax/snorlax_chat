#include <aio.h>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

void aio_completion_handler(sigval_t sigval) {
    struct aiocb *req = (struct aiocb *)sigval.sival_ptr;

    if (aio_error(req) == 0) {
        ssize_t bytesRead = aio_return(req);
        std::cout.write((char *)req->aio_buf, bytesRead);
        std::cout << "completion!" << std::endl;
    } else {
        std::cerr << "AIO error.\n";
    }
}

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    char buffer[1024];
    struct aiocb cb;
    memset(&cb, 0, sizeof(cb));
    cb.aio_fildes = fd;
    cb.aio_buf = buffer;
    cb.aio_nbytes = sizeof(buffer) - 1;
    cb.aio_sigevent.sigev_notify = SIGEV_THREAD;
    cb.aio_sigevent.sigev_notify_function = aio_completion_handler;
    cb.aio_sigevent.sigev_notify_attributes = NULL;
    cb.aio_sigevent.sigev_value.sival_ptr = &cb;

    if (aio_read(&cb) == -1) {
        std::cerr << "AIO read error.\n";
        close(fd);
        return 1;
    }

    // Do other work here...

    // Wait for the AIO operation to complete
    while (aio_error(&cb) == EINPROGRESS) {
        // Busy wait
    }

    close(fd);
    return 0;
}
