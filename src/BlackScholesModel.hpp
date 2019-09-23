#pragma once

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include <stdexcept>
#include <math.h>

/// \brief Modèle de Black Scholes
class BlackScholesModel
{
public:
    int size_; /// nombre d'actifs du modèle
    double r_; /// taux d'intérêt
    double rho_; /// paramètre de corrélation
    double dt_; /// T/nbTimeStep
    double sdt_; /// sqrt(dt)
    PnlVect *trend_; /// tendance du modèle
    PnlVect *sigma_; /// vecteur de volatilités
    PnlVect *sigma2r_;
    PnlVect *spot_; /// valeurs initiales des sous-jacents
    PnlVect *G_; ///Vecteur de loi normale
    PnlMat *L_; /// Factorisation de Cholesky de la matrice Г
    PnlVect *Ld_;


    /**
     * Génère une trajectoire du modèle et la stocke dans path
     *
     * @param[out] path contient une trajectoire du modèle.
     * C'est une matrice de taille (nbTimeSteps+1) x d
     * @param[in] T  maturité
     * @param[in] nbTimeSteps nombre de dates de constatation
     */
    void asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng);

    /**
     * Calcule une trajectoire du modèle connaissant le
     * passé jusqu' à la date t
     *
     * @param[out] path  contient une trajectoire du sous-jacent
     * donnée jusqu'à l'instant t par la matrice past
     * @param[in] t date jusqu'à laquelle on connait la trajectoire.
     * t n'est pas forcément une date de discrétisation
     * @param[in] nbTimeSteps nombre de pas de constatation
     * @param[in] T date jusqu'à laquelle on simule la trajectoire
     * @param[in] past trajectoire réalisée jusqu'a la date t
     */
    void asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past);

    /**
     * Shift d'une trajectoire du sous-jacent
     *
     * @param[in]  path contient en input la trajectoire
     * du sous-jacent
     * @param[out] shift_path contient la trajectoire path
     * dont la composante d a été shiftée par (1+h)
     * à partir de la date t.
     * @param[in] t date à partir de laquelle on shift
     * @param[in] h pas de différences finies
     * @param[in] d indice du sous-jacent à shifter
     * @param[in] timestep pas de constatation du sous-jacent
     */
    void shiftAsset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep);

    /**
     * Calcule la factorisée de Cholesky de la matrice Γ à partir du champ rho
     * @return la factorisée L
     */
    void CholeskyCorrelationMatrix();

    /**
     * Calcule la prochaine itération du modèle de Black and Scholes pour un actif donné.
     * @param Std La précédente valeur de l'actif
     * @param productIndex l'index de l'actif dans sigma et spot
     * @param dt (ti+1 - ti)
     * @param randomGenerator le générateur aléatoire du modèle
     * @return La prochaine valeur de l'actif dans le modèle
     */
    double next(double Std, int productIndex, double r);

    BlackScholesModel(int size, double r, double rho, PnlVect *sigma, PnlVect *spot, int nbTimeSteps, double T);

    virtual ~BlackScholesModel();

    void completePath(PnlMat *path, int nbTimeSteps, PnlRng *rng, int index, double r);

    void simul_market(PnlMat* market, double H, double endDate, PnlRng *rng);
};

