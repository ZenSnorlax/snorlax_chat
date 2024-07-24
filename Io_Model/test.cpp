#include <condition_variable>
#include <csignal>
#include <mutex>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <thread>

int main() {
    int server_fd, epoll_fd;
    struct sockaddr_in address;
    server_fd = socket(AF_INET,  SOCK_STREAM,  0);
    
    
}