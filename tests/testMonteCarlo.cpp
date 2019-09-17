//
// Created by cecile on 13/09/19.
//
#include <iostream>
#include "fakeSrc/FakeBlackScholesModel.h"
#include "../src/CallOption.h"
#include "../src/MonteCarlo.hpp"
#include <assert.h>
#include "gtest/gtest.h"
#include <sstream>

using namespace std;

/*
void testMonteCarlo() {
    //Création d'un call
    CallOption *opt = new CallOption(5, 5, 5, 1);

    //Création d'un modele BS
    //BlackScholesModel *mod = new BlackScholesModel(1, 0.02, 0, pnl_vect_create_from_scalar(1, 0.25), pnl_vect_create_from_scalar(1, 10));
    auto lambda = pnl_vect_create_from_scalar(1, 0.25);
    auto spots = pnl_vect_create_from_scalar(1, 10);
    BlackScholesModel *mod = new FakeBlackScholesModel(1, 0.01, 0,lambda, spots);

    //Creation de Monte Carlo

    MonteCarlo MC ;

    MC.opt_ = opt;
    MC.mod_ = mod;
    MC.nbSamples_ = 1;
    MC.rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(MC.rng_, 1234);
    // Faut il changer la seed à chaque fois

    double prix;
    double ic;

    MC.price(prix, ic);
    //Attention pour ic si nb rep = 1 pas d'intervalle
    cout << prix <<endl;
    cout << ic << endl;

delete mod;
delete opt;

}*/

class MonteCarloTests : public ::testing::Test{
    CallOption *opt;
    BlackScholesModel *mod;
    MonteCarlo MC;

    virtual void SetUp(){
        opt = new CallOption(1, 5, 5, 1);

        //Création d'un modele BS
        //BlackScholesModel *mod = new BlackScholesModel(1, 0.02, 0, pnl_vect_create_from_scalar(1, 0.25), pnl_vect_create_from_scalar(1, 10));
        auto lambda = pnl_vect_create_from_scalar(1, 0.25);
        auto spots = pnl_vect_create_from_scalar(1, 5);
        mod = new FakeBlackScholesModel(1, 0.01, 0.5,lambda, spots);

        //Creation de Monte Carlo

        MC.opt_ = opt;
        MC.mod_ = mod;
        MC.nbSamples_ = 1;
        MC.rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
        pnl_rng_sseed(MC.rng_, 1234);
        // Faut il changer la seed à chaque fois
    }

    virtual void TearDown(){
        delete mod;
        delete opt;
    }
};

TEST_F(MonteCarloTests, PriceInit){
    //Création d'un call
    CallOption *opt = new CallOption(1, 5, 5, 1);

    //Création d'un modele BS
    //BlackScholesModel *mod = new BlackScholesModel(1, 0.02, 0, pnl_vect_create_from_scalar(1, 0.25), pnl_vect_create_from_scalar(1, 10));
    auto lambda = pnl_vect_create_from_scalar(1, 0.25);
    auto spots = pnl_vect_create_from_scalar(1, 5);
    BlackScholesModel *mod = new FakeBlackScholesModel(1, 0.01, 0.5,lambda, spots);

    //Creation de Monte Carlo

    MonteCarlo MC ;

    MC.opt_ = opt;
    MC.mod_ = mod;
    MC.nbSamples_ = 1;
    MC.rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(MC.rng_, 1234);
    // Faut il changer la seed à chaque fois

    double prix;
    double ic;

    MC.price(prix, ic);
    //Attention pour ic si nb rep = 1 pas d'intervalle
    cout << prix <<endl;
    EXPECT_FLOAT_EQ(ic, 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}