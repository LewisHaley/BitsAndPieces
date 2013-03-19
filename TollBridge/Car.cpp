#include "Car.h"

Car::Car()
{
    m_cost = 5;
    m_passengers = rand() % 5 + 1; // random number passengers up to 5
}
