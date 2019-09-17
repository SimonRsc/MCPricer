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

public:
    ReadData(char *argv);

    ~ReadData();

    Option* getOption();

    BlackScholesModel* getModel();
};


#endif //MC_PRICER_READDATA_HPP
