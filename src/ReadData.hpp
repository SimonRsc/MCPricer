#ifndef MC_PRICER_READDATA_HPP
#define MC_PRICER_READDATA_HPP


#include <cstring>
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
    if (strcmp(str, "asian") == 0) {
        return ASIAN;
    } else if (strcmp(str, "basket") == 0) {
        return BASKET;
    } else if (strcmp(str, "performance") == 0) {
        return PERF;
    } else {
        return BAD_OPTION;
    }
}


#endif //MC_PRICER_READDATA_HPP
