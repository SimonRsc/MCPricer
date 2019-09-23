#include <iostream>
#include "fakeSrc/FakeBlackScholesModel.h"
#include "../src/CallOption.h"
#include "../src/MonteCarlo.hpp"
#include <assert.h>
#include "gtest/gtest.h"
#include "../src/BasketOption.h"
#include <sstream>

using namespace std;

class MonteCarloTests : public ::testing::Test{
    public:
        BasketOption *opt;
        BlackScholesModel *mod;
        MonteCarlo *MC;

    virtual void SetUp(){

        //Création d'un modele BS
        //BlackScholesModel *mod = new BlackScholesModel(1, 0.02, 0, pnl_vect_create_from_scalar(1, 0.25), pnl_vect_create_from_scalar(1, 10));
        auto lambda = pnl_vect_create_from_scalar(1, 1);
        auto spots = pnl_vect_create_from_scalar(1, 5);

        opt = new BasketOption(lambda, 5, 5,5, 1);
        mod = new FakeBlackScholesModel(1, 0.01, 0.5,lambda, spots, 5, 5);

        //Creation de Monte Carlo
        MC = new MonteCarlo(mod, opt, pnl_rng_create(PNL_RNG_MERSENNE), 1);
        pnl_rng_sseed(MC->rng_, 1);
        // Faut il changer la seed à chaque fois
    }

    virtual void TearDown(){
        delete mod;
        delete opt;
    }
};

TEST_F(MonteCarloTests, PriceInit){

    double prix;
    double ic;

    MC->price(prix, ic);
    //Attention pour ic si nb rep = 1 pas d'intervalle
    EXPECT_FLOAT_EQ(prix, 38.478336);
    EXPECT_FLOAT_EQ(ic, 0);
}

TEST_F(MonteCarloTests, PricePast){
    double prix;
    double ic;

    PnlMat *past = pnl_mat_create(2, 1);
    MLET(past, 0, 0) = 2;
    MLET(past, 1, 0) = 2.5;

    MC->price(past, 2, prix, ic);
    EXPECT_FLOAT_EQ(prix, 0.58539701);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}