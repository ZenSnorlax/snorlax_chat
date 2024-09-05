#include "mysql.h"
#include "redis.h"
#include "websocket_server.h"
#include <iostream>

int main() {
    try {
        Mysql mysql("127.0.0.1", "abs", 33060, "1510017673", "my_database");
        Redis redis("redis://127.0.0.1:6379");

        auto &server =
            websocketServer::instance(std::move(mysql), std::move(redis));
        server.start(); // 启动 WebSocket 服务器
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
