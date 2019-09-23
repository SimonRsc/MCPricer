#ifndef MC_PRICER_PERFORMANCEOPTION_H
#define MC_PRICER_PERFORMANCEOPTION_H
#include "Option.hpp"

/// Classe pour une option de type Performance

class PerformanceOption : public Option{

private:
    PnlVect *rowSup;
    double tmp_res;
    double sumInf;
    double sumSup;
public:

    ///
    /// \param lambdas vecteur des lambdas
    /// \param k Strike
    /// \param T_ Maturité
    /// \param nbTimeSteps nombre de dates de constatation
    /// \param size_ Nombre de sous-jacents
    PerformanceOption(PnlVect *lambdas , double T_, int nbTimeSteps, int size);
    ~PerformanceOption();

    ///
    /// \param path trajectoires des sous-jacents
    /// \return payoff de l'option
    virtual double payoff(const PnlMat * path);

    PnlVect *lambdas;
};


#endif //MC_PRICER_PERFORMANCEOPTION_H
