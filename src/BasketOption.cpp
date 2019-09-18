#include <assert.h>
#include <iostream>
#include "BasketOption.h"

 double BasketOption::payoff(const PnlMat *path) {

    double payoff = 0;
    bool isSell = false;
    double strike = this->K_;
    
    if(strike < 0){
        strike = -strike;
        isSell = true;
    }

    PnlVect *lastRow = pnl_vect_create(size_);

    pnl_mat_get_row(lastRow,path,nbTimeSteps_);
    pnl_vect_mult_vect_term(lastRow,lambdas);
    payoff = pnl_vect_sum(lastRow);
    pnl_vect_free(&lastRow);

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
    assert(pnl_vect_sum(lambdas) == 1);

    this->lambdas = lambdas;
    this->K_ = k;
}

BasketOption::~BasketOption() {
    pnl_vect_free(&lambdas);
}


