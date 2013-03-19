#ifndef __GAMEMAZE_H__
#define __GAMEMAZE_H__

#include <math.h>

#include "Maze/Maze.h"
#include "Maze/Cell.h"

/// \author Lewis Haley
/// \version 1.0
/// \date 29/02/2012 \n

/// Revision History : \n
/// 29/02/2012 - Moved appropriate methods and memeber variables from Maze class
/// 29/02/2012 - Split up gameSetUp into seperate methods
/// 29/02/2012 - Made GameMaze inherit from Maze
/// 29/02/2012 - Changed doDoorsAndKeys() so key can't be placed on the entrance

/// \class GameMaze
/// \brief GameMaze class contains data for a maze, in a game context
/// \todo make sure doors are put on keys function

class GameMaze : public Maze
{
public:
    // default ctor
    GameMaze();
    // UD ctor
    // x and z dimensions of maze
    GameMaze( const unsigned _x, const unsigned _z );
    // dtor
    ~GameMaze();

    // makes maze ready for game
    void        gameSetUp( const unsigned _numObjects );

    // marks cells as dead ends
    void        markDeadEnds();
    // assign entrance and exit
    void        markEntranceExit();
    // set up maze with corresponding doors and keys
    // parameter for how many door/key pairs
    void        doDoorsAndKeys( const unsigned _num );

    // get entrance coords
    inline std::vector<unsigned>    getEntrance() const {return m_entrance;}
    // get exit coords
    inline std::vector<unsigned>    getExit() const     {return m_exit;}
    // get path
    inline std::string              getPath() const     {return m_path;}

    // get list of doors and keys
    inline std::vector<std::vector<std::vector<unsigned> > > getDoorsKeys() const {return m_doorsKeys;}

    // returns a string of instructions to get from cell A to cell B
    // parameters as seperate start/end x/z coords
    std::string findPath( unsigned _startX,
                         unsigned _startZ,
                         unsigned _endX,
                         unsigned _endZ);
    // returns a string of instructions to get from cell A to cell B
    // parameter as unsigned vector (coords)
    std::string findPath( std::vector<unsigned> _start,
                          std::vector<unsigned> _end );
    // reverses path instructions so they can be followed backwards
    std::string reversePath( std::string _instructions );

    // follows a path of instructions
    // returns coordinates of cell it reached
    std::vector<unsigned>   followPath( std::vector<unsigned> _startCell,
                                        std::string _instructions );

    // prints the maze layout in the console
    void        print();
    // print the maze with per cell info
    // argument _verb is verbosity
    // 1 is walls, 2 is walls and borders, 3 is all bools, 4 is everything
    void        printPerCell( const unsigned _verb );

private:
    // the entrance
    std::vector<unsigned>   m_entrance;
    // the exit
    std::vector<unsigned>   m_exit;
    // the path through the maze
    std::string             m_path;
    // list of matching door and key locations
    std::vector<std::vector<std::vector<unsigned > > >  m_doorsKeys;
};

#endif // __GAMEMAZE_H__
