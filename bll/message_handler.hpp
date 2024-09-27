#ifndef MESSAGE_HANDLE_HPP
#define MESSAGE_HANDLE_HPP

#include <memory>

#include "message_parser.hpp"
#include "message.hpp"
class WebSocketSession;

class MessageHandler {
   public:
    virtual void handle(std::shared_ptr<WebSocketSession> session,
                        std::unique_ptr<MessageParser> parsed_message) = 0;
    virtual ~MessageHandler() {}

   protected:
    MessageHandler(const Message& message) : message_(message) {}
    Message message_;
};

#endif  // MESSAGE_HANDLE_HPP
