#ifndef VEHICLE_H
#define VEHICLE_H

#include <cstdlib>
#include <iostream>
#include "time.h"

class Vehicle
{
public:
    Vehicle(); // ctor
    ~Vehicle(); // dtor

    inline unsigned getCost() {return m_cost;}

protected:
    unsigned m_cost; // cost of vehicle to go through toll

};

#endif // VEHICLE_H
