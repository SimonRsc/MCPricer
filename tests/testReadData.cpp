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
    /*string str = "data/call.dat";
    char arg[str.length()];
    strcpy(arg, str.c_str());*/
    char arg[] = "call.dat";
    auto rd = new ReadData(arg);
    Option* option = rd->getOption();
    auto path = new PnlMat();
    MLET(path, 0, 0) = 10;
    MLET(path, 1, 0) = 11;
    EXPECT_EQ(option->payoff(path), 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}