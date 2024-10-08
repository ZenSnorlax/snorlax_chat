#include "dal.hpp"

enum class ErrorCode {
    Success = 0,
    EmailExists = 1,
    UsernameExists = 2,
    PasswordError = 3,
    CodeError = 4,
    UnknownError = 5,
    AuthError = 6,
    SmtpError = 7
};

class RegisterHandler {
   public:
    RegisterHandler() {}
    ErrorCode sendEmailCode(const std::string& email);

    ErrorCode registerUser(const std::string& username,
                           const std::string& password,
                           const std::string& email, const std::string& code);

   private:
    std::string code;
    int generateVerificationCode();
};
