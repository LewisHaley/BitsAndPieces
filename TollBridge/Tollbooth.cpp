#include "Tollbooth.h"

TollBooth::TollBooth()
{
    m_income = 0;
    for(unsigned i=0; i<10; ++i)
    {
        unsigned decide = rand() % 3;
        if (decide == 0)
        {
            m_queue.push_back( new Car() );
        }
        else if (decide == 1)
        {
            m_queue.push_back( new Lorry() );
        }
        else
        {
            m_queue.push_back( new Motorbike() );
        }
    }
}

void TollBooth::takeToll()
{
    m_income += m_queue[0]->getCost();
}

void TollBooth::moveOn()
{
    // remove the first element in the list
    m_queue.erase( m_queue.begin() );

    // randomly add new vehicle to end of list
    unsigned decide = rand() % 3;
    if (decide == 0)
    {
        m_queue.push_back( new Car() );
    }
    else if (decide == 1)
    {
        m_queue.push_back( new Lorry() );
    }
    else
    {
        m_queue.push_back( new Motorbike() );
    }
}

void TollBooth::printQueue()
{
    for(unsigned i = 0; i<m_queue.size(); ++i)
    {
        for(unsigned j=0; j<i; ++j)
        {
            std::cout<<" ";
        }
        unsigned val = m_queue[i]->getCost();
        switch ( val )
        {
        case 5:
            std::cout<<"Car\n";
            break;
        case 10:
            std::cout<<"Lorry\n";
            break;
        case 2:
            std::cout<<"Motorbike\n";
            break;
        }
    }
}
