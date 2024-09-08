#include <gtest/gtest.h>
#include "db/config.h"

TEST(ConfigTest, DefaultValues) {
    db::Config config("localhost", "3306");

    EXPECT_EQ(config.host(), "localhost");
    EXPECT_EQ(config.port(), "3306");
    EXPECT_FALSE(config.user().has_value());
    EXPECT_FALSE(config.password().has_value());
    EXPECT_FALSE(config.db_name().has_value());
}

TEST(ConfigTest, FullConstructor) {
    db::Config config("localhost", "3306", "user", "password", "dbname");

    EXPECT_EQ(config.host(), "localhost");
    EXPECT_EQ(config.port(), "3306");
    EXPECT_EQ(config.user().value(), "user");
    EXPECT_EQ(config.password().value(), "password");
    EXPECT_EQ(config.db_name().value(), "dbname");
}
