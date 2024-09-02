#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // 创建Socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "socket error" << std::endl;
        return -1;
    }
    // 绑定IP地址和端口
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);       // 使用8080端口
    server_addr.sin_addr.s_addr = INADDR_ANY; // 绑定到本地任意IP地址

    if (bind(server_socket, (sockaddr *)&server_addr, sizeof(server_addr)) ==
        -1) {
        std::cerr << "Failed to bind socket!" << std::endl;
        close(server_socket);
        return -1;
    }

    // 监听
    if (listen(server_socket, 5) == -1) {
        std::cerr << "listen error" << std::endl;
        close(server_socket);
        return -1;
    }
    // 等待客户端连接
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_socket =
        accept(server_socket, (sockaddr *)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        std::cerr << "accept error" << std::endl;
        close(server_socket);
        return -1;
    }
    // 接收数据
    char buf[1024] = {0};
    memset(buf, 0, sizeof(buf));
    int ret = recv(client_socket, buf, sizeof(buf), 0);
    if (ret == -1) {
        std::cerr << "recv error" << std::endl;
        close(server_socket);
        close(client_socket);
        return -1;
    }
    std::cout << "recv: " << buf << std::endl;
    // 发送数据
    ret = send(client_socket, buf, strlen(buf), 0);
    if (ret == -1) {
        std::cerr << "send error" << std::endl;
        close(server_socket);
        close(client_socket);
        return -1;
    }
    // 关闭套接字
    close(server_socket);
    close(client_socket);
    return 0;
}