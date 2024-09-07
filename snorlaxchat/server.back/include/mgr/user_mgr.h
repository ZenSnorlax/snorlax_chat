#ifndef USERS_MANAGER_H
#define USERS_MANAGER_H

#include "db/db_init.h"
#include <mutex>
#include <string>
namespace manager {

class Users {
  public:
    Users(mysqlx::Session &session);

    Users(const Users &) = delete;            // 删除拷贝构造函数
    Users &operator=(const Users &) = delete; // 删除拷贝赋值运算符

    // 默认移动构造函数和移动赋值运算符
    Users(Users &&) noexcept = default;

    void addUser(const std::string &username, const std::string &password);
    bool queryUser(const std::string &username);
    void deleteUser(const std::string &username);
    void changePassword(const std::string &username,
                        const std::string &password);

  private:
    mysqlx::Session &session_;

    std::unique_ptr<std::mutex> mutex_; // 使用智能指针管理互斥量
};

} // namespace manager

#endif // USERS_MANAGER_H
