#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;          // From <boost/beast.hpp>
namespace websocket = beast::websocket;  // From <boost/beast/websocket.hpp>
namespace net = boost::asio;             // From <boost/asio.hpp>
using tcp = net::ip::tcp;                // From <boost/asio/ip/tcp.hpp>

class WebSession : public std::enable_shared_from_this<WebSession> {
   public:
    explicit WebSession(tcp::socket socket) : ws_(std::move(socket)) {}

    void start() {
        ws_.async_accept([self = shared_from_this()](beast::error_code ec) {
            if (ec) {
                std::cerr << "WebSocket accept error: " << ec.message()
                          << std::endl;
                return;
            }
            self->do_read();
        });
    }

   private:
    websocket::stream<tcp::socket> ws_;
    beast::flat_buffer buffer_;

    std::string username;
    std::string password_hash;
    
    void do_read() {
        ws_.async_read(
            buffer_,
            [self = shared_from_this()](beast::error_code ec, std::size_t) {
                if (ec) {
                    std::cerr << "Read error: " << ec.message() << std::endl;
                    return;
                }
                std::cout << "Received message: "
                          << beast::make_printable(self->buffer_.data())
                          << std::endl;
                self->do_write();  // Echo the message back
            });
    }

    void do_write() {
        ws_.async_write(
            buffer_.data(),
            [self = shared_from_this()](beast::error_code ec, std::size_t) {
                if (ec) {
                    std::cerr << "Write error: " << ec.message() << std::endl;
                    return;
                }
                self->buffer_.consume(self->buffer_.size());
                self->do_read();  // Continue reading messages
            });
    }
};

class WebSocketServer {
   public:
    WebSocketServer(net::io_context& ioc, tcp::endpoint endpoint)
        : acceptor_(ioc, endpoint) {}

    void start() { do_accept(); }

   private:
    tcp::acceptor acceptor_;

    void do_accept() {
        acceptor_.async_accept(
            [this](beast::error_code ec, tcp::socket socket) {
                if (ec) {
                    std::cerr << "Accept error: " << ec.message() << std::endl;
                } else {
                    std::make_shared<WebSession>(std::move(socket))->start();
                }
                do_accept();  // Accept the next connection
            });
    }
};
