//
//
#include "ws/ws_server.h"
#include "mgr/user_mgr.h"
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <thread>

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace websocket = beast::websocket;

websocketServer &websocketServer::instance(manager::Users &users) {
    static websocketServer server(users);
    return server;
}

websocketServer::websocketServer(manager::Users &users)
    : users_(std::move(users)) {}

[[noreturn]] void websocketServer::start() {
    net::io_context ioc;
    tcp::acceptor acceptor(ioc, {tcp::v4(), 9001});
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    acceptor.listen();
    std::cout << "WebSocket server listening on port 9001..." << std::endl;

    while (true) {
        tcp::socket socket(ioc);
        acceptor.accept(socket);
        std::cout << "Accepted a new connection." << std::endl;

        std::thread([sock = std::move(socket)]() mutable {
            try {
                websocket::stream<tcp::socket> ws(std::move(sock));

                ws.accept();
                while (true) {
                    beast::flat_buffer buffer;
                    ws.read(buffer);
                    ws.text(ws.got_text());
                    ws.write(buffer.data());
                }
            } catch (const beast::system_error &se) {
                std::cerr << "WebSocket error: " << se.what() << std::endl;
            }
        }).detach();
    }
}
