#ifndef MESSAGE_HANDLE_HPP
#define MESSAGE_HANDLE_HPP

#include <memory>

#include "message_paraser.hpp"
#include "message.hpp"
class WebSocketSession;

class MessageHandle {
   public:
    virtual void handle(std::shared_ptr<WebSocketSession> session,
                        std::unique_ptr<MessageParse> parsed_message) = 0;
    virtual ~MessageHandle() {}

   protected:
    MessageHandle(const Message& message) : message_(message) {}
    Message message_;
};

#endif  // MESSAGE_HANDLE_HPP
