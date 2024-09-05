//
//
#include "websocket_server.h"
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <thread>

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace websocket = beast::websocket;

websocketServer &websocketServer::instance(Mysql &&mysql, Redis &&redis) {
    static websocketServer server(std::move(mysql), std::move(redis));
    return server;
}

websocketServer::websocketServer(Mysql &&mysql, Redis &&redis)
    : mysql_(std::move(mysql)), redis_(std::move(redis)) {}

[[noreturn]] void websocketServer::start() {
    net::io_context ioc;
    tcp::acceptor acceptor(ioc, {tcp::v4(), 9001});
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    acceptor.listen();
    std::cout << "WebSocket server listening on port 9001..." << std::endl;

    for (;;) {
        tcp::socket socket(ioc);
        acceptor.accept(socket);
        std::cout << "Accepted a new connection." << std::endl;

        std::thread([sock = std::move(socket)]() mutable {
            try {
                websocket::stream<tcp::socket> ws(std::move(sock));
                ws.accept();
                for (;;) {
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
