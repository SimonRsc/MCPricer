//
// Created by cecile on 13/09/19.
//

#include "FakeBlackScholesModel.h"

using namespace std;

void FakeBlackScholesModel::asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng){
    srand(1);

    for(int i = 0; i < nbTimeSteps + 1; i++){
        for(int j = 0; j < path->n; j++){
            MLET(path, i, j) = ((double) (rand() % 500) )/ 100;
        }
    }
}

void BlackScholesModel::asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past) {
    double dt = T / nbTimeSteps;
    double tmpDate = 0;
    int index = 0;
    while (tmpDate < t) {
        for (int c = 0; c < size_; ++c) {
            MLET(path, index, c) = MGET(past, index, c);
        }
        tmpDate += dt;
        index++;
    }
    for (int c = 0; c < size_; ++c) {
        MLET(path, index, c) = ((double) (rand() % 500) )/ 100;
    }
    index++;
    for (int i = index; i < nbTimeSteps + 1; ++i) {
        for (int j = 0; j < size_; ++j) {
            MLET(path, i, j) = ((double) (rand() % 500) )/ 100;
        }
    }
}

FakeBlackScholesModel::FakeBlackScholesModel(int size, double r, double rho, PnlVect* sigma, PnlVect* spot):
BlackScholesModel(size, r, rho, sigma, spot)
{

}