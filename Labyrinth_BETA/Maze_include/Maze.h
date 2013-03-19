#ifndef __MAZE_H__
#define __MAZE_H__

#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>

#include "Maze/Cell.h"

/// \author Lewis Haley
/// \version 1.0
/// \date 04/02/2012 \n

/// Revision History : \n
/// 04/02/2012 - Created class, added memeber variables and user defined constructor
/// 06/02/2012 - Added print method for class (debug), setup method
/// 08/02/2012 - Completed DFS method, added printPerCell method
/// 08/02/2012 - Changed DFS so origin on bottom right, not top left (works better for openGL)
/// 09/02/2012 - Fixed naming conventions and coordinate bugs for Marc
/// 09/02/2012 - Formatted header file for tidiness
/// 09/02/2012 - Added gameSetUp method
/// 10/02/2012 - Implemented HAK algorithm
/// 15/02/2012 - Implemented path finding algorithm between 2 cells
/// 22/02/2012 - Modified maze reset with new cell reset method, added follow path method
/// 22/02/2012 - Completed method to add door and key in maze so that the key is always accessible
/// 29/02/2012 - Transfered some methods into new GameMaze class

/// \class Maze
/// \brief Maze class contains data for a maze, methods for constructing a maze
/// \todo

/*********************************************************************
AUTHOR'S NOTE
  - Coordinates are always stored (x,z)
  - Methods asking for coordinates/lengths always ask for x THEN z
  - m_maze is accessed m_maze[z][x]
**********************************************************************/

class Maze
{
public:
    // default constructor
    Maze();
    // user define constructor
    // width and length arguments for maze
    Maze( const unsigned _x, const unsigned _z );
    // destrucor
    ~Maze();

    // sets up maze before path creation
    void        setUp();
    // depth first search algorithm for forming maze path
    void        makeMazeDFS();
    // hunt and kill algorithm for forming maze path
    void        makeMazeHAK();
    // resets maze
    void        reset();

    // get width of maze
    unsigned    geteastWestXAxis() const    {return m_eastWestXAxis;}
    // get length of maze
    unsigned    getnorthSouthZAxis() const  {return m_northSouthZAxis;}
    // get number of cells in maze
    unsigned    getNumCells() const         {return m_numCells;}

    // get percentage complete of maze
    unsigned    getPercentComplete() const  {return m_percentComplete;}

    // return pointer to cell in the maze
    // arguments _x _z coords of maze
    Cell*       getCell( const unsigned _x, const unsigned _z );

    // return pointer to cell in the maze
    // arguments _coord an unsigned vector representing a coordinate in the maze
    Cell*       getCell( const std::vector<unsigned> _coord );

protected:
    // width of maze
    unsigned                            m_eastWestXAxis;
    // length of maze
    unsigned                            m_northSouthZAxis;
    // number of cells in maze
    unsigned                            m_numCells;
    // percentage of maze completion
    unsigned                            m_percentComplete;
    // double vector containing maze
    std::vector< std::vector<Cell*> >   m_maze;
};

#endif //__MAZE_H__
