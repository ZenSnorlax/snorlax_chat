//
// Created by qing on 9/8/24.
//

#include "db/config.h"
#include "db/conn_pool.h"
#include <gtest/gtest.h>

TEST(ConnPoolTest, DEFAULT) {
    db::Config config("localhost", "33060", "abs", "1510017673", "my_database");
    db::MysqlConnectionPool *pool =
        db::MysqlConnectionPool::get_instance(config, 10);
    
}