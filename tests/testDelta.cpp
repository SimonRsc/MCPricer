#include "gtest/gtest.h"
#include <sstream>
#include "../src/MonteCarlo.hpp"
#include "../src/ReadData.hpp"

class TestDelta : public ::testing::Test {

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

TEST_F(TestDelta, Asian) {
    char arg[] = "asian.dat";
    auto rd = new ReadData(arg);
    auto mc = new MonteCarlo();
    mc->mod_ = rd->getModel();
    mc->opt_ = rd->getOption();
    mc->nbSamples_ = 50000;
    mc->rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(mc->rng_,0);
    auto deltas = pnl_vect_create(2);
    auto ic = pnl_vect_create(2);
    auto past = pnl_mat_create_from_scalar(1, 2, 100);
    mc->delta(past, 0., deltas, ic);
    EXPECT_NEAR(GET(deltas, 0), 0.281640, GET(ic, 0));
    EXPECT_NEAR(GET(deltas, 1), 0.281951, GET(ic, 1));
}


TEST_F(TestDelta, Basket) {
    char arg[] = "basket.dat";
    auto rd = new ReadData(arg);
    auto mc = new MonteCarlo();
    mc->mod_ = rd->getModel();
    mc->opt_ = rd->getOption();
    mc->nbSamples_ = 50000;
    mc->rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(mc->rng_, time(0));
    auto deltas = pnl_vect_create(40);
    auto ic = pnl_vect_create(40);
    auto past = pnl_mat_create_from_scalar(1, 40, 100);
    mc->delta(past, 0., deltas, ic);
    EXPECT_NEAR(GET(deltas, 0), 0.024842, GET(ic, 0));
    EXPECT_NEAR(GET(deltas, 1), 0.024847, GET(ic, 1));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}