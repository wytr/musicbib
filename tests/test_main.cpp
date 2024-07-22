#include <gtest/gtest.h>

// Main function for GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(TestSuite1, Test1) {
    ASSERT_EQ(1, 1);
}

TEST(TestSuite1, Test2) {
    ASSERT_EQ(2, 2);
}

TEST(TestSuite2, Test1) {
    ASSERT_EQ(3, 3);
}