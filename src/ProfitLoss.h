//
// Created by cecile on 17/09/19.
//

#ifndef MC_PRICER_PROFITLOSS_H
#define MC_PRICER_PROFITLOSS_H

#include "MonteCarlo.hpp"
#include "pnl/pnl_matrix.h"

class ProfitLoss {
public:
    static void PAndL(MonteCarlo *monteCarlo, PnlMat *path, int H, double T, double &pL);
   // void PastForDelta(MonteCarlo *monteCarlo, PnlMat *past, int H, double T, PnlMat *newPast);
};


#endif //MC_PRICER_PROFITLOSS_H

