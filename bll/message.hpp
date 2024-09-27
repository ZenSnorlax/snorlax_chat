#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

enum MessageType {
    REGISTER,
    LOGIN,

    LOGOUT,
    TEXT_MESSAGE,
    IMAGE_MESSAGE,
    FILE_TRANSFER,
    HEARTBEAT,
    SYSTEM_MESSAGE,
    CREATE_DUAL_CHAT,
    CREATE_MULT_CHAT,
};

class Message {
   public:
    Message(MessageType type, std::string sender, std::string receiver,
            std::string content)
        : type_(type),
          sender_(std::move(sender)),
          receiver_(std::move(receiver)),
          content_(std::move(content)) {}

    std::string getContent() const { return content_; }

    MessageType getType() const { return type_; }

    std::string getSender() const { return sender_; }

    std::string getReceiver() const { return receiver_; }

   private:
    std::string sender_;
    std::string content_;
    MessageType type_;
    std::string receiver_;
};

#endif  // MESSAGE_HPP
