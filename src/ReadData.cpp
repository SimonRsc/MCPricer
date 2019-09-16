#include "ReadData.hpp"
#include "jlparser/parser.hpp"
#include "CallOption.h"
#include <stdexcept>

using namespace std;

ReadData::ReadData(int argc, char **argv) {
    double T, r, strike, correlation;
    PnlVect *spot, *sigma, *divid;
    string model_type;
    const char *option_type;
    int size, timestep_number;
    size_t n_samples;

    char *infile = argv[1];
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
    P->extract("strike", strike);
    P->extract("sample number", n_samples);
    P->extract("timestep number", timestep_number);

    if (model_type == "bs") {
        model = new BlackScholesModel(size, r, correlation, sigma, spot);
    } else {
        // TODO Bad model (maybe we'll use another model during the PEPS)
    }

    switch (str2option(option_type)) {
        case ASIAN:
            // option = new AsianOption();
            break;
        case BASKET:
            option = new CallOption(strike, T, timestep_number, size);
            break;
        case PERF:
            // option = new PerformanceOption();
            break;
        case BAD_OPTION:
            // TODO
            break;
    }

}

Option* ReadData::getOption() {
    return option;
}

BlackScholesModel* ReadData::getModel() {
    return model;
}

ReadData::~ReadData() {
    delete model;
    delete option;
}
