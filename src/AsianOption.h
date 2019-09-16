//
// Created by simon on 13/09/19.
//

#ifndef MC_PRICER_ASIANOPTION_H
#define MC_PRICER_ASIANOPTION_H
#include "Option.hpp"

class AsianOption : public Option {

public :
     AsianOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_);

    virtual double payoff(const PnlMat *path);
    PnlVect* lambdas;
    double K_;

};


#endif //MC_PRICER_ASIANOPTION_H
