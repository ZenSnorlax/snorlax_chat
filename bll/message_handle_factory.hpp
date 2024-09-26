#ifndef MESSAGE_HANDLE_FACTORY_HPP
#define MESSAGE_HANDLE_FACTORY_HPP

#include <memory>

#include "login_message_handle.hpp"
#include "message_handle.hpp"
#include "register_message_handle.hpp"

class MessageHandleFactory {
   public:
    static std::shared_ptr<MessageHandle> createHandle(const Message& message) {
        switch (message.getType()) {
            case MessageType::REGISTER:
                return std::make_shared<RegisterMessageHandle>(message);
            case MessageType::LOGIN:
                return std::make_shared<LoginMessageHandle>(message);
            default:
                return nullptr;
        }
    }
};

#endif  // MESSAGE_HANDLE_FACTORY_HPP
