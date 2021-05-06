#include <gtest/gtest.h>

TEST(test, fails)
{
    ASSERT_TRUE(false);
}

TEST(test, passes)
{
    ASSERT_TRUE(true);
}