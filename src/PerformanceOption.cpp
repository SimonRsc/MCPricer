#include <iostream>
#include "PerformanceOption.h"

double PerformanceOption::payoff(const PnlMat *path) {
    return_payoff = 0;
    pnl_mat_get_row(rowSup, path, 0);
    pnl_vect_mult_vect_term(rowSup,lambdas);
    sumSup = pnl_vect_sum(rowSup);
    for (int i = 1 ; i < path->m ; i++) {
        sumInf = sumSup;
        pnl_mat_get_row(rowSup, path, i);
        pnl_vect_mult_vect_term(rowSup,lambdas);
        sumSup = pnl_vect_sum(rowSup);
        tmp_res = (sumSup / sumInf) - 1;
        if (tmp_res >= 0) {
            return_payoff += tmp_res;
        }
    }
    return return_payoff + 1;

}

PerformanceOption::PerformanceOption(PnlVect *lambdas , double T_, int nbTimeSteps, int size) : Option(T_,nbTimeSteps,size){
    this->lambdas = lambdas;
    rowSup = pnl_vect_create(size_);
    tmp_res = 0;
    sumSup = 0;
    sumInf = 0;
}

PerformanceOption::~PerformanceOption() {
    pnl_vect_free(&lambdas);
    pnl_vect_free(&rowSup);
}
