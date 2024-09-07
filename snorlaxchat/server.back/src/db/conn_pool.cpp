#include "db/conn_pool.h"

namespace database {

ConnectionPool &ConnectionPool::instance(Initializer &initializer,
                                         size_t poolSize) {
    static ConnectionPool pool(initializer, poolSize);
    return pool;
}

std::shared_ptr<mysqlx::Session> ConnectionPool::getConnection() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return !connectionPool_.empty(); });
    auto conn = connectionPool_.front();
    connectionPool_.pop();
    return conn;
}

void ConnectionPool::releaseConnection(std::shared_ptr<mysqlx::Session> conn) {
    std::unique_lock<std::mutex> lock(mutex_);
    connectionPool_.push(conn);
    cv_.notify_one();
}

ConnectionPool::ConnectionPool(Initializer &initializer, size_t poolSize) {
    for (size_t i = 0; i < poolSize; ++i) {
        connectionPool_.push(
            std::make_shared<mysqlx::Session>(std::move(initializer.getSession())));
    }
}

ConnectionPool::~ConnectionPool() {
    while (!connectionPool_.empty()) {
        connectionPool_.pop();
    }
}

} // namespace database
