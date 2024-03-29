#pragma once

#include <assert.h>
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include <iostream>
/// \brief Classe Option abstraite
class Option
{
public:
    double T_; /// maturité
    int nbTimeSteps_; /// nombre de pas de temps de discrétisation
    int size_; /// dimension du modèle, redondant avec BlackScholesModel::size_
    double return_payoff;

    Option(double T, int nbTimeSteps, int size){
        //assert(T <= nbTimeSteps);
        this->T_ = T;
        this->nbTimeSteps_ =  nbTimeSteps;
        this->size_ = size;
        this->return_payoff = 0;
    }

     virtual ~Option() = default;

    /**
     * Calcule la valeur du payoff sur la trajectoire
     *
     * @param[in] path est une matrice de taille (N+1) x d
     * contenant une trajectoire du modèle telle que créée
     * par la fonction asset.
     * @return phi(trajectoire)
     */
    virtual double payoff(const PnlMat *path) = 0;

};


