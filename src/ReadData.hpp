#ifndef MC_PRICER_READDATA_HPP
#define MC_PRICER_READDATA_HPP

#include <cstring>
#include <string>
#include "Option.hpp"
#include "BlackScholesModel.hpp"

using namespace std;

class ReadData {
private:
    Option *option;
    BlackScholesModel *model;
    long n_samples;

public:
    ReadData(char *argv);

    ~ReadData();

    Option* getOption();

    BlackScholesModel* getModel();

    long getNombreSample();
};


#endif //MC_PRICER_READDATA_HPP
