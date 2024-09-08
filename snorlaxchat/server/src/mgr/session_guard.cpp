#include "mgr/session_guard.h"
#include <iostream>

namespace mgr {

SessionGuard::SessionGuard(db::MysqlConnectionPool *pool) : pool_(pool) {
    session_ = pool_->get_connection();
    std::cout << "[INFO] Session acquired." << std::endl;
}

SessionGuard::~SessionGuard() {
    if (session_) {
        pool_->release_connection(session_);
        std::cout << "[INFO] Session released." << std::endl;
    }
}

std::shared_ptr<mysqlx::Session> SessionGuard::session() const {
    return session_;
}

} // namespace mgr
