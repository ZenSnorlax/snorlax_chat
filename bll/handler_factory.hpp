#ifndef MESSAGE_HANDLE_FACTORY_HPP
#define MESSAGE_HANDLE_FACTORY_HPP

#include <memory>

#include "login_handler.hpp"
#include "message_handler.hpp"
#include "register_handler.hpp"

class HandlerFactory {
   public:
    static std::shared_ptr<MessageHandler> createHandle(const Message& message) {
        switch (message.getType()) {
            case MessageType::REGISTER:
                return std::make_shared<RegisterHandler>(message);
            case MessageType::LOGIN:
                return std::make_shared<LoginHandler>(message);
            default:
                return nullptr;
        }
    }
};

#endif  // MESSAGE_HANDLE_FACTORY_HPP
