#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = net::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

// 会话类：处理 WebSocket 连接
class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
  public:
    WebSocketSession(tcp::socket socket) : ws_(std::move(socket)) {}

    void start() {
        // 执行 WebSocket 握手操作
        ws_.async_accept([self = shared_from_this()](beast::error_code ec) {
            if (!ec) {
                self->do_read();
            }
        });
    }

  private:
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;

    void do_read() {
        ws_.async_read(
            buffer_,
            [self = shared_from_this()](beast::error_code ec,
                                        std::size_t bytes_transferred) {
                boost::ignore_unused(bytes_transferred);

                if (!ec) {
                    // 将消息写回客户端（Echo 服务器）
                    self->do_write();
                }
            });
    }

    void do_write() {
        ws_.async_write(
            buffer_.data(),
            [self = shared_from_this()](beast::error_code ec,
                                        std::size_t bytes_transferred) {
                boost::ignore_unused(bytes_transferred);

                if (!ec) {
                    // 清空缓冲区并继续读取
                    self->buffer_.consume(self->buffer_.size());
                    self->do_read();
                }
            });
    }
};

void do_accept(tcp::acceptor &acceptor, tcp::socket &socket) {
    acceptor.async_accept(socket, [&](beast::error_code ec) {
        if (!ec) {
            // 启动新的会话
            std::make_shared<WebSocketSession>(std::move(socket))->start();
        }
        // 继续接受连接
        do_accept(acceptor, socket);
    });
}

int main() {
    try {
        net::io_context ioc{1};

        // 监听端口 8080
        tcp::acceptor acceptor{ioc, {tcp::v4(), 8080}};
        tcp::socket socket{ioc};

        do_accept(acceptor, socket);

        // 运行 I/O 上下文
        ioc.run();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
