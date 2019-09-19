//
// Created by simon on 19/09/19.
//

#include <assert.h>
#include "ReadData.hpp"
#include "HedgingResults.hpp"
#include "MonteCarlo.hpp"
#include "ProfitLoss.h"

int main(int argc, char**argv){
    assert(argc == 3);

    char * marketFile = argv[1];
    char * dataInput = argv[2];

    auto rd = new ReadData(dataInput);

    MonteCarlo MC(rd->getModel(),rd->getOption(),pnl_rng_create(PNL_RNG_MERSENNE),rd->getNombreSample());

    double prix;
    double ic;
    MC.price(prix,ic);
    PnlMat *past = pnl_mat_create_from_file(marketFile);
    double covErr=0;

    ProfitLoss::PAndL(&MC,past,0.,past->m,covErr);
    HedgingResults hedgeResult(prix,ic,covErr);

}