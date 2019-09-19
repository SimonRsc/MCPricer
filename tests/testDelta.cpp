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
    pnl_rng_sseed(mc->rng_, 0);
    auto deltas = pnl_vect_create(2);
    auto st_dev = pnl_vect_create(2);
    auto past = pnl_mat_create_from_scalar(1, 2, 100);
    mc->delta(past, 0., deltas, st_dev);
    EXPECT_NEAR(GET(deltas, 0), 0.281640, 2 * 1.96 * GET(st_dev, 0));
    EXPECT_NEAR(GET(deltas, 1), 0.281951, 2 * 1.96 * GET(st_dev, 1));

    EXPECT_NEAR(GET(st_dev, 0), 0.001058, 0.00005);   // Moins de 5% d'écart
    EXPECT_NEAR(GET(st_dev, 1), 0.001060, 0.00005);   // Moins de 5% d'écart
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
    auto st_dev = pnl_vect_create(40);
    auto past = pnl_mat_create_from_scalar(1, 40, 100);
    mc->delta(past, 0., deltas, st_dev);
    EXPECT_NEAR(GET(deltas, 0), 0.024842, 2 * 1.96 * GET(st_dev, 0));
    EXPECT_NEAR(GET(deltas, 1), 0.024847, 2 * 1.96 * GET(st_dev, 1));
    EXPECT_NEAR(GET(deltas, 2), 0.024842, 2 * 1.96 * GET(st_dev, 2));

    EXPECT_NEAR(GET(st_dev, 0), 0.000040, 0.000002);   // Moins de 5% d'écart
    EXPECT_NEAR(GET(st_dev, 1), 0.000040, 0.000002);   // Moins de 5% d'écart
    EXPECT_NEAR(GET(st_dev, 2), 0.000040, 0.000002);   // Moins de 5% d'écart
}

TEST_F(TestDelta, Basket_1) {
    char arg[] = "basket_1.dat";
    auto rd = new ReadData(arg);
    auto mc = new MonteCarlo();
    mc->mod_ = rd->getModel();
    mc->opt_ = rd->getOption();
    mc->nbSamples_ = 50000;
    mc->rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(mc->rng_, time(0));
    auto deltas = pnl_vect_create(40);
    auto st_dev = pnl_vect_create(40);
    auto past = pnl_mat_create_from_scalar(1, 40, 100);
    mc->delta(past, 0., deltas, st_dev);
    EXPECT_NEAR(GET(deltas, 0), 0.024882, 2 * 1.96 * GET(st_dev, 0));
    EXPECT_NEAR(GET(deltas, 1), 0.024853, 2 * 1.96 * GET(st_dev, 1));
    EXPECT_NEAR(GET(deltas, 2), 0.024868, 2 * 1.96 * GET(st_dev, 2));

    EXPECT_NEAR(GET(st_dev, 0), 0.000041, 0.000002);   // Moins de 5% d'écart
    EXPECT_NEAR(GET(st_dev, 1), 0.000041, 0.000002);   // Moins de 5% d'écart
    EXPECT_NEAR(GET(st_dev, 2), 0.000040, 0.000002);   // Moins de 5% d'écart
}

TEST_F(TestDelta, Performance) {
    char arg[] = "perf.dat";
    auto rd = new ReadData(arg);
    auto mc = new MonteCarlo();
    mc->mod_ = rd->getModel();
    mc->opt_ = rd->getOption();
    mc->nbSamples_ = 50000;
    mc->rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(mc->rng_, time(0));
    auto deltas = pnl_vect_create(5);
    auto st_dev = pnl_vect_create(5);
    auto past = pnl_mat_create_from_scalar(1, 5, 100);
    mc->delta(past, 0., deltas, st_dev);

    EXPECT_NEAR(GET(deltas, 0), 0.000001, 2 * 1.96 * GET(st_dev, 0));
    EXPECT_NEAR(GET(deltas, 1), -0.000001, 2 * 1.96 * GET(st_dev, 1));
    EXPECT_NEAR(GET(deltas, 2), -0.000001, 2 * 1.96 * GET(st_dev, 2));
    EXPECT_NEAR(GET(deltas, 3), -0.000002, 2 * 1.96 * GET(st_dev, 3));
    EXPECT_NEAR(GET(deltas, 4), 0.000002, 2 * 1.96 * GET(st_dev, 4));

    EXPECT_NEAR(GET(st_dev, 0), 0.000001, 0.0000002);   // Moins de 20% d'écart
    EXPECT_NEAR(GET(st_dev, 1), 0.000001, 0.0000002);   // Moins de 20% d'écart
    EXPECT_NEAR(GET(st_dev, 2), 0.000001, 0.0000002);   // Moins de 20% d'écart
    EXPECT_NEAR(GET(st_dev, 3), 0.000001, 0.0000002);   // Moins de 20% d'écart
    EXPECT_NEAR(GET(st_dev, 4), 0.000001, 0.0000002);   // Moins de 20% d'écart
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
