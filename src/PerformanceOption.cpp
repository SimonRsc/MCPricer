//
// Created by simon on 13/09/19.
//

#include <iostream>
#include "PerformanceOption.h"

double PerformanceOption::payoff(const PnlMat *path) {
    double payoff = 0;
for(int i = 1 ; i <= this->nbTimeSteps_ ; ++i){
    double sum_inf = 0 , sum = 0;
    for(int assetNum = 0; assetNum < this->size_ ; ++ assetNum){
        sum_inf += GET(lambdas,assetNum) * MGET(path,i-1,assetNum);
        sum +=GET(lambdas,assetNum)* MGET(path,i,assetNum);
    }
    payoff += (double) sum / sum_inf - 1;
}
if(payoff >= 0){
    return payoff + 1;
}else{
    return 1;
}
}
