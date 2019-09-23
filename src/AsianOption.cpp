#include <iostream>
#include "AsianOption.h"
#include <assert.h>
using namespace std;

AsianOption::AsianOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_) : Option(T_,nbTimeSteps,size_){

    //Vérification des lambdas
    assert(pnl_vect_sum(lambdas)-1<0.00001);
    assert(k >= 0);

    this->lambdas = lambdas;
    this->K_ = k;
}

AsianOption::~AsianOption() {
    pnl_vect_free(&lambdas);
}

double AsianOption::payoff(const PnlMat *path) {
    double payoff = 0;
    double steps =(double) 1 / (path->m );
    auto tmp_ = pnl_vect_create(path->m);
    for(int assetNum = 0 ; assetNum < size_ ; assetNum++){
        pnl_mat_get_col(tmp_,path,assetNum);
        payoff += GET(lambdas,assetNum) * steps* pnl_vect_sum(tmp_);
    }
    payoff -= K_;
    pnl_vect_free(&tmp_);
    if(payoff >= 0){
        return payoff;
    }else{
        return 0;
    }

}