#include "gtest/gtest.h"
#include "../src/ReadData.hpp"
#include "../src/CallOption.h"
#include "../src/Option.hpp"

class ReadDataTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(ReadDataTest, ReadCall) {
    char arg[] = "call.dat";
    auto rd = new ReadData(arg);
    Option* option = rd->getOption();
    auto path = pnl_mat_create(2, 1);
    MLET(path, 0, 0) = 100;
    MLET(path, 1, 0) = 101;
    EXPECT_EQ(option->payoff(path), 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}