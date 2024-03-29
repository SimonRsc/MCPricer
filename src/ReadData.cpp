#include "ReadData.hpp"
#include "3rdparty/jlparser/include/jlparser/parser.hpp"
#include "BasketOption.h"
#include "AsianOption.h"
#include "PerformanceOption.h"
#include <stdexcept>

using namespace std;

ReadData::ReadData(char *fileName) {
    double T, r, strike, correlation;
    PnlVect *spot, *sigma, *divid, *payoff_coeff;
    string model_type;
    string option_type;
    int size, timestep_number;
    size_t n_samples;

    char *infile = fileName;
    Param *P = new Parser(infile);

    P->extract("model type", model_type);
    P->extract("option type", option_type);
    P->extract("maturity", T);
    P->extract("option size", size);
    P->extract("spot", spot, size);
    P->extract("volatility", sigma, size);
    P->extract("interest rate", r);
    P->extract("correlation", correlation);

//    if (P->extract("dividend rate", divid, size, true) == false)
//    {
//        divid = pnl_vect_create_from_zero(size);
//    }

    if(option_type != "performance"){
        P->extract("strike", strike);
    }
    P->extract("sample number", n_samples);
    P->extract("timestep number", timestep_number);
    P->extract("payoff coefficients", payoff_coeff, size);

    if (model_type == "bs") {
        model = new BlackScholesModel(size, r, correlation, sigma, spot, timestep_number, T);
    } else {
        throw invalid_argument("Le type de modèle demandé n'est pas pris en compte");
    }

    if (option_type == "basket") {
        option = new BasketOption(payoff_coeff, strike, T, timestep_number, size);
        //option = new CallOption(strike, T, timestep_number, size);
    } else if (option_type == "asian") {
        option = new AsianOption(payoff_coeff, strike, T, timestep_number, size);
    } else if (option_type == "performance") {
        option = new PerformanceOption(payoff_coeff, T, timestep_number, size);
    } else {
        throw invalid_argument("Le type d'option demandé n'est pas pris en compte");
    }

    this->n_samples = n_samples;
    delete P;
}

Option* ReadData::getOption() {
    return option;
}

BlackScholesModel* ReadData::getModel() {
    return model;
}

long ReadData::getNombreSample(){
    return n_samples;
}
ReadData::~ReadData() {
    delete model;
    delete option;
}
