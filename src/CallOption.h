//
// Created by simon on 12/09/19.
//

#ifndef MC_PRICER_CALLOPTION_H
#define MC_PRICER_CALLOPTION_H
#include "Option.hpp"

class CallOption : public Option{
public:

    CallOption(double k, double t, int nbTimeSteps, int size);

    virtual double payoff(const PnlMat *path);

private:
    double K_;

};


#endif //MC_PRICER_CALLOPTION_H
