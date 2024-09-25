#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <boost/asio.hpp>
#include <memory>
#include <string>

#include "../server/message_paraser.hpp"

class WebSocketSession;

class Message {
   public:
    Message(MessageType type, std::string sender, std::string receiver,
            std::string content);

    std::string getContent() const;
    MessageType getType() const;
    std::string getSender() const;
    std::string getReceiver() const;

   private:
    std::string sender_;
    std::string content_;
    MessageType type_;
    std::string receiver_;
};

class MessageHandle {
   public:
    virtual void handle(std::shared_ptr<WebSocketSession> session,
                        std::unique_ptr<MessageParse> parsed_message) = 0;
    virtual ~MessageHandle() {}

   protected:
    MessageHandle(const Message& message);
    Message message_;
};

class RegisterMessageHandle
    : public MessageHandle,
      public std::enable_shared_from_this<RegisterMessageHandle> {
   public:
    RegisterMessageHandle(const Message& message);
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override;
};

class LoginMessageHandle : public MessageHandle {
   public:
    LoginMessageHandle(const Message& message);
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override;
};

class LogoutMessageHandle : public MessageHandle {
   public:
    LogoutMessageHandle(const Message& message) : MessageHandle(message) {}
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override;
};

class TextMessageHandle : public MessageHandle {
   public:
    TextMessageHandle(const Message& message) : MessageHandle(message) {}
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override;
};

class ImageMessageHandle : public MessageHandle {
   public:
    ImageMessageHandle(const Message& message) : MessageHandle(message) {}
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override;
};

class FileMessageHandle : public MessageHandle {
   public:
    FileMessageHandle(const Message& message) : MessageHandle(message) {}
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override;
};

class HeartbeatMessageHandle : public MessageHandle {
   public:
    HeartbeatMessageHandle(const Message& message) : MessageHandle(message) {}
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override;
};

class SystemMessageHandle : public MessageHandle {
   public:
    SystemMessageHandle(const Message& message) : MessageHandle(message) {}
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override;
};

class MessageHandleFactory {
   public:
    static std::shared_ptr<MessageHandle> createHandle(const Message& message);
};

#endif  // MESSAGE_HPP
