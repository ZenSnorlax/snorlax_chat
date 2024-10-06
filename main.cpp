#include "websocket.hpp"

int main() {
    try {
        net::io_context ioc;
        tcp::endpoint endpoint(tcp::v4(), 8080);
        WebSocketServer server(ioc, endpoint);
        server.start();
        ioc.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
