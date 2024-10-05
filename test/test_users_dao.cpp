#include <gtest/gtest.h>

#include "conn_pool.hpp"
#include "dao.hpp"

class UsersDaoTest : public ::testing::Test {
   protected:
    UsersDao* usersDao;

    UsersDaoTest() {
        auto& pool = ConnectionPool::getInstance();
        pool.Intialize(10, "localhost", 33060, "abs", "1510017673");

        usersDao = new UsersDao;
    }

    ~UsersDaoTest() { delete usersDao; }

    void SetUp() override {
        // 在每个测试之前清理数据库
        usersDao->deleteuser("test", "test");  // 确保用户不存在
    }

    void TearDown() override {
        // 可选：每个测试之后的清理
        usersDao->deleteuser("test", "test");
    }
};

TEST_F(UsersDaoTest, TestEmailExists) {
    usersDao->insert("test", "test", "test@example.com");
    ASSERT_TRUE(usersDao->emailExists("test@example.com"));
}

TEST_F(UsersDaoTest, TestUsernameExists) {
    usersDao->insert("test", "test", "test@example.com");
    ASSERT_TRUE(usersDao->usernameExists("test"));
}

TEST_F(UsersDaoTest, TestMatch) {
    usersDao->insert("test", "test", "test@example.com");
    ASSERT_TRUE(usersDao->match("test", "test"));
    ASSERT_FALSE(usersDao->match("test", "wrongpassword"));
}

TEST_F(UsersDaoTest, TestDeleteUser) {
    usersDao->insert("test", "test", "test@example.com");
    usersDao->deleteuser("test", "test");
    ASSERT_FALSE(usersDao->usernameExists("test"));
}

TEST_F(UsersDaoTest, TestUpdataStatus) {
    usersDao->insert("test", "test", "test@example.com");
    usersDao->updataStatus("test", UserStatus::Inactive);
    ASSERT_EQ(usersDao->getStatus("test"), UserStatus::Inactive);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
