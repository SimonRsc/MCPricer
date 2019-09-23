#ifndef MC_PRICER_BASKETOPTION_H
#define MC_PRICER_BASKETOPTION_H

#include "Option.hpp"

/// Classe d'une option de type Basket
class BasketOption : public Option{
private:
    PnlVect * tmp_;
    bool isSell;
public:

    ///
    /// \param lambdas vecteur des lambdas
    /// \param k Strike
    /// \param T_ Maturité
    /// \param nbTimeSteps nombre de dates de constatation
    /// \param size_ Nombre de sous-jacents
    BasketOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_);
    ~BasketOption();

    ///
    /// \param path trajectoires des sous-jacents
    /// \return payoff de l'option
    virtual double payoff(const PnlMat *path);

    PnlVect *lambdas;
    double K_;

};


#endif //MC_PRICER_BASKETOPTION_H
