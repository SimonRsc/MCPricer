#include <iostream>
#include "AsianOption.h"
#include <assert.h>
using namespace std;

AsianOption::AsianOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_) : Option(T_,nbTimeSteps,size_){

    //Vérification des lambdas
    assert(pnl_vect_sum(lambdas) - 1 < 0.00001);
    assert(k >= 0);

    this->lambdas = lambdas;
    this->K_ = k;

    tmp_ = pnl_vect_create(nbTimeSteps + 1);

}

AsianOption::~AsianOption() {
    pnl_vect_free(&lambdas);
    pnl_vect_free(&tmp_);
}

double AsianOption::payoff(const PnlMat *path) {
    return_payoff = 0;
    for (int Num = 0 ; Num < nbTimeSteps_ ; Num++){
        pnl_mat_get_row(tmp_, path, Num);
        return_payoff += pnl_vect_scalar_prod(tmp_, lambdas);
    }
    return_payoff /= path->m;
    return_payoff -= K_;
    if(return_payoff > 0){
        return return_payoff;
    }else{
        return 0;
    }
}