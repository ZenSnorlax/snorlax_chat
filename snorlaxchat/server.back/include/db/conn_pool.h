#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H

#include "db_init.h"
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
namespace database {

class ConnectionPool {
  public:
    static ConnectionPool &instance(Initializer &initializer,
                                    size_t poolSize = 10);

    std::shared_ptr<mysqlx::Session> getConnection();
    void releaseConnection(std::shared_ptr<mysqlx::Session> conn);

  private:
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<std::shared_ptr<mysqlx::Session>> connectionPool_;

    ConnectionPool(Initializer &initializer, size_t poolSize);
    ~ConnectionPool();
};

} // namespace database

#endif // CONNECTION_POOL_H
