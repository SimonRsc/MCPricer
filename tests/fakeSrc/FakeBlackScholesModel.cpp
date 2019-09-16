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

FakeBlackScholesModel::FakeBlackScholesModel(int size, double r, double rho, PnlVect* sigma, PnlVect* spot):
BlackScholesModel(size, r, rho, sigma, spot)
{

}