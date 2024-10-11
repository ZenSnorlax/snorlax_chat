#include "bll.hpp"

#include <bcrypt.h>
#include <gtest/gtest.h>

#include "conn_pool.hpp"

TEST(RegisterHandler, sendEmailCode) {
    RegisterHandler handler;

    EXPECT_EQ(handler.sendEmailCode("q1510017673@outlook.com"),
              ErrorCode::Success);
}

TEST(RegisterHandler, registerUser) {
    RegisterHandler handler;
    handler.sendEmailCode("q1510017673@outlook.com");

    EXPECT_NE(handler.registerUser("test", "test", "test@qq.com", "123456"),
              ErrorCode::Success);

    EXPECT_EQ(handler.registerUser(
                  "snorlax", "1510017673", "test@qq.com", handler.getCode()),
              ErrorCode::Success);
}

TEST(LoginHandler, Login) {
    LoginHandler handler;
    EXPECT_EQ(handler.login("snorlax", "1510017673"), ErrorCode::Success);
}

TEST(LoginHandler, getMissingMessage) {}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto& pool = ConnectionPool::getInstance();
    pool.Intialize(10, "localhost", 33060, "abs", "1510017673");
    return RUN_ALL_TESTS();
}
