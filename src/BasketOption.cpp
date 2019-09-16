//
// Created by simon on 12/09/19.
//

#include <assert.h>
#include <iostream>
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
         payoff += GET(lambdas,assetNumber) * MGET(path, this->T_, assetNumber);
     }
    payoff -= strike;
    if(payoff >= 0){
        if(isSell){
            return  -payoff;
       }else{
            return payoff;
        }
    }else{
       return 0;
    }
}

BasketOption::BasketOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_) : Option(T_,nbTimeSteps,size_) {

    //Vérification des lambdas
    double sum = 0;
    for(int i = 0 ; i < size_ ; ++i){
        sum += GET(lambdas,i);
    }
    assert(sum == 1);

    this->lambdas = lambdas;
    this->K_ = k;
}

BasketOption::~BasketOption() {
    pnl_vect_free(&lambdas);
}


