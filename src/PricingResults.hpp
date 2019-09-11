#pragma once
#include <string>
#include "pnl/pnl_vector.h"

class PricingResults
{
private:
    double price;
    PnlVect *delta;
    double priceStdDev;
    PnlVect *deltaStdDev;
public:
    PricingResults(double price, double priceStdDev, const PnlVect * const delta, const PnlVect *const deltaStdDev)
    {
        this->price = price;
        this->priceStdDev = priceStdDev;
        this->delta = pnl_vect_copy(delta);
        this->deltaStdDev = pnl_vect_copy(deltaStdDev);
    }

    ~PricingResults()
    {
        pnl_vect_free(&delta);
        pnl_vect_free(&deltaStdDev);
    }

    PricingResults(const PricingResults &pr) : price(pr.price), priceStdDev(pr.priceStdDev)
    {
        delta = pnl_vect_copy(pr.Delta());
        deltaStdDev = pnl_vect_copy(pr.DeltaStdDev());
    }

    PricingResults& operator= (const PricingResults &pr)
    {
        if (this == &pr)
        {
            return *this;
        }
        pnl_vect_free(&delta);
        pnl_vect_free(&deltaStdDev);
        price = pr.Price();
        priceStdDev = pr.PriceStdDev();
        delta = pnl_vect_copy(pr.Delta());
        deltaStdDev = pnl_vect_copy(pr.DeltaStdDev());
        return *this;
    }

    double Price() const
    {
        return price;
    }

    double PriceStdDev() const
    {
        return priceStdDev;
    }

    const PnlVect * const Delta() const
    {
        return delta;
    }

    const PnlVect * const DeltaStdDev() const
    {
        return deltaStdDev;
    }

    std::string ToJson();
};