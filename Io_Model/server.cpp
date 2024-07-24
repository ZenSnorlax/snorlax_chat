#include <condition_variable>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <netinet/in.h>
#include <queue>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

const int MAX_EVENTS = 10;
const int BUFFER_SIZE = 1024;
const int PORT = 7070;

std::mutex queue_mutex;
std::queue<int> request_queue;
std::condition_variable cv;
bool server_running = true;

void handle_client_request(int client_fd) {
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        const char *response =
            "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";
        write(client_fd, response, strlen(response));
    }
    close(client_fd);
}

void worker_thread() {
    while (server_running) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        cv.wait(lock, [] { return !request_queue.empty() || !server_running; });

        while (!request_queue.empty()) {
            int client_fd = request_queue.front();
            request_queue.pop();
            lock.unlock();
            handle_client_request(client_fd);
            lock.lock();
        }
    }
}

void signal_handler(int signal) {
    if (signal == SIGINT) {
        server_running = false;
        cv.notify_all();
    }
}

int main() {
    signal(SIGINT, signal_handler);

    int server_fd, epoll_fd;
    struct sockaddr_in address;
    struct epoll_event event, events[MAX_EVENTS];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1 failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    event.events = EPOLLIN;
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
        perror("epoll_ctl failed");
        close(server_fd);
        close(epoll_fd);
        exit(EXIT_FAILURE);
    }

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; ++i) {
        workers.emplace_back(worker_thread);
    }

    while (server_running) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == server_fd) {
                int client_fd = accept(server_fd, NULL, NULL);
                if (client_fd == -1) {
                    perror("accept failed");
                } else {
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    request_queue.push(client_fd);
                    cv.notify_one();
                }
            }
        }
    }

    for (auto &worker : workers) {
        worker.join();
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}
