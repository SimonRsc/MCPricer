//
// Created by cecile on 12/09/19.
//
#include <iostream>
#include "MonteCarlo.hpp"

using namespace std;

void MonteCarlo::price(double &prix, double &ic){

    //Initialisation des variables necessaires
    double sum = 0;
    double sumSquare = 0;
    double phi =0;
    int nbAssets = this->mod_->size_;
    int nbTimeSteps = this->opt_->nbTimeSteps_;

    PnlMat *path = pnl_mat_create(nbAssets, nbTimeSteps+1);

    double estim = 0;


    //Calcul du prix a t=0
    for(int i = 0; i < this->nbSamples_; i++){
        mod_->asset(path, this->opt_->T_, nbTimeSteps, this->rng_);
        phi = this->opt_->payoff(path);
        sum += phi;
        sumSquare += pow(phi, 2);
    }

    pnl_mat_free(& path);

    prix = exp(-this->mod_->r_ * this->opt_->T_) * sum / this->nbSamples_;

    //Calcul de l'estimateur

    estim = exp(-2 * this->mod_->r_ * this->opt_->T_) * ((sumSquare/this->nbSamples_) - pow(sum/this->nbSamples_,2));

    //Calcul de l'intervalle de confiance a 95%

    ic = 2 * 1.96 * sqrt(estim) / sqrt(this->nbSamples_);
}

