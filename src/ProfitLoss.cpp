//
// Created by cecile on 17/09/19.
//

#include "ProfitLoss.h"
using namespace std;

void ProfitLoss::PAndL(MonteCarlo *monteCarlo, PnlMat *path, int H, double T, double &pL){
    Option *opt = monteCarlo->opt_;
    int N = monteCarlo->opt_->nbTimeSteps_;

    double V = 0;

    int subIndex = 0;

    double prix;
    double ic;
    PnlVect *dIc = pnl_vect_create(path->n);
    PnlVect *delta = pnl_vect_create(path->n);
    PnlVect *deltaMoins = pnl_vect_create(path->n);
    PnlVect *deltaTmp = pnl_vect_create(path->n);

    PnlVect * tmpVect = pnl_vect_create_from_zero(path->n);

    PnlMat *past = pnl_mat_create(1, 1);
    pnl_mat_extract_subblock(past, path, 0, 1, 0, path->n);

    PnlVect *S = pnl_vect_create(path->n);

    monteCarlo->price(prix, ic);
    monteCarlo->delta(past, 0, delta, dIc);

    pnl_mat_get_row(S, path, 0);

    V = prix - pnl_vect_scalar_prod(delta, S);

    pnl_vect_clone(deltaMoins, delta);

    for(int i = 1; i <= H; i++){

        //Creation de la sous matrice past pour les calculs du delta
        if(subIndex % (H/N) == 0){
            pnl_mat_add_row(past, past->m, tmpVect);
            subIndex = 0;

        }
        //cout<<past->m<<endl;
        pnl_mat_get_row(tmpVect, path, i);
        pnl_mat_set_row(past, tmpVect, past->m-1);

        subIndex++;


        monteCarlo->delta(past, i*T/H, delta, dIc);

        pnl_mat_get_row(S, path, i);
        pnl_vect_clone(deltaTmp, delta);

        //Calcul de la nouvelle valeur du portefeuille

        pnl_vect_minus_vect(delta, deltaMoins);
        V = V * exp((monteCarlo->mod_->r_ * T)/H) - pnl_vect_scalar_prod(delta, S);

        //FIN BOUCLE

        pnl_vect_clone(deltaMoins, deltaTmp);
    }
    double payoff = opt->payoff(path);

    pL = V + pnl_vect_scalar_prod(deltaMoins, S) - payoff;

//            34,6570315;

    pnl_vect_free(&dIc);
    pnl_vect_free(&delta);
    pnl_vect_free(&deltaMoins);
    pnl_vect_free(&deltaTmp);
    pnl_vect_free(&S);
    pnl_mat_free(&past);

}

/*void ProfitLoss::PastForDelta(MonteCarlo *monteCarlo, PnlMat *past, int H, double T, PnlMat *newPast){
    int N = monteCarlo->opt_->nbTimeSteps_;
    double dt = T/N;
    double dh = T/H;

    PnlVect *V = pnl_vect_create(past->n);
    int indexPast = 0;

    for(int i=0; i< past->m; i++){
        if(ABS(dh * i - dt * indexPast) < 0.0001){

            pnl_mat_get_row(V, past, i);
            pnl_mat_set_row(newPast, V, indexPast);
            indexPast++;
        }
    }

    pnl_mat_get_row(V, past, past->m-1);
    pnl_mat_set_row(newPast, V, newPast->m-1);
}*/