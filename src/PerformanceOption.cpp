#include <iostream>
#include "PerformanceOption.h"

double PerformanceOption::payoff(const PnlMat *path) {
    double payoff = 0;
    for(int i = 1 ; i <= this->nbTimeSteps_ ; i++){
        double sum_inf = 0 , sum = 0;
        for(int assetNum = 0; assetNum < this->size_ ; assetNum++){
            sum_inf += GET(lambdas,assetNum) * MGET(path,i-1,assetNum);
            sum +=GET(lambdas,assetNum)* MGET(path,i,assetNum);
        }
        double tmp_res = ((double) sum / sum_inf) - 1;
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
