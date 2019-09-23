#ifndef MC_PRICER_PERFORMANCEOPTION_H
#define MC_PRICER_PERFORMANCEOPTION_H
#include "Option.hpp"

class PerformanceOption : public Option{

private:
    PnlVect *rowInf;
    PnlVect *rowSup;
    double tmp_res;
public:
    PerformanceOption(PnlVect *lambdas , double T_, int nbTimeSteps, int size);
    ~PerformanceOption();
    virtual double payoff(const PnlMat * path);
    PnlVect *lambdas;
};


#endif //MC_PRICER_PERFORMANCEOPTION_H
