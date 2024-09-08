#pragma once

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <mysqlx/xdevapi.h>
#include "config.h"

namespace db {

class MysqlConnectionPool {
public:
    // 静态方法获取单例实例
    static MysqlConnectionPool *get_instance(const Config &config, size_t pool_size);

    // 获取一个连接
    std::shared_ptr<mysqlx::Session> get_connection();

    // 释放连接
    void release_connection(std::shared_ptr<mysqlx::Session> session);

private:
    // 私有构造函数
    MysqlConnectionPool(const Config &config, size_t pool_size);

    // 配置对象
    Config config_;

    // 连接队列
    std::queue<std::shared_ptr<mysqlx::Session>> connections_;

    // 互斥锁和条件变量
    std::mutex mutex_;
    std::condition_variable cv_;
};

} // namespace db
