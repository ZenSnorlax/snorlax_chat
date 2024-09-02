#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
constexpr int port = 8080;
constexpr const char *server_ip = "127.0.0.1";
int main() {
    // 创建Socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "socket error" << std::endl;
        return -1;
    }

    // 连接服务器
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(client_socket, (sockaddr *)&server_addr, sizeof(server_addr)) ==
        -1) {
        std::cerr << "connect error" << std::endl;
        close(client_socket);
        return -1;
    }

    std::cout << "connect success" << std::endl;
    // 发送数据
    char buf[] = "hello world";
    int ret = send(client_socket, buf, strlen(buf), 0);
    if (ret == -1) {
        std::cerr << "send error" << std::endl;
        close(client_socket);
        return -1;
    }
    // 接受服务器发送的数据
    char recv_buf[1024] = {0};
    ret = recv(client_socket, recv_buf, sizeof(recv_buf), 0);
    if (ret == -1) {
        std::cerr << "recv error" << std::endl;
        close(client_socket);
        return -1;
    }
    std::cout << "recv: " << recv_buf << std::endl;
    close(client_socket);
    return 0;
}