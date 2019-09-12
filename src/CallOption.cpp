//
// Created by simon on 12/09/19.
//

#include <assert.h>
#include "CallOption.h"

double CallOption::payoff(const PnlMat *path) {

    //Un seul sous-jacent pour un Call
    assert(this->size_==1);

    double payoff = MGET(path,(this->T_/this->nbTimeSteps_)-1 ,0) - this->K_;
    if(payoff>=0){
        return payoff;
    }else{
        return 0;
    }

}

CallOption::CallOption(double k,double t, int nbTimeSteps_, int size) : K_(k) {
    this->nbTimeSteps_= nbTimeSteps_;
    this->T_=t;
    this->size_= size;
}
