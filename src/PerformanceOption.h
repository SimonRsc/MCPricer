//
// Created by simon on 13/09/19.
//

#ifndef MC_PRICER_PERFORMANCEOPTION_H
#define MC_PRICER_PERFORMANCEOPTION_H
#include "Option.hpp"

class PerformanceOption : public Option{
public:
    PerformanceOption(double T_, int nbTimeSteps, int size) : Option(T_,nbTimeSteps,size){}
    virtual double payoff(const PnlMat * path);
};


#endif //MC_PRICER_PERFORMANCEOPTION_H
