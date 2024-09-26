#include "websocket_server.hpp"

#include <memory>

#include "../bll/message_handle_factory.hpp"
#include "../bll/message_paraser.hpp"
#include "../log/snorlax_log.hpp"

WebSocketSession::WebSocketSession(tcp::socket socket)
    : ws_(std::move(socket)) {}

void WebSocketSession::start() {
    ws_.async_accept([self = shared_from_this()](beast::error_code ec) {
        self->on_accept(ec);
    });
}

websocket::stream<tcp::socket>& WebSocketSession::getWebSocketStream() {
    return ws_;
}

void WebSocketSession::on_accept(beast::error_code ec) {
    if (ec) {
        LOG(Level::ERROR, "Accept failed: ", ec.message());
        return;
    }
    read_message();
}

void WebSocketSession::read_message() {
    ws_.async_read(buffer_,
                   [self = shared_from_this()](beast::error_code ec,
                                               std::size_t bytes_transferred) {
                       self->on_read(ec, bytes_transferred);
                   });
}

void WebSocketSession::on_read(beast::error_code ec,
                               std::size_t bytes_transferred) {
    if (ec) {
        LOG(Level::ERROR, "Read failed: ", ec.message());
        return;
    }

    std::string message = beast::buffers_to_string(buffer_.data());
    LOG(Level::INFO, "Received message: ", message);

    buffer_.consume(bytes_transferred);
    handle_message(message);
}

void WebSocketSession::handle_message(const std::string& message) {
    // 使用智能指针管理 MessageParse 对象
    auto parsed_message = std::make_unique<MessageParse>(message);
    // 使用工厂类创建消息处理器
    auto message_ = Message(parsed_message->getMessageType(),
                            parsed_message->getSender(),
                            parsed_message->getReceiver(),
                            parsed_message->getContent());
    auto message_handle = MessageHandleFactory::createHandle(message_);
    if (message_handle) {
        message_handle->handle(shared_from_this(), std::move(parsed_message));
    } else {
        LOG(Level::WARNING,
            "Unknown message type: ",
            parsed_message->getMessageType());
    }
    // 读取下一条对话
    read_message();
}

WebSocketServer::WebSocketServer(net::io_context& ioc, tcp::endpoint endpoint)
    : acceptor_(ioc) {
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(net::socket_base::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen(net::socket_base::max_listen_connections);
    do_accept();
}

void WebSocketServer::do_accept() {
    acceptor_.async_accept([this](beast::error_code ec, tcp::socket socket) {
        if (!ec) {
            auto session =
                std::make_shared<WebSocketSession>(std::move(socket));
            session->start();
        } else {
            LOG(Level::ERROR, "Accept failed: ", ec.message());
        }
        // 继续接受下一个连接
        do_accept();
    });
}
