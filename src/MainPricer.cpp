//
// Created by simon on 16/09/19.
//

#include "ReadData.hpp"
#include "MonteCarlo.hpp"
#include <iostream>
#include <filesystem>
#include <string>

int main(int argc, char *argv[]){

    assert(argc == 2);
    string dir= "../../data/";
    char * file = new char[100];
    strcpy(file,dir.append(argv[1]).c_str());
    auto rd = new ReadData(file);

    Option* option = rd->getOption();
    auto model =  rd->getModel();
    MonteCarlo MC ;

    MC.opt_ = option;
    MC.mod_ = model;
    MC.nbSamples_ = rd->getNombreSample();
    MC.rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(MC.rng_, time(0));
    // Faut il changer la seed à chaque fois

    double prix;
    double ic;

    MC.price(prix, ic);
    cout << prix <<endl;
    cout << ic << endl;

    delete option;
    delete model;

}