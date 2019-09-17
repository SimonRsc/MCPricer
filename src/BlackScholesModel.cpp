#include <iostream>
#include "BlackScholesModel.hpp"

void BlackScholesModel::asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng) {
    double dt = T/nbTimeSteps;
    pnl_mat_set_row(path, spot_, 0);
    completePath(path, nbTimeSteps, rng, dt, 1);
}

void BlackScholesModel::asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past) {
    double dt = T/nbTimeSteps;
    int index = past->m-2;

    PnlMat sub = pnl_mat_wrap_mat_rows(past, 0, index);
    pnl_mat_set_subblock(path, &sub, 0, 0);

    index++;
    for (int c = 0; c < size_; ++c) {
        MLET(path, index, c) = next(MGET(past, index, c), c, (index+1)*dt-t,rng);
    }

    completePath(path, nbTimeSteps, rng, dt, index+1);
}

void BlackScholesModel::completePath(PnlMat *path, int nbTimeSteps, PnlRng *rng, double dt, int index) {
    for (int i = index; i < nbTimeSteps + 1; ++i) {
        for (int j = 0; j < size_; ++j) {
            MLET(path, i, j) = next(MGET(path, i - 1, j), j, dt, rng);;
        }
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
    pnl_vect_free(&this->spot_);
    pnl_vect_free(&this->sigma_);
}

void BlackScholesModel::shiftAsset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t,
                                   double timestep) {
    int index = ceil(t/timestep);
    int m = path->m;

    pnl_mat_clone(shift_path, path);

    for (int i = index; i < m; ++i) {
        MLET(shift_path, i, d) = MGET(path, i, d)*(1+h);
    }
}
