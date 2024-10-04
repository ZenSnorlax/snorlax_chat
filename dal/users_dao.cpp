#include "conn_pool.hpp"
#include "dao.hpp"
#include "snorlax_log.hpp"

ErrorCode UsersDao::insert(const std::string& username,
                           const std::string& passwd,
                           const std::string& email) {  // 默认状态为 'active'
    ConnectionGuard conn_guard(ConnectionPool::getInstance().getConnection());
    mysqlx::Schema schema = conn_guard->getSchema(db_name_);
    mysqlx::Table table = schema.getTable(table_name_);

    try {
        table.insert("username", "password_hash", "email", "status")
            .values(username, passwd, email, "inactive")
            .execute();
        return ErrorCode::kSuccess;
    } catch (const mysqlx::Error& err) {
        LOG(Level::INFO, "Error inserting user: ", err.what());
        return ErrorCode::kDatabaseError;
    } catch (const std::exception& ex) {
        LOG(Level::INFO, "Error inserting user: ", ex.what());
        return ErrorCode::kUnknownError;
    }
}
