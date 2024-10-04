#include <string>

enum class ErrorCode {
    kSuccess = 0,
    kAccountExist = 1,
    kAccountNotExist = 2,
    kPasswdError = 3,
    kEmailExist = 4,
    kEmailNotExist = 5,
    kDatabaseError = 6,
    kUnknownError = 7
};

class UsersDao {
   public:
    UsersDao(std::string db_name, std::string table_name)
        : db_name_(std::move(db_name)), table_name_(std::move(table_name)) {}

    ErrorCode insert(const std::string& username, const std::string& passwd,
                     const std::string& email);

    ErrorCode delete_by_account(const std::string& username,
                                const std::string& passwd);

    ErrorCode check(const std::string& username, const std::string& passwd);

   private:
    std::string db_name_;
    std::string table_name_;
};
