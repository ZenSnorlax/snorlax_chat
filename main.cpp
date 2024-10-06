/*
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
*/

#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    
    nlohmann::json json_obj = {
        {"username", "user123"}, {"password", "pass123"}, {"type", "login"}};

    
    std::cout << json_obj.dump() << std::endl;

    
    std::string username = json_obj["username"];
    std::string type = json_obj["type"];

    std::cout << "Username: " << username << std::endl;
    std::cout << "Type: " << type << std::endl;

    return 0;
}
