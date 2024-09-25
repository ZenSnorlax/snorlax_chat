#include "message.hpp"

#include "../server/websocket.hpp"
#include "user.hpp"

Message::Message(MessageType type, std::string sender, std::string receiver,
                 std::string content)
    : type_(type),
      sender_(std::move(sender)),
      receiver_(std::move(receiver)),
      content_(std::move(content)) {}

std::string Message::getContent() const { return content_; }
MessageType Message::getType() const { return type_; }
std::string Message::getSender() const { return sender_; }
std::string Message::getReceiver() const { return receiver_; }

MessageHandle::MessageHandle(const Message& message) : message_(message) {}

RegisterMessageHandle::RegisterMessageHandle(const Message& message)
    : MessageHandle(message) {}

void RegisterMessageHandle::handle(
    std::shared_ptr<WebSocketSession> session,
    std::unique_ptr<MessageParse> parsed_message) {
    std::string response_message;

    auto buffer = net::buffer(response_message);
    boost::json::value jsonValue =
        boost::json::parse(parsed_message->getContent());
    auto jsonObject = jsonValue.as_object();

    if (jsonObject.contains("account") && jsonObject.contains("password")) {
        UserDAO::Register(std::string(jsonObject.at("account").as_string()),
                          std::string(jsonObject.at("password").as_string()));
        response_message = "Registration successful!";
    } else {
        response_message = "Missing account or password field ";
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

LoginMessageHandle::LoginMessageHandle(const Message& message)
    : MessageHandle(message) {}

void LoginMessageHandle::handle(std::shared_ptr<WebSocketSession> session,
                                std::unique_ptr<MessageParse> parsed_message) {}

void LogoutMessageHandle::handle(std::shared_ptr<WebSocketSession> session,
                                 std::unique_ptr<MessageParse> parsed_message) {

}

void TextMessageHandle::handle(std::shared_ptr<WebSocketSession> session,
                               std::unique_ptr<MessageParse> parsed_message) {}

void ImageMessageHandle::handle(std::shared_ptr<WebSocketSession> session,
                                std::unique_ptr<MessageParse> parsed_message) {}

void FileMessageHandle::handle(std::shared_ptr<WebSocketSession> session,
                               std::unique_ptr<MessageParse> parsed_message) {}

void HeartbeatMessageHandle::handle(
    std::shared_ptr<WebSocketSession> session,
    std::unique_ptr<MessageParse> parsed_message) {}

void SystemMessageHandle::handle(std::shared_ptr<WebSocketSession> session,
                                 std::unique_ptr<MessageParse> parsed_message) {

}

std::shared_ptr<MessageHandle> MessageHandleFactory::createHandle(
    const Message& message) {
    switch (message.getType()) {
        case MessageType::REGISTER:
            return std::make_shared<RegisterMessageHandle>(message);
        case MessageType::LOGIN:
            return std::make_shared<LoginMessageHandle>(message);
        case MessageType::LOGOUT:
            return std::make_shared<LogoutMessageHandle>(message);
        case MessageType::TEXT_MESSAGE:
            return std::make_shared<TextMessageHandle>(message);
        case MessageType::IMAGE_MESSAGE:
            return std::make_shared<ImageMessageHandle>(message);
        case MessageType::FILE_TRANSFER:
            return std::make_shared<FileMessageHandle>(message);
        case MessageType::HEARTBEAT:
            return std::make_shared<HeartbeatMessageHandle>(message);
        case MessageType::SYSTEM_MESSAGE:
            return std::make_shared<SystemMessageHandle>(message);
        default:
            return nullptr;
    }
}
