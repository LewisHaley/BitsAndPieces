#ifndef TOLLBOOTH_H
#define TOLLBOOTH_H

#include <vector>

#include "Car.h"
#include "Lorry.h"
#include "Motorbike.h"

class TollBooth
{
public:
    TollBooth();

    inline int getIncome() {return m_income;} // returns income so far
    void takeToll(); // take toll from current vehicle
    void moveOn(); // vehicles move up one position in queue
    void printQueue(); // prints contents of queue

private:
    int m_income; // total earnings
    std::vector< Vehicle* > m_queue; // the queue
};

#endif // TOLLBOOTH_H
