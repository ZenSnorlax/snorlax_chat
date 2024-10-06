#include "dal.hpp"

class RegisterHandler {
   public:
    RegisterHandler() {}
    bool registerUser(const std::string& username, const std::string& password,
                      const std::string& email);

   private:
    std::string hashPassword(const std::string& password);
};
