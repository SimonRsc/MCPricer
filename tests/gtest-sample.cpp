#include "gtest/gtest.h"
#include <sstream>

class FooTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(FooTest, WhatDoesTheTest) {
    EXPECT_EQ(0, 0);
}

TEST_F(FooTest, WhatDoesThisOtherTest) {
    EXPECT_NE(0, 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}