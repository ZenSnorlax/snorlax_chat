#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

constexpr int port = 8080;
constexpr const char *server_ip = "127.0.0.1";

class Server {
  public:
    Server() : server_socket(-1) {}
    bool start() {
        // 创建Socket
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1) {
            std::cerr << "socket error" << std::endl;
            return false;
        }
        // 绑定
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr(server_ip);
        if (bind(server_socket,
                 reinterpret_cast<sockaddr *>(&server_addr),
                 sizeof(server_addr)) == -1) {
            std::cerr << "bind error" << std::endl;
            close(server_socket);
            return false;
        }
        // 监听
        if (listen(server_socket, 5) == -1) {
            std::cerr << "listen error" << std::endl;
            close(server_socket);
            return false;
        }
        return true;
    }

    ~Server() { close(server_socket); }

  private:
    int server_socket;
};