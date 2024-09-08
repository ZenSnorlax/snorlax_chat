#pragma once

#include <string>
#include <optional>

namespace db {

class Config {
public:
    // 构造函数
    Config(const std::string &host, const std::string &port,
           std::optional<std::string> user = std::nullopt,
           std::optional<std::string> password = std::nullopt,
           std::optional<std::string> db_name = std::nullopt);

    // 获取配置项的方法
    const std::string &host() const;
    const std::string &port() const;
    const std::optional<std::string> &user() const;
    const std::optional<std::string> &password() const;
    const std::optional<std::string> &db_name() const;

private:
    std::string host_;
    std::string port_;
    std::optional<std::string> user_;
    std::optional<std::string> password_;
    std::optional<std::string> db_name_;
};

} // namespace db
