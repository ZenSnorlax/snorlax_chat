#include "db/conn_pool.h"
#include "db/db_init.h"
#include "mgr/user_mgr.h"
#include "ws/ws_server.h"
#include <iostream>

int main() {
    try {
        database::Initializer initializer(
            "127.0.0.1", 33060, "abs", "1510017673", "my_database");

        database::ConnectionPool::instance(initializer, 10);

        manager::Users users(initializer.getSession());

        auto &server = websocketServer::instance(users);
        server.start(); // 启动 WebSocket 服务器
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
