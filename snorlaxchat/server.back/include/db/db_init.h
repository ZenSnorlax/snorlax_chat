#ifndef DATABASE_INITIALIZER_H
#define DATABASE_INITIALIZER_H

#include <mysql-cppconn-8/mysqlx/xdevapi.h>
#include <string>

namespace database {

class Initializer {
  public:
    Initializer(const std::string &host, int port, const std::string &user,
                const std::string &password, const std::string &database);

    mysqlx::Session &getSession();

  private:
    mysqlx::Session session_;
    void createTables();
};

} // namespace database

#endif // DATABASE_INITIALIZER_H
