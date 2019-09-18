//
// Created by simon on 16/09/19.
//

#include "ReadData.hpp"
#include "MonteCarlo.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]){

    assert(argc == 2);
    string dir= "../../data/";
    char * file = new char[100];
    strcpy(file,dir.append(argv[1]).c_str());
    auto rd = new ReadData(file);


    MonteCarlo MC(rd->getModel(),rd->getOption(),pnl_rng_create(PNL_RNG_MERSENNE),rd->getNombreSample());
    // Faut il changer la seed à chaque fois

    double prix;
    double ic;

    MC.price(prix, ic);
    cout << "Price : " << prix <<endl;
    cout << "Interval : [" << prix-ic/2<<","<<prix+ic/2<<"]"<< endl;
}