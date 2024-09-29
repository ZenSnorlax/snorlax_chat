#ifndef REGISTER_MESSAGE_HANDLE_HPP
#define REGISTER_MESSAGE_HANDLE_HPP

#include <boost/beast/core.hpp>
#include <boost/json.hpp>
#include <regex>

#include "../dal/user_dao.hpp"
#include "../server/websocket_server.hpp"
#include "message_handler.hpp"

class RegisterHandler : public MessageHandler,
                        public std::enable_shared_from_this<RegisterHandler> {
   public:
    RegisterHandler(const Message& message) : MessageHandler(message) {}

    void handle(std::shared_ptr<WebSocketSession> session) override {
        try {
            auto [account, password] = parseJson();
            sendResponse(session, validateAndRegister(account, password));
        } catch (const std::invalid_argument& e) {
            sendResponse(session, generateErrorResponse(e.what()));
        }
    }

   private:
    std::pair<std::string, std::string> parseJson() {
        auto jsonObject = boost::json::parse(message_.getContent()).as_object();

        if (!jsonObject.contains("account") ||
            !jsonObject.contains("password")) {
            throw std::invalid_argument(
                "Missing account or password in content");
        }

        return {jsonObject["account"].as_string().c_str(),
                jsonObject["password"].as_string().c_str()};
    }

    std::string validateAndRegister(const std::string& account,
                                    const std::string& password) {
        const std::regex account_regex("^[A-Za-z]{10}$");
        const std::regex password_regex("^[0-9]{10}$");

        if (!std::regex_match(account, account_regex) ||
            !std::regex_match(password, password_regex)) {
            return generateErrorResponse("Invalid account or password format");
        }

        return generateResponse(UserDAO::Register(account, password));
    }

    std::string generateErrorResponse(const std::string& message) {
        return R"({"status":"error", "message":")" + message + R"("})";
    }

    std::string generateResponse(const std::string& result) {
        return result == "Register successful"
                   ? R"({"status":"success", "message":"User registered successfully"})"
                   : R"({"status":"error", "message":")" + result + R"("})";
    }

    void sendResponse(std::shared_ptr<WebSocketSession> session,
                      const std::string& response_message) {
        auto buffer = net::buffer(response_message);
        session->getWebSocketStream().async_write(
            buffer,
            [self = shared_from_this()](beast::error_code ec, std::size_t) {
                if (ec) {
                    LOG(Level::ERROR, "Write failed: ", ec.message());
                } else {
                    LOG(Level::INFO, "Message sent successfully");
                }
            });
    }
};

#endif  // REGISTER_MESSAGE_HANDLE_HPP
