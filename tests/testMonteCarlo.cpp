//
// Created by cecile on 13/09/19.
//
#include <iostream>
#include "fakeSrc/FakeBlackScholesModel.h"
#include "../src/CallOption.h"
#include "../src/MonteCarlo.hpp"

using namespace std;

void testMonteCarlo() {
    //Création d'un call
    CallOption *opt = new CallOption(5, 5, 5, 1);

    //Création d'un modele BS
    BlackScholesModel *mod = new BlackScholesModel(1, 0.02, 0, pnl_vect_create_from_scalar(1, 0.25), pnl_vect_create_from_scalar(1, 10));

    mod->size_ = 1;

    //Creation de Monte Carlo

    MonteCarlo MC ;

    MC.opt_ = opt;
    MC.mod_ = mod;
    MC.nbSamples_ = 1;
    MC.rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(MC.rng_, 0);


    double prix;
    double ic;

    MC.price(prix, ic);

    cout << prix <<endl;
    cout << ic << endl;



}
int main(){
    testMonteCarlo();
}