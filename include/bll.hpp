#include <string>
#include <vector>

#include "dal.hpp"
enum class ErrorCode {
    Success = 0,
    EmailExists = 1,
    UsernameExists = 2,
    PasswordError = 3,
    CodeError = 4,
    UnknownError = 5,
    AuthError = 6,
    SmtpError = 7,
    UsernameFormatError = 8,
    PasswordFormatError = 9,
    UsernameNotExists = 10,
    RoomExists = 11,
    RoomnameFormatError = 12,
    RoomNotExists = 13,
};

class RegisterHandler {
   public:
    RegisterHandler() {}
    ErrorCode sendEmailCode(const std::string& email);

    ErrorCode registerUser(const std::string& username,
                           const std::string& password,
                           const std::string& email, const std::string& code);

    std::string getCode() { return code; }

   private:
    std::string code;
    int generateVerificationCode();
};

class LoginHandler {
   public:
    LoginHandler() {}
    ErrorCode login(const std::string& username, const std::string& password);
    std::vector<std ::string> getMissingMessage();

   private:
    std::string username_;
};

class ChatroomHandler {
   public:
    ChatroomHandler() {}
    ErrorCode joinChatroom(const std::string& username,
                           const std::string& password,
                           const std::string& room_name);

    ErrorCode createChatroom(const std::string& username,
                             const std::string& password,
                             const std::string& room_name);
};

class MessageHanlder {
   public:
    MessageHanlder() {}
    ErrorCode addMessage(const std::string& username,
                         const std::string& room_name,
                         const std::string& content);
};
