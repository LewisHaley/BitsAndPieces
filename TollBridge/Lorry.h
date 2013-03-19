#ifndef LORRY_H
#define LORRY_H

#include "Vehicle.h"

class Lorry: public Vehicle
{
public:
    Lorry(); // ctor
    ~Lorry(); // dtor

private:
    int m_weight; // weight of goods
};

#endif // LORRY_H
