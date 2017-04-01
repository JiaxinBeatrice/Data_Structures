#ifndef PriceTableIMP_h
#define PriceTableIMP_h

#include "readonly/PriceTableADT.h"

class PriceTableIMP : public PriceTableADT
{
public:
    //=================================================================
    // calculate the all pairs shortest patch and store the results
    // in this->distTable
    //=================================================================
    void calcAllPairsShortestPath(std::string mapFile);

    //=================================================================
    // calculate and return the rental when an ubike is returned
    //=================================================================
    int calcPrice(int milageDiff, std::string bClass,
                          std::string from, std::string toStation);
};

#endif
