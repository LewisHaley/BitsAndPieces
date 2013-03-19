#ifndef __CELL_H__
#define __CELL_H__

#include <cstdlib>
#include <iostream>
#include <cassert>

/// \author Lewis Haley
/// \version 1.0
/// \date 04/02/2012 \n

/// Revision History : \n
/// 04/02/2012 - Created class, added memeber variables and inline set/get methods
/// 08/02/2012 - Added deadEnd boolean/methods, added print method
/// 08/02/2012 - Formatted header file for tidiness
/// 10/02/2012 - Added frontier/maze bools
/// 15/02/2012 - Added getNumWalls method
/// 17/02/2012 - Added "occupied" stuff
/// 22/02/2012 - Added cell reset method

/// \class Cell
/// \brief Cell class contains data on cells for a maze, including any walls and borders, entrance/exit, any game items on this cell
/// \todo Add code for cell contents (game items), possible obstacles/ doors/ etc.

class Cell
{
public:
    // constructor
    Cell();
    // destructor
    ~Cell();

    // set hasNB on
    inline void     setHasNBOn()            {m_hasNB=1;}
    // set hasNB off
    inline void     setHasNBOff()           {m_hasNB=0;}
    // get hasNB
    inline bool     getNB() const           {return m_hasNB;}

    // set hasEB on
    inline void     setHasEBOn()            {m_hasEB=1;}
    // set hasEB off
    inline void     setHasEBOff()           {m_hasNB=0;}
    // get hasEB
    inline bool     getEB() const           {return m_hasEB;}

    // set hasSB on
    inline void     setHasSBOn()            {m_hasSB=1;}
    // set hasEB off
    inline void     setHasSBOff()           {m_hasSB=0;}
    // get hasSB
    inline bool     getSB() const           {return m_hasSB;}

    // set hasWB on
    inline void     setHasWBOn()            {m_hasWB=1;}
    // set hasWB off
    inline void     setHasWBOff()           {m_hasWB=0;}
    // get hasEB
    inline bool     getWB() const           {return m_hasWB;}

    // set hasNW on
    inline void     setHasNWOn()            {m_hasNW=1;}
    // set hasNW off
    inline void     setHasNWOff()           {m_hasNW=0;}
    // get hasNW
    inline bool     getNW() const           {return m_hasNW;}

    // set hasEW on
    inline void     setHasEWOn()            {m_hasEW=1;}
    // set hasEW off
    inline void     setHasEWOff()           {m_hasEW=0;}
    // get hasEW
    inline bool     getEW() const           {return m_hasEW;}

    // set hasSW on
    inline void     setHasSWOn()            {m_hasSW=1;}
    // set hasSW off
    inline void     setHasSWOff()           {m_hasSW=0;}
    // get hasSW
    inline bool     getSW() const           {return m_hasSW;}

    // set hasWW on
    inline void     setHasWWOn()            {m_hasWW=1;}
    // set hasWW off
    inline void     setHasWWOff()           {m_hasWW=0;}
    // get hasWW
    inline bool     getWW() const           {return m_hasWW;}

    // set isEntrance on
    inline void     setIsEntranceOn()       {m_isEntrance=1;}
    // set isEntrance off
    inline void     setIsEntranceOff()      {m_isEntrance=0;}
    // get isEntrance
    inline bool     getIsEntrance() const   {return m_isEntrance;}

    // set isExit on
    inline void     setIsExitOn()           {m_isExit=1;}
    // set isExit off
    inline void     setIsExitOff()          {m_isExit=0;}
    // get isExit
    inline bool     getIsExit() const       {return m_isExit;}

    // dead ends are where a cell has 3 walls up
    // set isDeadEnd on
    inline void     setIsDeadEndOn()        {m_isDeadEnd=1;}
    // set isExit off
    inline void     setIsDeadEndOff()       {m_isDeadEnd=0;}
    // get isExit
    inline bool     getIsDeadEnd() const    {return m_isDeadEnd;}

    // marks a cell as formed into part of the maze during path construction
    // set m_isMaze on
    inline void     setIsMazeOn()           {m_isMaze=1;}
    // set m_isMaze off
    inline void     setIsMazeOff()          {m_isMaze=0;}
    // get m_isMaze
    inline bool     getIsMaze() const       {return m_isMaze;}

    // frontier cells are in contact with the maze on at least 1 side but not part of the maze yet
    // i.e. never have m_isMaze and m_isFrontier on at the same time
    // set isFrontier on
    inline void     setIsFrontierOn()       {m_isFrontier=1;}
    // set isFrontier off
    inline void     setIsFrontierOff()      {m_isFrontier=0;}
    // get isFrontier
    inline bool     getIsFrontier() const   {return m_isFrontier;}

    // marks a cell as part of the route through the maze
    // set isPath on
    inline void     setIsPathOn()           {m_isPath=1;}
    // set isPath off
    inline void     setIsPathOff()          {m_isPath=0;}
    // get isPath
    inline bool     getIsPath() const       {return m_isPath;}

    // marks a cell as having an impassible object
    // set isOccupied on
    inline void     setIsOccupiedOn()       {m_isOccupied=1;}
    // set isOccupied off
    inline void     setIsOccupiedOff()      {m_isOccupied=0;}
    // get isOccupied
    inline bool     getIsOccupied() const   {return m_isOccupied;}

    // marks a cell as seen by player
    // set m_seen on
    inline void     setSeenOn()             {m_seen=1;}
    // set m_seen off
    inline void     setSeenOff()            {m_seen=0;}
    // get m_seen
    inline bool     getSeen() const         {return m_seen;}

    // prints out cell wall/border/other info as bit codes
    // argument _verb is verbosity
    // 1 is walls, 2 is walls and borders, 3 is all bools, 4 is everything
    void            print(const unsigned _verb);

    // finds number of walls around a cell
    unsigned        getNumWalls();

    // resets cell to original state
    void            reset();

private:
    // North border
    bool            m_hasNB;
    // East border
    bool            m_hasEB;
    // South border
    bool            m_hasSB;
    // West border
    bool            m_hasWB;
    // North wall
    bool            m_hasNW;
    // East wall
    bool            m_hasEW;
    // South wall
    bool            m_hasSW;
    // West wall
    bool            m_hasWW;
    // entrance
    bool            m_isEntrance;
    // exit
    bool            m_isExit;
    // deadend
    bool            m_isDeadEnd;
    // cell has been visited
    bool            m_isMaze;
    // cell neighbours the maze, but not part of it
    bool            m_isFrontier;
    // mark cell as part of the path
    bool            m_isPath;
    // marks if the cell is occupied and therefore impassable
    bool            m_isOccupied;
    // marks cell as seen by player
    bool            m_seen;
};

#endif //__CELL_H__
