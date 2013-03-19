#include "Lorry.h"

Lorry::Lorry()
{
    m_cost = 10;
    m_weight = rand() % 10 + 1; // random weight in tonnes
}
