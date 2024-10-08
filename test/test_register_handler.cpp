#include <gtest/gtest.h>

#include "bll.hpp"
#include "conn_pool.hpp"

TEST(RegisterHandler, sendEmailCode) {
    auto& pool = ConnectionPool::getInstance();
    pool.Intialize(10, "localhost", 33060, "abs", "1510017673");
    RegisterHandler handler;
    EXPECT_TRUE(handler.sendEmailCode("q1510017673@outlook.com"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}