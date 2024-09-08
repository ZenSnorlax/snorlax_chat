enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests db/test_config.cpp)
target_link_libraries(tests
    core
    GTest::gtest
    GTest::gtest_main
    redis++
    hiredis
    mysqlcppconn8
    boost_system
    boost_thread
)

add_test(NAME test_config COMMAND tests)
