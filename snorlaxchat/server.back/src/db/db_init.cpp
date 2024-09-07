#include "db/db_init.h"

namespace database {

Initializer::Initializer(const std::string &host, int port,
                         const std::string &user, const std::string &password,
                         const std::string &database)
    : session_(host, port, user, password) {
    try {
        session_.sql("USE " + database).execute();
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error selecting database: " +
                                 std::string(e.what()));
    }

    createTables();
}

mysqlx::Session &Initializer::getSession() { return session_; }

void Initializer::createTables() {
    try {
        session_
            .sql("CREATE TABLE IF NOT EXISTS users ("
                 "  id INT NOT NULL AUTO_INCREMENT,"
                 "  username VARCHAR(15) NOT NULL UNIQUE,"
                 "  password VARCHAR(15) NOT NULL ,"
                 "  PRIMARY KEY (id)"
                 ")")
            .execute();

        session_
            .sql("CREATE TABLE IF NOT EXISTS messages ("
                 "  id INT NOT NULL AUTO_INCREMENT,"
                 "  sender VARCHAR(14) NOT NULL,"
                 "  receiver VARCHAR(255),"
                 "  content VARCHAR(255) NOT NULL,"
                 "  is_global BOOLEAN NOT NULL DEFAULT 0,"
                 "  PRIMARY KEY (id)"
                 ")")
            .execute();
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error creating tables: " +
                                 std::string(e.what()));
    }
}

} // namespace database
