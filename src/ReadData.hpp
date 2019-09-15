#ifndef MC_PRICER_READDATA_HPP
#define MC_PRICER_READDATA_HPP


#include "Option.hpp"
#include "BlackScholesModel.hpp"

class ReadData {
private:
    Option *option;
    BlackScholesModel *model;

public:
    ReadData(int argc, char **argv);

    ~ReadData();

    Option* getOption();

    BlackScholesModel* getModel();
};

enum OPTION_TYPE {ASIAN, BASKET, PERF, BAD_OPTION};

OPTION_TYPE str2option(char const *str) {
    if (str == "asian") {
        return ASIAN;
    } else if (str == "basket") {
        return BASKET;
    } else if (str == "performance") {
        return PERF;
    } else {
        return BAD_OPTION;
    }
}


#endif //MC_PRICER_READDATA_HPP
