#include <iostream>
#include "BlackScholesModel.hpp"

void BlackScholesModel::asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng) {
    pnl_mat_set_row(path, spot_, 0);
    completePath(path, nbTimeSteps, rng, 1);
}

void BlackScholesModel::asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past) {
    pnl_mat_set_subblock(path, past, 0, 0);

    int index = past->m-1;
    pnl_vect_rng_normal(G_, size_, rng);
    double tmp  = dt_;
    dt_ = (index)*dt_-t;
    for (int c = 0; c < size_; ++c) {
        MLET(path, index, c) = next(MGET(past, index, c), c);
    }
    dt_ = tmp;
    completePath(path, nbTimeSteps, rng, index+1);
}

void BlackScholesModel::completePath(PnlMat *path, int nbTimeSteps, PnlRng *rng, int index) {
    for (int i = index; i < nbTimeSteps + 1; ++i) {
        pnl_vect_rng_normal(G_, size_, rng);
        for (int j = 0; j < size_; ++j) {
            MLET(path, i, j) = next(MGET(path, i - 1, j), j);
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

double BlackScholesModel::next(double Std, int productIndex){
    Ld_ = pnl_vect_wrap_mat_row(L_, productIndex);
    return Std*exp( GET(sigma2r_, productIndex)+GET(sigma_, productIndex)*sdt_*pnl_vect_scalar_prod(&Ld_, G_) );
}

double BlackScholesModel::next(double Std, int productIndex, double r){
    Ld_ = pnl_vect_wrap_mat_row(L_, productIndex);
    double vol = GET(sigma_, productIndex);
    return Std*exp( (r - vol*vol/2)*dt_+GET(sigma_, productIndex)*sdt_*pnl_vect_scalar_prod(&Ld_, G_) );
}

BlackScholesModel::BlackScholesModel(int size, double r, double rho, PnlVect *sigma, PnlVect *spot, int nbTimeSteps,
                                     double T) : size_(
        size), r_(r), rho_(rho), sigma_(sigma), spot_(spot) {
    CholeskyCorrelationMatrix();
    G_ = pnl_vect_create(size_);
    dt_ = T/nbTimeSteps;
    sdt_ = sqrt(dt_);
    // Compute sigma2r
    sigma2r_ = pnl_vect_copy(sigma);
    pnl_vect_mult_vect_term(sigma2r_, sigma2r_);
    pnl_vect_div_scalar(sigma2r_, 2);
    pnl_vect_minus(sigma2r_);
    pnl_vect_plus_scalar(sigma2r_, r_);
    pnl_vect_mult_scalar(sigma2r_, dt_);
}



BlackScholesModel::~BlackScholesModel() {
    pnl_mat_free(&L_);
    pnl_vect_free(&G_);
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

void BlackScholesModel::simul_market(PnlMat* market, double H, double endDate, PnlRng *rng){
    pnl_mat_set_row(market, spot_, 0);
    for (int i = 1; i < H+1; ++i) {
        pnl_vect_rng_normal(G_, size_, rng);
        for (int j = 0; j < size_; ++j) {
            MLET(market, i, j) = next(MGET(market, i - 1, j), j, GET(trend_, j));;
        }
    }
}