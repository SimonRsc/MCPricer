//
// Created by cecile on 17/09/19.
//

#ifndef MC_PRICER_PROFITLOSS_H
#define MC_PRICER_PROFITLOSS_H

#include "MonteCarlo.hpp"
#include "pnl/pnl_matrix.h"

class ProfitLoss {
    static void PAndL(MonteCarlo *monteCarlo, PnlMat *path, double *pL);
};


#endif //MC_PRICER_PROFITLOSS_H
