// db/config.cpp
#include "db/config.h"

namespace db {

Config::Config(const std::string &host, const std::string &port,
               std::optional<std::string> user,
               std::optional<std::string> password,
               std::optional<std::string> db_name)
    : host_(host), port_(port), user_(std::move(user)),
      password_(std::move(password)), db_name_(std::move(db_name)) {}

const std::string &Config::host() const { return host_; }
const std::string &Config::port() const { return port_; }
const std::optional<std::string> &Config::user() const { return user_; }
const std::optional<std::string> &Config::password() const { return password_; }
const std::optional<std::string> &Config::db_name() const { return db_name_; }

} // namespace db