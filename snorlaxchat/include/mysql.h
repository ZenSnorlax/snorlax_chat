#ifndef MYSQL_H
#define MYSQL_H

#include <mysql-cppconn-8/mysqlx/xdevapi.h>
#include <string>

class Mysql {
public:
    Mysql(const std::string &host, const std::string &user, int port,
          const std::string &password, const std::string &database);
    Mysql(Mysql &&other) noexcept;
    ~Mysql();

private:
    mysqlx::Session session_;
};

#endif // MYSQL_H
