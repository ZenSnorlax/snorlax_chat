#include <gtest/gtest.h>

#include "conn_pool.hpp"
#include "dao.hpp"

class UsersDaoTest : public ::testing::Test {
   protected:
    UsersDao* usersDao;

    UsersDaoTest() {
        auto& pool = ConnectionPool::getInstance();
        pool.Intialize(10, "localhost", 33060, "abs", "1510017673");
        usersDao = new UsersDao("snorlax_chat", "users");
    }

    ~UsersDaoTest() { delete usersDao; }

    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(UsersDaoTest, TestEmailExists) {
    if (!usersDao->emailExists("test@example.com"))
        usersDao->insert("test", "test", "test@example.com");
    ASSERT_TRUE(usersDao->emailExists("test@example.com"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}