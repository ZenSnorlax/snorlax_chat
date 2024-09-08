#pragma once
#include "db/conn_pool.h"
#include <mysqlx/xdevapi.h>

namespace mgr {

class SessionGuard {
public:
    explicit SessionGuard(db::MysqlConnectionPool* pool);
    ~SessionGuard();

    std::shared_ptr<mysqlx::Session> session() const;

private:
    db::MysqlConnectionPool* pool_;
    std::shared_ptr<mysqlx::Session> session_;
};

} // namespace mgr

