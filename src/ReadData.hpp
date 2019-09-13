#ifndef MC_PRICER_READOPTIONDATA_HPP
#define MC_PRICER_READOPTIONDATA_HPP

#include "Option.hpp"
#include "BlackScholesModel.hpp"

class ReadOptionData {

private:
    Option option;
    BlackScholesModel model;

public:
    ReadData(int argc, char **argv);

    ~ReadData();

    Option getOption() const;

    BlackScholesModel getModel() const;
};


#endif //MC_PRICER_READOPTIONDATA_HPP
