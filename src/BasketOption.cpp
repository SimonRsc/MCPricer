#include <assert.h>
#include <iostream>
#include "BasketOption.h"

 double BasketOption::payoff(const PnlMat *path) {

    return_payoff = 0;
    pnl_mat_get_row(tmp_, path,path->m-1);
    pnl_vect_mult_vect_term(tmp_,lambdas);
    return_payoff = pnl_vect_sum(tmp_);

    return_payoff -= this->K_;

    return return_payoff >= 0 ? isSell ? -return_payoff : return_payoff : 0;
}

BasketOption::BasketOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_) : Option(T_,nbTimeSteps,size_) {

    //Vérification des lambdas
    assert(pnl_vect_sum(lambdas)- 1 < 0.00001);

    this->lambdas = lambdas;
    this->K_ = (k > 0) ? k : -k;

    tmp_ = pnl_vect_create(size_);
    isSell = (k < 0);
}

BasketOption::~BasketOption() {
    pnl_vect_free(&lambdas);
    pnl_vect_free(&tmp_);
}


