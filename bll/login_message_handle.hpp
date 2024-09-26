#ifndef LOGIN_MESSAGE_HANDLE_HPP
#define LOGIN_MESSAGE_HANDLE_HPP

#include "message.hpp"
#include "message_handle.hpp"

class LoginMessageHandle : public MessageHandle {
   public:
    LoginMessageHandle(const Message& message) : MessageHandle(message) {}
    void handle(std::shared_ptr<WebSocketSession> session,
                std::unique_ptr<MessageParse> parsed_message) override {}
};

#endif  // LOGIN_MESSAGE_HANDLE_HPP
