//
// Created by cecile on 17/09/19.
//

#include "ProfitLoss.h"

static void PAndL(MonteCarlo *monteCarlo, PnlMat *path, int H, double T, double *pL){
    Option *opt = monteCarlo->opt_;

    double V = 0;

    double prix;
    double ic;
    PnlVect *dIc;
    PnlVect *delta = pnl_vect_create(path->n);
    PnlVect *deltaMoins = pnl_vect_create(path->n);
    PnlVect *deltaTmp = pnl_vect_create(path->n);

    PnlMat past;

    PnlVect *S = pnl_vect_create(path->n);

    monteCarlo->price(prix, ic);
    monteCarlo->delta(NULL, 0, delta, dIc);

    pnl_mat_get_row(S, path, 0);

    V = prix - pnl_vect_scalar_prod(delta, S);

    pnl_vect_clone(deltaMoins, delta);

    for(int i = 1; i <= H; i++){
        pnl_mat_extract_subblock(&past, path, 0, i, 0, path->n - 1);

        monteCarlo->delta(&past, i, delta, dIc);

        pnl_mat_get_row(S, path, i);

        pnl_vect_clone(deltaTmp, delta);

        //Calcul de la nouvelle valeur du portefeuille

        pnl_vect_minus_vect(delta, deltaMoins);
        V = V * exp((monteCarlo->mod_->r_ * T)/H) - pnl_vect_scalar_prod(delta, S);

        //FIN BOUCLE

        pnl_vect_clone(deltaMoins, deltaTmp);

    }



}