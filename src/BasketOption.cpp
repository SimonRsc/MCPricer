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

    pnl_mat_get_row(tmp_,path,path->m-1);
    pnl_vect_mult_vect_term(tmp_,lambdas);
    payoff = pnl_vect_sum(tmp_);

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
    assert(pnl_vect_sum(lambdas)- 1 < 0.00001);

    this->lambdas = lambdas;
    this->K_ = k;
    tmp_ = pnl_vect_create(size_);
}

BasketOption::~BasketOption() {
    pnl_vect_free(&lambdas);
    pnl_vect_free(&tmp_);
}


