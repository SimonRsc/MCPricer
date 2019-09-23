#include <iostream>
#include "MonteCarlo.hpp"

using namespace std;

MonteCarlo::~MonteCarlo() {
    pnl_rng_free(&rng_);
    pnl_mat_free(&path);
    pnl_mat_free(&shift_path);
}

void MonteCarlo::price(double &prix, double &st_dev){

    //Initialisation des variables necessaires
    double sum = 0;
    double sumSquare = 0;
    double phi = 0;

    int N = this->opt_->nbTimeSteps_;
    int M = this->nbSamples_;
    double T = this->opt_->T_;
    double r = this->mod_->r_;

    double estim = 0;


    //Calcul du prix a t=0
    for(int i = 0; i < M; i++){
        mod_->asset(path, T, N, this->rng_);
        phi = this->opt_->payoff(path);
        sum += phi;
        sumSquare += phi * phi;
    }

    prix = exp(-r * T) * sum / M;

    //Calcul de l'estimateur
    estim = (double) exp(-2 * r * T) *
            ((sumSquare / M) - (sum / M) * (sum / M));

    //Calcul de st_dev
    st_dev = sqrt(estim) / sqrt(M);
}

void MonteCarlo::price(const PnlMat *past, double t, double &prix, double &st_dev){
    double sum = 0;
    double sumSquare = 0;
    double phi = 0;
    double estim = 0;

    int N = this->opt_->nbTimeSteps_;
    int M = this->nbSamples_;
    double T = this->opt_->T_;
    double r = this->mod_->r_;

    for(int j = 0; j < M; j++){

        mod_->asset(path, t, T, N, this->rng_, past);
        phi = this->opt_->payoff(path);

        sum += phi;
        sumSquare += phi * phi;
    }

    prix = exp(-r * (T - t)) * sum / M;

    //Calcul de l'estimateur
    estim = (double) exp(-2 * r * (T - t)) * ((sumSquare / M) - (sum / M) * (sum / M));

    //Calcul de st_dev
    st_dev = sqrt(estim) / sqrt(M);
    }

void MonteCarlo::delta(const PnlMat *past, double t, PnlVect *delta, PnlVect *st_dev) {
    double sum;
    double sumSquare;
    double phi_minus;
    double phi_plus;

    double st;
    double estim;

    int D = this->mod_->size_;
    int N = this->opt_->nbTimeSteps_;
    int M = this->nbSamples_;
    double T = this->opt_->T_;
    double r = this->mod_->r_;

    double dt = T / N;
    double h = 0.1;

    for (int d = 0; d < D; d++) {
        sum = 0;
        sumSquare = 0;
        for (int j = 0; j < M; j++) {
            if (past->m > 1) {
                mod_->asset(path, t, T, N, this->rng_, past);
            } else {
                mod_->asset(path, T, N, this->rng_);
            }
            mod_->shiftAsset(shift_path, path, d, h, t, dt);
            phi_plus = this->opt_->payoff(shift_path);
            mod_->shiftAsset(shift_path, path, d, -h, t, dt);
            phi_minus = this->opt_->payoff(shift_path);
            sum += (phi_plus - phi_minus);
            sumSquare += (phi_plus - phi_minus) * (phi_plus - phi_minus);
        }
        st = MGET(past, past->m -1, d);
        LET(delta, d) = sum * exp(-r * (T - t)) /
                (M * 2 * st * h);
        estim = exp(-2 * r * (T - t)) *
                     ((sumSquare / M) - (sum / M) * (sum / M)) / (4 * st * st * h * h);
        LET(st_dev, d) = sqrt(estim) / sqrt(M);
    }
}

MonteCarlo::MonteCarlo(BlackScholesModel *mod, Option *opt, PnlRng *rng, int nbSamples) : mod_(mod), opt_(opt),
                                                                                          rng_(rng),
                                                                                          nbSamples_(nbSamples) {
    pnl_rng_sseed(rng_, time(0));
    path = pnl_mat_create(opt->nbTimeSteps_+1, mod->size_);
    shift_path = pnl_mat_create(opt->nbTimeSteps_+1, mod->size_);
}
