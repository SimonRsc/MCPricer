#ifndef MC_PRICER_ASIANOPTION_H
#define MC_PRICER_ASIANOPTION_H
#include "Option.hpp"

///
/// Classe pour une option de type Asian
///
class AsianOption : public Option {

private:
    PnlVect * tmp_;
    double steps;
public :
    ///
    /// \param lambdas vecteur des lambdas
    /// \param k Strike
    /// \param T_ Maturité
    /// \param nbTimeSteps nombre de dates de constatation
    /// \param size_ Nombre de sous-jacents
     AsianOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_);
    ~AsianOption();

    ///
    /// \param path trajectoires des sous-jacents
    /// \return payoff de l'option
    virtual double payoff(const PnlMat *path);

    
    PnlVect* lambdas;
    double K_;

};


#endif //MC_PRICER_ASIANOPTION_H
