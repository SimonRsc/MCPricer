//
// Created by simon on 13/09/19.
//

#ifndef MC_PRICER_PERFORMANCEOPTION_H
#define MC_PRICER_PERFORMANCEOPTION_H
#include "Option.hpp"

class PerformanceOption : public Option{

    virtual double payoff(PnlMat * path);
};


#endif //MC_PRICER_PERFORMANCEOPTION_H
