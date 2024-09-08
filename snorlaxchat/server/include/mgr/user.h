#pragma once

#include <string>
#include <vector>
#include <optional>
#include "db/conn_pool.h"

namespace mgr {

class UserManager {
public:
    // 构造函数，接受一个数据库连接池指针
    explicit UserManager(db::MysqlConnectionPool *db_pool);

    // 执行计数查询
    bool executeCountQuery(const std::string &query,
                           const std::vector<std::string> &params,
                           int &result_count);

    // 检查用户是否存在
    bool isUserExists(const std::string &user_name);

    // 验证用户凭据
    bool verifyUserCredentials(const std::string &user_name,
                               const std::string &password);

    // 添加用户
    bool addUser(const std::string &user_name,
                 const std::string &password);

    // 删除用户
    bool deleteUser(const std::string &user_name,
                    const std::string &password);

    // 更新用户密码
    bool updatePassword(const std::string &user_name,
                        const std::string &oldpassword,
                        const std::string &newpassword);

    // 获取用户信息
    std::optional<std::pair<std::string, std::string>> getUserInfo(const std::string &user_name);

private:
    db::MysqlConnectionPool *db_pool_;  // 数据库连接池指针
};

} // namespace mgr
