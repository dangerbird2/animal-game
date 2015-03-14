#include <stdio.h>
#include <gtest/gtest.h>

/**
 * @brief: main file for test suite
 * @details initializes and runs the gtest runner
 */
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}