//
// Created by simon on 13/09/19.
//

#ifndef MC_PRICER_PERFORMANCEOPTION_H
#define MC_PRICER_PERFORMANCEOPTION_H
#include "Option.hpp"

class PerformanceOption : public Option{
public:
    PerformanceOption(PnlVect *lambdas , double T_, int nbTimeSteps, int size);
    ~PerformanceOption();
    virtual double payoff(const PnlMat * path);
    PnlVect *lambdas;
};


#endif //MC_PRICER_PERFORMANCEOPTION_H
