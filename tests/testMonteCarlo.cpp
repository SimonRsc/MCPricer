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
    CallOption *opt = new CallOption(5, 5, 5, 3);

    //Création d'un modele BS
    BlackScholesModel *mod = new FakeBlackScholesModel();

    mod->size_ = 5;

    //Creation de Monte Carlo

    MonteCarlo MC ;

    MC.opt_ = opt;
    MC.mod_ = mod;
    MC.nbSamples_ = 1;


    double prix;
    double ic;

    MC.price(prix, ic);

    cout << prix <<endl;
    cout << ic << endl;



}
int main(){
    testMonteCarlo();
}