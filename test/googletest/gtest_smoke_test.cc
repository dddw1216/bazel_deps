#include <gtest/gtest.h>

TEST(GoogleTest, BasicAssertion) {
    EXPECT_EQ(1 + 1, 2);
    EXPECT_NE(2, 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

