#include <sstream>
#include <iostream>
#include "PricingResults.hpp"
#include "PnlVectToJson.hpp"

using namespace std;
std::string PricingResults::ToJson()
{
    ostringstream stm;
    stm << '{' << "\"price\": " << price << ", \"priceStdDev\": " << priceStdDev << ", \"delta\": ";
    auto result = stm.str() + ConvertToJson(delta) +  ", \"deltaStdDev\": " + ConvertToJson(deltaStdDev) + '}';
    return result;
}