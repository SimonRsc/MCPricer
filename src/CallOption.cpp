#include <assert.h>
#include "CallOption.h"
#include <iostream>
using namespace std;
double CallOption::payoff(const PnlMat *path) {

    //Un seul sous-jacent pour un Call
    assert(this->size_==1);

    double payoff = MGET(path,this->T_ ,0) ;
    payoff -=  this->K_;
    if(payoff>=0){
        return payoff;
    }else{
        return 0;
    }

}

CallOption::CallOption(double k,double t, int nbTimeSteps_, int size): Option(t,nbTimeSteps_,size) {
   this->K_ = k;

}
