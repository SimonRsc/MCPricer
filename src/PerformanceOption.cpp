#include <iostream>
#include "PerformanceOption.h"

double PerformanceOption::payoff(const PnlMat *path) {
    double payoff = 0;
    PnlVect *rowInf = pnl_vect_create(size_);
    PnlVect *rowSup = pnl_vect_create(size_);

    for(int i = 1 ; i < path->m ; i++){
        //double sum_inf = 0 , sum = 0;
        for(int assetNum = 0; assetNum < this->size_ ; assetNum++){
            pnl_mat_get_row(rowInf,path,i-1);
            pnl_mat_get_row(rowSup,path,i);
            pnl_vect_mult_vect_term(rowInf,lambdas);
            pnl_vect_mult_vect_term(rowSup,lambdas);
            /*
            sum_inf += GET(lambdas,assetNum) * MGET(path,i-1,assetNum);
            sum +=GET(lambdas,assetNum)* MGET(path,i,assetNum);*/
        }
        double tmp_res = ((double) pnl_vect_sum(rowSup) / pnl_vect_sum(rowInf)) - 1;
        if(tmp_res >= 0){
            payoff+= tmp_res;
        }
    }
    return payoff + 1;

}

PerformanceOption::PerformanceOption(PnlVect *lambdas , double T_, int nbTimeSteps, int size) : Option(T_,nbTimeSteps,size){
    this->lambdas = lambdas;
}

PerformanceOption::~PerformanceOption() {
    pnl_vect_free(&lambdas);
}
