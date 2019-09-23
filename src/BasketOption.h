#ifndef MC_PRICER_BASKETOPTION_H
#define MC_PRICER_BASKETOPTION_H

#include "Option.hpp"

class BasketOption : public Option{
private:
    PnlVect * tmp_;
    bool isSell;
public:
    BasketOption(PnlVect *lambdas, double k, double T_, int nbTimeSteps, int size_);
    ~BasketOption();

    virtual double payoff(const PnlMat *path);
    PnlVect *lambdas;
    double K_;

};


#endif //MC_PRICER_BASKETOPTION_H
