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

TEST_F(TestDelta, Asian_0) {
    char arg[] = "asian.dat";
    auto rd = new ReadData(arg);
    auto mod_ = rd->getModel();
    auto opt_ = rd->getOption();
    auto nbSamples_ = rd->getNombreSample();
    auto rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    auto mc = new MonteCarlo(mod_, opt_, rng_, nbSamples_);
    auto deltas = pnl_vect_create(2);
    auto st_dev = pnl_vect_create(2);
    auto past = pnl_mat_create_from_scalar(1, 2, 100);
    mc->delta(past, 0., deltas, st_dev);
    EXPECT_NEAR(GET(deltas, 0), 0.281640, 2 * 1.96 * GET(st_dev, 0));
    EXPECT_NEAR(GET(deltas, 1), 0.281951, 2 * 1.96 * GET(st_dev, 1));

    EXPECT_NEAR(GET(st_dev, 0), 0.001058, 0.00005);   // Moins de 5% d'écart
    EXPECT_NEAR(GET(st_dev, 1), 0.001060, 0.00005);   // Moins de 5% d'écart
}


TEST_F(TestDelta, Basket_0) {
    char arg[] = "basket.dat";
    auto rd = new ReadData(arg);
    auto mod_ = rd->getModel();
    auto opt_ = rd->getOption();
    auto nbSamples_ = rd->getNombreSample();
    auto rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    auto mc = new MonteCarlo(mod_, opt_, rng_, nbSamples_);
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

TEST_F(TestDelta, Basket_1_0) {
    char arg[] = "basket_1.dat";
    auto rd = new ReadData(arg);
    auto mod_ = rd->getModel();
    auto opt_ = rd->getOption();
    auto nbSamples_ = rd->getNombreSample();
    auto rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    auto mc = new MonteCarlo(mod_, opt_, rng_, nbSamples_);
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

TEST_F(TestDelta, Performance_0) {
    char arg[] = "perf.dat";
    auto rd = new ReadData(arg);
    auto mod_ = rd->getModel();
    auto opt_ = rd->getOption();
    auto nbSamples_ = rd->getNombreSample();
    auto rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    auto mc = new MonteCarlo(mod_, opt_, rng_, nbSamples_);
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


TEST_F(TestDelta, Asian_t) {
    char arg[] = "asian.dat";
    auto rd = new ReadData(arg);
    auto mod_ = rd->getModel();
    auto opt_ = rd->getOption();
    auto nbSamples_ = rd->getNombreSample();
    auto rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    auto mc = new MonteCarlo(mod_, opt_, rng_, nbSamples_);
    auto deltas_ref = pnl_vect_create(opt_->size_);
    auto st_dev_ref = pnl_vect_create(opt_->size_);
    auto deltas = pnl_vect_create(opt_->size_);
    auto st_dev = pnl_vect_create(opt_->size_);
    auto market_data = pnl_mat_create_from_file("simul_asian.dat");
    auto past = pnl_mat_wrap_mat_rows(market_data, 0, 1);
    auto spot = pnl_mat_wrap_mat_rows(market_data, 1, 1);
    pnl_rng_sseed(mc->rng_, 0);
    mc->delta(&past, opt_->T_ / market_data->m, deltas, st_dev);
    pnl_mat_get_row(mc->mod_->spot_, &spot, 0);
    pnl_rng_sseed(mc->rng_, 0);
    mc->delta(&spot, 0., deltas_ref, st_dev_ref);

    EXPECT_NEAR(GET(deltas, 0), GET(deltas_ref, 0), 2 * 1.96 * GET(st_dev_ref, 0));
    EXPECT_NEAR(GET(deltas, 1), GET(deltas_ref, 1), 2 * 1.96 * GET(st_dev_ref, 1));

    EXPECT_NEAR(GET(st_dev, 0), GET(st_dev_ref, 0), 0.00001);
    EXPECT_NEAR(GET(st_dev, 1), GET(st_dev_ref, 1), 0.00001);
}

TEST_F(TestDelta, Basket_1_t) {
    char arg[] = "basket_1.dat";
    auto rd = new ReadData(arg);
    auto mod_ = rd->getModel();
    auto opt_ = rd->getOption();
    auto nbSamples_ = rd->getNombreSample();
    auto rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    auto mc = new MonteCarlo(mod_, opt_, rng_, nbSamples_);
    auto deltas_ref = pnl_vect_create(opt_->size_);
    auto st_dev_ref = pnl_vect_create(opt_->size_);
    auto deltas = pnl_vect_create(opt_->size_);
    auto st_dev = pnl_vect_create(opt_->size_);
    auto market_data = pnl_mat_create_from_file("simul_basket_1.dat");
    auto past = pnl_mat_wrap_mat_rows(market_data, 0, 1);
    auto spot = pnl_mat_wrap_mat_rows(market_data, 1, 1);
    pnl_rng_sseed(mc->rng_, 0);
    mc->delta(&past, opt_->T_ / market_data->m, deltas, st_dev);
    pnl_mat_get_row(mc->mod_->spot_, &spot, 0);
    pnl_rng_sseed(mc->rng_, 0);
    mc->delta(&spot, 0., deltas_ref, st_dev_ref);

    EXPECT_NEAR(GET(deltas, 0), GET(deltas_ref, 0), 2 * 1.96 * GET(st_dev_ref, 0));
    EXPECT_NEAR(GET(deltas, 1), GET(deltas_ref, 1), 2 * 1.96 * GET(st_dev_ref, 1));

    EXPECT_NEAR(GET(st_dev, 0), GET(st_dev_ref, 0), 0.00001);
    EXPECT_NEAR(GET(st_dev, 1), GET(st_dev_ref, 1), 0.00001);
}

TEST_F(TestDelta, Basket_2_t) {
    char arg[] = "basket_2.dat";
    auto rd = new ReadData(arg);
    auto mod_ = rd->getModel();
    auto opt_ = rd->getOption();
    auto nbSamples_ = rd->getNombreSample();
    auto rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    auto mc = new MonteCarlo(mod_, opt_, rng_, nbSamples_);
    auto deltas_ref = pnl_vect_create(opt_->size_);
    auto st_dev_ref = pnl_vect_create(opt_->size_);
    auto deltas = pnl_vect_create(opt_->size_);
    auto st_dev = pnl_vect_create(opt_->size_);
    auto market_data = pnl_mat_create_from_file("simul_basket_2.dat");
    auto past = pnl_mat_wrap_mat_rows(market_data, 0, 1);
    auto spot = pnl_mat_wrap_mat_rows(market_data, 1, 1);
    pnl_rng_sseed(mc->rng_, 0);
    mc->delta(&past, opt_->T_ / market_data->m, deltas, st_dev);
    pnl_mat_get_row(mc->mod_->spot_, &spot, 0);
    pnl_rng_sseed(mc->rng_, 0);
    mc->delta(&spot, 0., deltas_ref, st_dev_ref);

    EXPECT_NEAR(GET(deltas, 0), GET(deltas_ref, 0), 2 * 1.96 * GET(st_dev_ref, 0));
    EXPECT_NEAR(GET(deltas, 1), GET(deltas_ref, 1), 2 * 1.96 * GET(st_dev_ref, 1));

    EXPECT_NEAR(GET(st_dev, 0), GET(st_dev_ref, 0), 0.00001);
    EXPECT_NEAR(GET(st_dev, 1), GET(st_dev_ref, 1), 0.00001);
}

TEST_F(TestDelta, Performance_t) {
    char arg[] = "perf.dat";
    auto rd = new ReadData(arg);
    auto mod_ = rd->getModel();
    auto opt_ = rd->getOption();
    auto nbSamples_ = rd->getNombreSample();
    auto rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    auto mc = new MonteCarlo(mod_, opt_, rng_, nbSamples_);
    auto deltas_ref = pnl_vect_create(opt_->size_);
    auto st_dev_ref = pnl_vect_create(opt_->size_);
    auto deltas = pnl_vect_create(opt_->size_);
    auto st_dev = pnl_vect_create(opt_->size_);
    auto market_data = pnl_mat_create_from_file("simul_perf.dat");
    auto past = pnl_mat_wrap_mat_rows(market_data, 0, 1);
    auto spot = pnl_mat_wrap_mat_rows(market_data, 1, 1);
    pnl_rng_sseed(mc->rng_, 0);
    mc->delta(&past, opt_->T_ / market_data->m, deltas, st_dev);
    pnl_mat_get_row(mc->mod_->spot_, &spot, 0);
    pnl_rng_sseed(mc->rng_, 0);
    mc->delta(&spot, 0., deltas_ref, st_dev_ref);

    EXPECT_NEAR(GET(deltas, 0), GET(deltas_ref, 0), 2 * 1.96 * GET(st_dev_ref, 0));
    EXPECT_NEAR(GET(deltas, 1), GET(deltas_ref, 1), 2 * 1.96 * GET(st_dev_ref, 1));

    EXPECT_NEAR(GET(st_dev, 0), GET(st_dev_ref, 0), 0.00001);
    EXPECT_NEAR(GET(st_dev, 1), GET(st_dev_ref, 1), 0.00001);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
