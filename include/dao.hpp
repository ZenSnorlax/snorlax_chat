#include <string>

enum class UserStatus { Active, Inactive };

class UsersDao {
   public:
    UsersDao(const std::string &db_name, const std::string &table_name)
        : db_name_(std::move(db_name)), table_name_(std::move(table_name)) {}

    bool emailExists(const std::string &email);

    void insert(const std::string &username, const std::string &password,
                const std::string &email);

    bool usernameExists(const std::string &username);

    bool match(const std::string &username, const std::string &password);

    void deleteuser(const std::string &username, const std::string &password);

    void setStatus(const std::string &username, UserStatus status);

    UserStatus getStatus(const std::string &username);

   private:
    const std::string db_name_;
    const std::string table_name_;

    std::string statusToString(UserStatus status);
};
