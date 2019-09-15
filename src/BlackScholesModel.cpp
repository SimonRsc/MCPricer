//
// Created by lamur on 11/09/2019.
//
#include "BlackScholesModel.hpp"

void BlackScholesModel::asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng) {
    double dt = T/nbTimeSteps;
    for (int c = 0; c < size_; ++c) {
        MLET(path, 0, c) = GET(spot_, c);
    }
    for (int i = 1; i < nbTimeSteps+1; ++i) {
        for (int j = 0; j < size_; ++j) {
            MLET(path, i, j) = next(MGET(path, i-1, j), j, dt, rng);;
        }
    }
}

void BlackScholesModel::asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past) {
    double dt = T/nbTimeSteps;
    double tmpDate = 0;
    int index = 0;
    while (tmpDate < t){
        for (int c = 0; c < size_; ++c) {
            MLET(path, c, index) = MGET(past, c,index);
        }
        tmpDate += dt;
        index++;
    }
}

PnlMat* BlackScholesModel::CholeskyCorrelationMatrix() {
    if (rho_>=1 || rho_<= -1/(((double)size_)-1)){
        throw std::invalid_argument("Rho should be in ]−1/(D−1),1[");
    }
    PnlMat *corrMatrix = pnl_mat_create_from_scalar(size_, size_, rho_);
    pnl_mat_set_diag(corrMatrix, 1, 0);
    pnl_mat_chol(corrMatrix);
    return  corrMatrix;
}

double BlackScholesModel::next(double Std, int productIndex, double dt, PnlRng *randomGenerator){
    double volatility = GET(sigma_, productIndex);
    PnlVect *Ld = pnl_vect_create(size_);
    pnl_mat_get_row(Ld, L_, productIndex);
    PnlVect *G = pnl_vect_create(size_);
    pnl_vect_rng_normal_d(G, size_, randomGenerator);
    double LdG = pnl_vect_scalar_prod(Ld, G);
    double exposant = (r_-pow(volatility,2)/2)*dt+volatility*sqrt(dt)*LdG;
    pnl_vect_free(&G);
    pnl_vect_free(&Ld);
    return Std*exp(exposant);
}

BlackScholesModel::BlackScholesModel(int size, double r, double rho, PnlVect *sigma, PnlVect *spot) : size_(
        size), r_(r), rho_(rho), sigma_(sigma), spot_(spot) {
    L_ = CholeskyCorrelationMatrix();
}

BlackScholesModel::~BlackScholesModel() {
    pnl_mat_free(&L_);
}
