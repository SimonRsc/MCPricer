//
// Created by simon on 12/09/19.
//

#ifndef MC_PRICER_BASKETOPTION_H
#define MC_PRICER_BASKETOPTION_H

#include "Option.hpp"

class BasketOption : public Option{
public:
    BasketOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_);


    virtual double payoff(const PnlMat *path);
    PnlVect *lambdas;
    double K_;

};


#endif //MC_PRICER_BASKETOPTION_H
