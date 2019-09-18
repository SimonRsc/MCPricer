//
// Created by simon on 16/09/19.
//

#include "ReadData.hpp"
#include "MonteCarlo.hpp"
#include <iostream>
#include <string>
#include "PricingResults.hpp"

int main(int argc, char *argv[]){

    assert(argc == 2);
    string dir= "";
    char * file = new char[100];
    strcpy(file,dir.append(argv[1]).c_str());
    auto rd = new ReadData(file);


    MonteCarlo MC(rd->getModel(),rd->getOption(),pnl_rng_create(PNL_RNG_MERSENNE),rd->getNombreSample());
    // Faut il changer la seed à chaque fois

    double prix;
    double ic;

    MC.price(prix, ic);

    PnlVect *delta = pnl_vect_create_from_zero(MC.mod_->size_);
    PnlVect *deltaStdDev = pnl_vect_create_from_zero(MC.mod_->size_);

    PnlMat *spots = pnl_mat_create(1,rd->getModel()->size_);
    pnl_mat_set_row(spots,rd->getModel()->spot_,0);
    pnl_mat_print(spots);

    MC.delta(spots,0.,delta,deltaStdDev);
    PricingResults res(prix, ic, delta, deltaStdDev);
    std::cout << res << std::endl;


}