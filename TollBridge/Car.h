#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car: public Vehicle
{
public:
    Car(); // ctor
    ~Car(); // dtor

private:
   int m_passengers; // number of passengers
};

#endif // CAR_H
