#include "Maze/Cell.h"

//----------------------------------------------------------------------------------------------------------------------
// default contructor
Cell::Cell()
{
    m_hasNB = 0;
    m_hasEB = 0;
    m_hasSB = 0;
    m_hasWB = 0;
    m_hasNW = 1;
    m_hasEW = 1;
    m_hasSW = 1;
    m_hasWW = 1;
    m_isEntrance = 0;
    m_isExit = 0;
    m_isDeadEnd = 0;
    m_isMaze = 0;
    m_isFrontier = 0;
    m_isPath = 0;
    m_isOccupied = 0;
    m_seen = 0;
}

//----------------------------------------------------------------------------------------------------------------------
// destructor
Cell::~Cell()
{
    //std::cout<<"Cell destroyed"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// prints out cell wall/border/other info
void Cell::print(const unsigned _verb)
{
    assert( 0<_verb );
    assert( _verb<5 );
    unsigned tmp = 0;
    if ( tmp < _verb )
    {
        std::cout<<"Walls: \t\t"<<m_hasNW<<m_hasEW<<m_hasSW<<m_hasWW<<std::endl;
        ++tmp;
    }
    if ( tmp < _verb )
    {
        std::cout<<"Borders: \t"<<m_hasNB<<m_hasEB<<m_hasSB<<m_hasWB<<std::endl;
        ++tmp;
    }
    if ( tmp < _verb )
    {
        std::cout<<"Entr/Exit/DEnd: "<<m_isEntrance<<m_isExit<<m_isDeadEnd<<std::endl;
        ++tmp;
    }
    if ( tmp < _verb )
    {
        std::cout<<"Other: \t\t"<<"BLANK"<<std::endl;
        ++tmp;
    }
}

//----------------------------------------------------------------------------------------------------------------------
// finds number of walls around a cell
unsigned Cell::getNumWalls()
{
    unsigned o_num = 0;
    if(m_hasNW){++o_num;}
    if(m_hasEW){++o_num;}
    if(m_hasWW){++o_num;}
    if(m_hasSW){++o_num;}
    return o_num;
}

//----------------------------------------------------------------------------------------------------------------------
// resets cell to original state
void Cell::reset()
{
    m_hasNB = 0;
    m_hasEB = 0;
    m_hasSB = 0;
    m_hasWB = 0;
    m_hasNW = 1;
    m_hasEW = 1;
    m_hasSW = 1;
    m_hasWW = 1;
    m_isEntrance = 0;
    m_isExit = 0;
    m_isDeadEnd = 0;
    m_isMaze = 0;
    m_isFrontier = 0;
    m_isPath = 0;
    m_isOccupied = 0;
    m_seen = 0;
}
