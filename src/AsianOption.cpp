//
// Created by simon on 13/09/19.
//

#include <iostream>
#include "AsianOption.h"
#include <assert.h>
using namespace std;

AsianOption::AsianOption(double *lambdas, double k, double T_, int nbTimeSteps, int size_) : Option(T_,nbTimeSteps,size_){

    //Vérification des lambdas
    double sum = 0;
    for(int i = 0 ; i < size_ ; ++i){
        sum += lambdas[i];
    }
    assert(sum == 1);
    assert(k >= 0);

    this->lambdas = lambdas;
    this->K_ = k;
}


double AsianOption::payoff(const PnlMat *path) {
    double payoff = 0;
    double steps =(double) 1 / (this->nbTimeSteps_ + 1);
    for(int assetNum = 0 ; assetNum < size_ ; assetNum++){
        double sum = 0;
        for(int i = 0 ; i < nbTimeSteps_; ++i){
            sum += MGET(path,i,assetNum);
        }
        payoff += lambdas[assetNum] * steps* sum;
    }
    payoff -= K_;
    if(payoff >= 0){
        return payoff;
    }else{
        return 0;
    }
}