//
// Created by cecile on 17/09/19.
//

#include <iostream>
#include "fakeSrc/FakeBlackScholesModel.h"
#include "../src/CallOption.h"
#include "../src/MonteCarlo.hpp"
#include <assert.h>
#include "gtest/gtest.h"
#include "../src/ProfitLoss.h"
#include "../src/BasketOption.h"
#include <sstream>

using namespace std;

class TestProfitLoss : public ::testing::Test{
public:
    BasketOption *opt;
    BlackScholesModel *mod;
    MonteCarlo *MC;

    virtual void SetUp(){


        auto lambda = pnl_vect_create_from_scalar(1, 1);
        auto spots = pnl_vect_create_from_scalar(1, 5);
        opt = new BasketOption(lambda, 1.5, 5, 5, 1);
        mod = new BlackScholesModel(1, 0.01, 0.5,lambda, spots, opt->nbTimeSteps_, opt->T_);

        //Creation de Monte Carlo
        MC = new MonteCarlo(mod,opt, pnl_rng_create(PNL_RNG_MERSENNE),100);

        // Faut il changer la seed à chaque fois
    }

    virtual void TearDown(){
        delete mod;
        delete opt;
    }
};

TEST_F(TestProfitLoss, TestPL){

    PnlMat* path = pnl_mat_create(6, 1);
    MLET(path, 0, 0) = 2.5;
    MLET(path, 1, 0) = 2;
    MLET(path, 2, 0) = 3.4;
    MLET(path, 3, 0) = 2.9;
    MLET(path, 4, 0) = 4.3;
    MLET(path, 5, 0) = 3.8;

    double pL;

    ProfitLoss::PAndL(MC, path, 5, 5, pL);

    cout<<pL<<endl;

}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}