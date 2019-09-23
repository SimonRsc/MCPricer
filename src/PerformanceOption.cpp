#include <iostream>
#include "PerformanceOption.h"

double PerformanceOption::payoff(const PnlMat *path) {
    return_payoff = 0;
    for (int i = 1 ; i < path->m ; i++) {
        for (int assetNum = 0 ; assetNum < this->size_ ; assetNum++){
            pnl_mat_get_row(rowInf, path,i-1);
            pnl_mat_get_row(rowSup, path, i);
            pnl_vect_mult_vect_term(rowInf,lambdas);
            pnl_vect_mult_vect_term(rowSup,lambdas);
        }
        tmp_res = ((double) pnl_vect_sum(rowSup) / pnl_vect_sum(rowInf)) - 1;
        if (tmp_res >= 0) {
            return_payoff += tmp_res;
        }
    }
    return return_payoff + 1;

}

PerformanceOption::PerformanceOption(PnlVect *lambdas , double T_, int nbTimeSteps, int size) : Option(T_,nbTimeSteps,size){
    this->lambdas = lambdas;
    rowInf = pnl_vect_create(size_);
    rowSup = pnl_vect_create(size_);
}

PerformanceOption::~PerformanceOption() {
    pnl_vect_free(&lambdas);
    pnl_vect_free(&rowInf);
    pnl_vect_free(&rowSup);
}
