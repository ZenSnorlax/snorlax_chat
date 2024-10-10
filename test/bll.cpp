#include <bcrypt.h>
#include <gtest/gtest.h>

#include "bll.hpp"
#include "conn_pool.hpp"

TEST(RegisterHandler, sendEmailCode) {
    auto& pool = ConnectionPool::getInstance();
    pool.Intialize(10, "localhost", 33060, "abs", "1510017673");
    RegisterHandler handler;

    EXPECT_EQ(handler.sendEmailCode("q1510017673@outlook.com"),
              ErrorCode::Success);
}

TEST(RegisterHandler, registerUser) {
    auto& pool = ConnectionPool::getInstance();
    pool.Intialize(10, "localhost", 33060, "abs", "1510017673");
    RegisterHandler handler;
    handler.sendEmailCode("q1510017673@outlook.com");

    EXPECT_NE(handler.registerUser("test", "test", "test@qq.com", "123456"),
              ErrorCode::Success);

    EXPECT_EQ(handler.registerUser(
                  "snorlax", "1510017673", "test@qq.com", handler.getCode()),
              ErrorCode::Success);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
