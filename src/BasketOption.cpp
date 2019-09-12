//
// Created by simon on 12/09/19.
//

#include <assert.h>
#include "BasketOption.h"

 double BasketOption::payoff(const PnlMat *path) {

    double payoff = 0;
    bool isSell = false;
    double strike = this->K_;
    if(this->K_ < 0){
        strike = -strike;
        isSell = true;
    }
     for (int assetNumber = 0; assetNumber < this->size_; ++assetNumber) {
         payoff += MGET(path, this->T_-1, assetNumber) - strike;
     }

     if(payoff >= 0){
         if(isSell){
             return  payoff;
         }else{
             return -payoff;
         }
     }else{
         return 0;
     }
}

BasketOption::BasketOption(double *lambdas, double k) : lambdas(lambdas), K_(k) {}
