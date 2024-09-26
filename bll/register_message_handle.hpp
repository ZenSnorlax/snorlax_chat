#ifndef REGISTER_MESSAGE_HANDLE_HPP
#define REGISTER_MESSAGE_HANDLE_HPP

#include <boost/beast/core.hpp>
#include <boost/json.hpp>

#include "../dal/user_dao.hpp"
#include "../server/websocket_server.hpp"
#include "message_handle.hpp"

class RegisterMessageHandle
    : public MessageHandle,
      public std::enable_shared_from_this<RegisterMessageHandle> {
   public:
    RegisterMessageHandle(const Message& message) : MessageHandle(message) {}

    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override {
        std::string response_message;

        auto buffer = net::buffer(response_message);
        boost::json::value jsonValue =
            boost::json::parse(parsed_message->getContent());
        auto jsonObject = jsonValue.as_object();

        if (jsonObject.contains("account") && jsonObject.contains("password")) {
            UserDAO::Register(
                std::string(jsonObject.at("account").as_string()),
                std::string(jsonObject.at("password").as_string()));
            response_message = "Registration successful!";
        } else {
            response_message = "Missing account or password field";
        }

        session->getWebSocketStream().async_write(
            buffer,
            [self = shared_from_this()](beast::error_code ec,
                                        std::size_t bytes_transferred) {
                if (ec) {
                    LOG(Level::ERROR, "Write failed: ", ec.message());
                    return;
                }
                LOG(Level::INFO, "Sent message: ", bytes_transferred, " bytes");
            });
    }
};

#endif  // REGISTER_MESSAGE_HANDLE_HPP
