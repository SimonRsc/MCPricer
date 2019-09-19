#include <iostream>
#include "BlackScholesModel.hpp"

void BlackScholesModel::asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng) {
    double dt = T/nbTimeSteps;
    pnl_mat_set_row(path, spot_, 0);
    completePath(path, nbTimeSteps, rng, dt, 1, r_);
}

void BlackScholesModel::asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past) {
    double dt = T/nbTimeSteps;
    int index = past->m-2;

    PnlMat sub = pnl_mat_wrap_mat_rows(past, 0, index);
    pnl_mat_set_subblock(path, &sub, 0, 0);

    index++;
    pnl_vect_rng_normal(G_, size_, rng);
    for (int c = 0; c < size_; ++c) {
        MLET(path, index, c) = next(MGET(past, index, c), c, (index+1)*dt-t, r_);
    }

    completePath(path, nbTimeSteps, rng, dt, index+1, r_);
}

void BlackScholesModel::completePath(PnlMat *path, int nbTimeSteps, PnlRng *rng, double dt, int index, double r) {
    for (int i = index; i < nbTimeSteps + 1; ++i) {
        //TODO create matrix and not a vector
        pnl_vect_rng_normal(G_, size_, rng);
        for (int j = 0; j < size_; ++j) {
            MLET(path, i, j) = next(MGET(path, i - 1, j), j, dt, r);
        }
    }
}

void BlackScholesModel::CholeskyCorrelationMatrix() {
    if (rho_>=1 || rho_<= -1/(((double)size_)-1)){
        throw std::invalid_argument("Rho should be in ]−1/(D−1),1[");
    }
    L_ = pnl_mat_create_from_scalar(size_, size_, rho_);
    pnl_mat_set_diag(L_, 1, 0);
    pnl_mat_chol(L_);
}

double BlackScholesModel::next(double Std, int productIndex, double dt, double r){
    double volatility = GET(sigma_, productIndex);
    pnl_mat_get_row(Ld_, L_, productIndex);
    double LdG = pnl_vect_scalar_prod(Ld_, G_);
    double exposant = (r-pow(volatility,2)/2)*dt+volatility*sqrt(dt)*LdG;
    return Std*exp(exposant);
}


BlackScholesModel::BlackScholesModel(int size, double r, double rho, PnlVect *sigma, PnlVect *spot) : size_(
        size), r_(r), rho_(rho), sigma_(sigma), spot_(spot) {
    CholeskyCorrelationMatrix();
    G_ = pnl_vect_create(size_);
    Ld_= pnl_vect_create(size_);

}

BlackScholesModel::~BlackScholesModel() {
    pnl_mat_free(&L_);
    pnl_vect_free(&G_);
    pnl_vect_free(&Ld_);
    pnl_vect_free(&this->spot_);
    pnl_vect_free(&this->sigma_);

}

void BlackScholesModel::shiftAsset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t,
                                   double timestep) {
    int index = ceil(t/timestep);
    int m = path->m;
    pnl_mat_clone(shift_path,path);
    for (int i = index; i < m; ++i) {
        MLET(shift_path, i, d) = MGET(path, i, d)*(1+h);
    }
}

void BlackScholesModel::simul_market(PnlMat* market, double H, double endDate, PnlRng *rng){
    pnl_mat_set_row(market, spot_, 0);
    double dt = endDate/H;
    for (int i = 1; i < H+1; ++i) {
        pnl_vect_rng_normal(G_, size_, rng);
        for (int j = 0; j < size_; ++j) {
            MLET(market, i, j) = next(MGET(market, i - 1, j), j, dt, GET(trend_, j));;
        }
    }
}