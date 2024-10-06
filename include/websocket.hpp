#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_set>

namespace beast = boost::beast;          // From <boost/beast.hpp>
namespace websocket = beast::websocket;  // From <boost/beast/websocket.hpp>
namespace net = boost::asio;             // From <boost/asio.hpp>
using tcp = net::ip::tcp;                // From <boost/asio/ip/tcp.hpp>

class WebSession : public std::enable_shared_from_this<WebSession> {
   public:
    WebSession(tcp::socket socket,
               std::unordered_set<std::shared_ptr<WebSession>>& sessions,
               std::mutex& mutex)
        : ws_(std::move(socket)), sessions_(sessions), sessions_mutex_(mutex) {}

    void start() {
        {
            std::lock_guard<std::mutex> lock(sessions_mutex_);
            sessions_.insert(shared_from_this());
        }

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
    std::unordered_set<std::shared_ptr<WebSession>>& sessions_;
    std::mutex& sessions_mutex_;

    void do_read() {
        ws_.async_read(
            buffer_,
            [self = shared_from_this()](beast::error_code ec, std::size_t) {
                if (ec == websocket::error::closed) {
                    std::cerr << "Connection closed: " << ec.message()
                              << std::endl;
                    self->destroy();
                    return;
                } else if (ec) {
                    self->handle_error(ec);
                    return;
                }

                std::string message =
                    beast::buffers_to_string(self->buffer_.data());
                std::cout << "Received message: " << message << std::endl;

                self->broadcast(message);
                self->buffer_.consume(self->buffer_.size());
                self->do_read();
            });
    }

    void broadcast(const std::string& message) {
        std::lock_guard<std::mutex> lock(sessions_mutex_);
        for (const auto& session : sessions_) {
            std::cout << "Broadcast message: " << message << std::endl;
            if (session != shared_from_this()) {
                session->send(message);
            }
        }
    }

    void send(const std::string& message) {
        ws_.async_write(
            net::buffer(message),
            [self = shared_from_this()](beast::error_code ec, std::size_t) {
                if (ec) {
                    std::cerr << "Write error: " << ec.message() << std::endl;
                }
            });
    }

    void handle_error(beast::error_code ec) {
        std::cerr << "Error: " << ec.message() << std::endl;
        destroy();
    }

    void destroy() {
        std::lock_guard<std::mutex> lock(sessions_mutex_);
        sessions_.erase(shared_from_this());
    }
};

class WebSocketServer {
   public:
    WebSocketServer(net::io_context& ioc, tcp::endpoint endpoint)
        : acceptor_(ioc, endpoint) {}

    void start() { do_accept(); }

   private:
    tcp::acceptor acceptor_;
    std::unordered_set<std::shared_ptr<WebSession>> sessions_;
    std::mutex sessions_mutex_;

    void do_accept() {
        acceptor_.async_accept(
            [this](beast::error_code ec, tcp::socket socket) {
                if (ec) {
                    std::cerr << "Accept error: " << ec.message() << std::endl;
                } else {
                    std::make_shared<WebSession>(
                        std::move(socket), sessions_, sessions_mutex_)
                        ->start();
                }
                do_accept();
            });
    }
};
