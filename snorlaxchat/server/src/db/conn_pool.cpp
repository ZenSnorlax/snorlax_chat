// db/connection_pool.cpp
#include "db/conn_pool.h"
#include <iostream>
#include <memory>

namespace db {

MysqlConnectionPool::MysqlConnectionPool(const Config &config, size_t pool_size)
    : config_(config) {
    for (size_t i = 0; i < pool_size; ++i) {
        auto session =
            std::make_unique<mysqlx::Session>(config_.host(),
                                              std::stoi(config_.port()),
                                              config_.user().value_or(""),
                                              config_.password().value_or(""),
                                              config_.db_name().value_or(""));
        connections_.push(std::move(session));
    }
}

MysqlConnectionPool *MysqlConnectionPool::get_instance(const Config &config,
                                                       size_t pool_size) {
    static MysqlConnectionPool pool(config, pool_size);
    return &pool;
}

std::shared_ptr<mysqlx::Session> MysqlConnectionPool::get_connection() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return !connections_.empty(); });

    auto session = std::move(connections_.front());
    connections_.pop();
    std::cout << "get connection" << std::endl;
    return session;
}

void MysqlConnectionPool::release_connection(
    std::shared_ptr<mysqlx::Session> session) {
    std::unique_lock<std::mutex> lock(mutex_);
    connections_.push(std::move(session));
    std::cout << "释放连接" << std::endl;
    cv_.notify_one();
}

} // namespace db
