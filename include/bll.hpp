#include "dal.hpp"

class RegisterHandler {
   public:
    RegisterHandler() {}
    bool sendEmailCode(const std::string& email);

   private:
    std::string code;
    int generateVerificationCode();
};
