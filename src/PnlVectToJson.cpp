#include <sstream>
#include <iostream>
#include "PnlVectToJson.hpp"

std::string ConvertToJson(const PnlVect * const vect)
{
    int length = vect->size;
    std::ostringstream stm;
    if (length == 0) return "[]";
    stm << '[';
    for (int i = 0; i < length - 1; i++)
    {
        stm << GET(vect, i) << ", ";
    }
    stm << GET(vect, length - 1) << "]";
    return stm.str();
}