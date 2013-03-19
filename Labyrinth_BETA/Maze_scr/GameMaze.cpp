#include "Maze/GameMaze.h"

//----------------------------------------------------------------------------------------------------------------------
// default ctor
GameMaze::GameMaze()
{
    std::cout<<"WARNING! Maze empty!"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// requires a pointer to a maze object
// UD ctor
GameMaze::GameMaze( const unsigned _x, const unsigned _z )
{
    // clear any existing data
    m_entrance.clear();
    m_exit.clear();
    m_path.clear();
    for (unsigned i=0; i<m_doorsKeys.size(); ++i)
    {
        for (unsigned j=0; j<m_doorsKeys[i].size(); ++j)
        {
            m_doorsKeys[i][j].clear();
        }
    }

    assert(_x>0);
    assert(_z>0);

    // initialise the width and length as per input
    m_eastWestXAxis = _x;
    m_northSouthZAxis = _z;
    m_numCells = m_eastWestXAxis * m_northSouthZAxis;

    // fill up the 2D vector with Cell objects
    for (unsigned z=0; z<m_northSouthZAxis; ++z)
    {
        m_maze.push_back( std::vector<Cell*>() );

        for (unsigned x=0; x<m_eastWestXAxis; ++x)
        {
            m_maze[z].push_back( new Cell() );
        }
    }
    setUp();
    makeMazeHAK();
}

//----------------------------------------------------------------------------------------------------------------------
// dtor
GameMaze::~GameMaze()
{

}

//----------------------------------------------------------------------------------------------------------------------
// makes maze ready for game
void GameMaze::gameSetUp( const unsigned _numObjects )
{
    // mark all dead ends
    markDeadEnds();

    // mark entrance and exit cells
    markEntranceExit();

    assert( _numObjects<m_numCells/4);

    // puts doors and keys in maze
    doDoorsAndKeys( _numObjects );

    // turn off all m_occupied flags
    for (unsigned z=0; z<m_northSouthZAxis; ++z)
    {
        for (unsigned x=0; x<m_eastWestXAxis; ++x)
        {
            getCell( x, z )->setIsOccupiedOff();
        }
    }
    // turn on occupiedflag  for door cells
    for (unsigned i=0; i<m_doorsKeys.size(); ++i)
    {
        getCell( m_doorsKeys[i][0] )->setIsOccupiedOn();
    }
}
//----------------------------------------------------------------------------------------------------------------------
// returns a string of instructions to get from cell A to cell B
std::string GameMaze::findPath( unsigned _startX,
                            unsigned _startZ,
                            unsigned _endX,
                            unsigned _endZ )
{
    // clear any existing path information
    for (unsigned z=0; z<getnorthSouthZAxis(); ++z)
    {
        for (unsigned x=0; x<geteastWestXAxis(); ++x)
        {
            getCell(x,z)->setIsPathOff();
        }
    }

    // an empty vector to hold list of cells visited
    std::vector<std::vector<unsigned> > cellPath;
    // an empty vector to hold directions followed
    std::vector<char> moves;
    // set start cell to be the current cell
    std::vector<unsigned> currentCell;
    currentCell.push_back( _startX );
    currentCell.push_back( _startZ );
    getCell(currentCell[0],currentCell[1])->setIsPathOn();
    // set up end cell
    std::vector<unsigned> endCell;
    endCell.push_back( _endX );
    endCell.push_back( _endZ );
    // add current cell to cellPath
    cellPath.push_back( currentCell );

    // initialise a variable to tell us whether the path we followed was blocked by an object
    bool pathBlocked = 0;

    // while the current cell is not equal to the end cell
    while ( currentCell != endCell )
    {
        // get possible moves
        std::vector<char> possibleMoves;
        // check movement north
        if ( !( getCell( currentCell )->getNW() ) &&
             !( getCell( currentCell[0], currentCell[1]+1 )->getIsPath() ) &&
             !( getCell( currentCell )->getNB() ) )
        {
            possibleMoves.push_back('N');
        }
        // check movement east
        if ( !( getCell( currentCell )->getEW() ) &&
             !( getCell(currentCell[0]-1, currentCell[1] )->getIsPath() ) &&
             !( getCell( currentCell )->getEB() )  )
        {
            possibleMoves.push_back('E');
        }
        // check movement south
        if ( !( getCell( currentCell )->getSW() ) &&
             !( getCell( currentCell[0], currentCell[1]-1 )->getIsPath() ) &&
             !( getCell( currentCell )->getSB() )  )
        {
            possibleMoves.push_back('S');
        }
        // check movement west
        if ( !( getCell( currentCell )->getWW() ) &&
             !( getCell( currentCell[0]+1, currentCell[1] )->getIsPath() ) &&
             !( getCell( currentCell )->getWB() )  )
        {
            possibleMoves.push_back('W');
        }

        // if the list of possible moves is not empty (zero length)
        if ( possibleMoves.size() > 0 )
        {
            // chose at random from possible moves
            unsigned index = rand() % possibleMoves.size();
            char movingTo = possibleMoves[index];
            // add the movement we are making to list of moves
            moves.push_back( movingTo );

            // change currentCell according to movement
            if ( movingTo == 'N')
            {
                currentCell[1] += 1;
                //std::cout<<"N"<<std::endl;
            }
            else if ( movingTo == 'E')
            {
                currentCell[0] -= 1;
                //std::cout<<"E"<<std::endl;
            }
            else if ( movingTo == 'S')
            {
                currentCell[1] -= 1;
                //std::cout<<"S"<<std::endl;
            }
            else if ( movingTo == 'W')
            {
                currentCell[0] += 1;
                //std::cout<<"W"<<std::endl;
            }

            // add current cell to cellPath
            cellPath.push_back( currentCell );
            // set the current cell to be part of the path
            getCell( currentCell )->setIsPathOn();

            // check to see if the cell we are now in was occupied
            // if true, then our path is blocked
            if ( getCell( currentCell )->getIsOccupied() )
            {
                pathBlocked = 1;
            }

        }
        else /* if there are no moves */
        {
            // check if the cell we are in was blocking our path
            // if it was, then make the path unblocked
            if ( getCell( currentCell )->getIsOccupied() )
            {
                pathBlocked = 0;
            }

            // go back to the previous cell in the cellPath list
            // set current cell to previous
            currentCell = cellPath[cellPath.size()-2];
            // remove last cell from cell path
            cellPath.pop_back();
            // remove last move from moves list
            moves.pop_back();
        }
    }

    std::string o_string;
    if ( pathBlocked )
    {
        o_string += 'X';
    }
    else
    {
        // add every character stored in moves list to the string
        for (unsigned i=0; i<moves.size(); ++i)
        {
            o_string += moves[i];
        }
    }
    return o_string;
}

//----------------------------------------------------------------------------------------------------------------------
// returns a string of instructions to get from cell A to cell B
// parameter as unsigned vector (coords)
std::string GameMaze::findPath( std::vector<unsigned> _start,
                      std::vector<unsigned> _end )
{
    // clear any existing path information
    for (unsigned z=0; z<getnorthSouthZAxis(); ++z)
    {
        for (unsigned x=0; x<geteastWestXAxis(); ++x)
        {
            getCell(x,z)->setIsPathOff();
        }
    }

    // an empty vector to hold list of cells visited
    std::vector<std::vector<unsigned> > cellPath;
    // an empty vector to hold directions followed
    std::vector<char> moves;
    // set start cell to be the current cell
    std::vector<unsigned> currentCell = _start;
    getCell( currentCell[0],currentCell[1] )->setIsPathOn();
    // set up end cell
    std::vector<unsigned> endCell = _end;
    // add current cell to cellPath
    cellPath.push_back( currentCell );

    /***********
      MAIN LOOP
      **********/

    // while the current cell is not equal to the end cell
    while ( currentCell != endCell )
    {
        // get possible moves
        std::vector<char> possibleMoves;
        // check movement north
        if ( !( getCell( currentCell )->getNW() ) &&
             !( getCell( currentCell[0], currentCell[1]+1 )->getIsPath() ) &&
             !( getCell( currentCell )->getNB() ) )
        {
            possibleMoves.push_back('N');
        }
        // check movement east
        if ( !( getCell( currentCell )->getEW() ) &&
             !( getCell(currentCell[0]-1, currentCell[1] )->getIsPath() ) &&
             !( getCell( currentCell )->getEB() )  )
        {
            possibleMoves.push_back('E');
        }
        // check movement south
        if ( !( getCell( currentCell )->getSW() ) &&
             !( getCell( currentCell[0], currentCell[1]-1 )->getIsPath() ) &&
             !( getCell( currentCell )->getSB() )  )
        {
            possibleMoves.push_back('S');
        }
        // check movement west
        if ( !( getCell( currentCell )->getWW() ) &&
             !( getCell( currentCell[0]+1, currentCell[1] )->getIsPath() ) &&
             !( getCell( currentCell )->getWB() )  )
        {
            possibleMoves.push_back('W');
        }

        // if the list of possible moves is not empty (zero length)
        if ( possibleMoves.size() > 0 )
        {
            // chose at random from possible moves
            unsigned index = rand() % possibleMoves.size();
            char movingTo = possibleMoves[index];
            // add the movement we are making to list of moves
            moves.push_back( movingTo );

            // change currentCell according to movement
            if ( movingTo == 'N')
            {
                currentCell[1] += 1;
                //std::cout<<"N"<<std::endl;
            }
            else if ( movingTo == 'E')
            {
                currentCell[0] -= 1;
                //std::cout<<"E"<<std::endl;
            }
            else if ( movingTo == 'S')
            {
                currentCell[1] -= 1;
                //std::cout<<"S"<<std::endl;
            }
            else if ( movingTo == 'W')
            {
                currentCell[0] += 1;
                //std::cout<<"W"<<std::endl;
            }

            // add current cell to cellPath
            cellPath.push_back( currentCell );
            // set the current cell to be part of the path
            getCell( currentCell )->setIsPathOn();

        }
        else /* if there are no moves */
        {
            // go back to the previous cell in the cellPath list
            // set current cell to previous
            currentCell = cellPath[cellPath.size()-2];
            // remove last cell from cell path
            cellPath.pop_back();
            // remove last move from moves list
            moves.pop_back();
        }
    } // path now found

    // the string we will return
    std::string o_string;

    // add every character stored in moves list to the string
    for (unsigned i=0; i<moves.size(); ++i)
    {
        o_string += moves[i];
    }

    // check path isn't blocked
    bool pathBlocked = 0;
    currentCell = _start;

    // for every move in the path check its value
    for (unsigned i=0; i<o_string.size(); ++i)
    {
        if ( o_string[i] == 'N' )
        {
            currentCell[1] = currentCell[1]+1;
        }
        else if ( o_string[i] == 'E' )
        {
            currentCell[0] = currentCell[0]-1;
        }
        else if ( o_string[i] == 'S' )
        {
            currentCell[1] = currentCell[1]-1;
        }
        else if ( o_string[i] == 'W' )
        {
            currentCell[0] = currentCell[0]+1;
        }

        if ( getCell( currentCell )->getIsOccupied() &&
             !getCell( currentCell )->getIsEntrance() &&
             !getCell( currentCell )->getIsExit() )
        {
            pathBlocked = 1;
        }
    }

    if ( pathBlocked == 1 )
    {
        o_string.clear();
        o_string += 'X';
        return o_string;
    }
    else
    {
        return o_string;
    }
}

//----------------------------------------------------------------------------------------------------------------------
// follows a path of instructions
// returns coordinates of cell it reached
std::vector<unsigned> GameMaze::followPath( std::vector<unsigned> _startCell,
                                        std::string _instructions )
{
    assert( _instructions[0] != 'X' );
    // make start cell the current cell
    std::vector<unsigned> o_currentCell = _startCell;
    // for every instruction in the list, change current cell accordingly
    for (unsigned i=0; i<_instructions.size(); ++i)
    {
        if ( _instructions[i] == 'N' )
        {
            o_currentCell[1] = o_currentCell[1]+1;
        }
        else if ( _instructions[i] == 'E' )
        {
            o_currentCell[0] = o_currentCell[0]-1;
        }
        else if ( _instructions[i] == 'S' )
        {
            o_currentCell[1] = o_currentCell[1]-1;
        }
        else if ( _instructions[i] == 'W' )
        {
            o_currentCell[0] = o_currentCell[0]+1;
        }
    }
    return o_currentCell;
}

//----------------------------------------------------------------------------------------------------------------------
// reverses path instructions so they can be followed backwards
std::string GameMaze::reversePath(
        std::string _instructions )
{
    assert ( !_instructions.empty() );
    // create string to output
    std::string o_string;
    // cycle through the instructions in reverse, swapping directions
    for (unsigned i=1; i<_instructions.size()+1; ++i)
    {
        unsigned j = _instructions.size()-i;
        if ( _instructions[j] == 'N' )
        {
            o_string += 'S';
        }
        else if ( _instructions[j] == 'E' )
        {
            o_string += 'W';
        }
        else if ( _instructions[j] == 'S' )
        {
            o_string += 'N';
        }
        else if ( _instructions[j] == 'W' )
        {
            o_string += 'E';
        }
    }
    return o_string;
}

//----------------------------------------------------------------------------------------------------------------------
// prints the maze in the console
void GameMaze::print()
{
    for (unsigned x=0; x<geteastWestXAxis(); ++x)
    {
        std::cout<<"._"; // row of underscores for top line
    }
    std::cout<<".\n";
    //for every ROW
    for (unsigned z=0; z<getnorthSouthZAxis(); ++z)
    {
        std::cout<<"|"; // add polon at start of each row
        // check each CELL (column)
        for (unsigned x=0; x<geteastWestXAxis(); ++x)
        {
            if( getCell(geteastWestXAxis()-x-1,getnorthSouthZAxis()-z-1)->getIsEntrance() ||
                getCell(geteastWestXAxis()-x-1,getnorthSouthZAxis()-z-1)->getIsExit() )
            {
                std::cout<<"#.";
            }
            else
            {
                // if the CELL has a SOUTH WALL or SOUTH BORDER
                if ( getCell(geteastWestXAxis()-x-1,getnorthSouthZAxis()-z-1)->getSB() ||
                     getCell(geteastWestXAxis()-x-1,getnorthSouthZAxis()-z-1)->getSW() )
                {
                    // draw a WALL
                    std::cout<<"_";
                }
                else
                {
                    // otherwise leave it BLANK
                    std::cout<<" ";
                }
                // if the CELL has an EAST WALL or EAST BORDER
                if ( getCell(geteastWestXAxis()-x-1,getnorthSouthZAxis()-z-1)->getEB() ||
                     getCell(geteastWestXAxis()-x-1,getnorthSouthZAxis()-z-1)->getEW() )
                {
                    // draw a WALL
                    std::cout<<"|";
                }
                else
                {
                    // otherwise leave it BLANK
                    std::cout<<".";
                }
            }
        }
        std::cout<<"\n";
    }
}

//----------------------------------------------------------------------------------------------------------------------
// print the maze with per cell info
void GameMaze::printPerCell( const unsigned _verb )
{
    for (unsigned z=0; z<getnorthSouthZAxis(); ++z)
    {
        for (unsigned x=0; x<geteastWestXAxis(); ++x)
        {
            std::cout<<"Cell ("<<x<<", "<<z<<")"<<std::endl;
            getCell(x,z)->print(_verb);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
// marks cells as dead ends
void GameMaze::markDeadEnds()
{
    for (unsigned z=0; z<getnorthSouthZAxis(); ++z)
    {
        for (unsigned x=0; x<geteastWestXAxis(); ++x)
        {
            // if a cell has 3 walls up
            if ( getCell(x,z)->getNumWalls() == 3 )
            {
                // it is a dead end
                getCell(x,z)->setIsDeadEndOn();
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
// assign entrance and exit
void GameMaze::markEntranceExit()
{
    // make vector to store possible entrances/exits
    std::vector<std::vector<unsigned> > deadEnds;
    unsigned pathLength = 0;
    // don't want the path from entrance to exit to be too short
    // check the path length using the path finding method
    while ( pathLength < (geteastWestXAxis()+getnorthSouthZAxis()-1) )
    {
        // make empty vector to store coords
        std::vector<unsigned> tmpCoord;
        // assigns the entrance and exit to the maze
        // always at the borders
        for (unsigned z=0; z<getnorthSouthZAxis(); ++z)
        {
            for (unsigned x=0; x<geteastWestXAxis(); ++x)
            {
                // if cell[z][x] is a dead end
                if ( getCell(x,z)->getIsDeadEnd() )
                {
                    // add the x,z coords to tmp coord
                    tmpCoord.push_back(x);
                    tmpCoord.push_back(z);
                    // add tmpCoord to border list
                    deadEnds.push_back( tmpCoord );
                    // clear tmpCoord
                    tmpCoord.clear();
                }
            }
        }

        // randomly index into borders
        unsigned index = rand() % deadEnds.size();
        m_entrance = deadEnds[index];

        // remove indexed cell from borders list so entrance and exit not on same cell
        deadEnds.erase( deadEnds.begin()+index );

        // randomly index into borders
        index = rand() % deadEnds.size();
        m_exit = deadEnds[index];
        deadEnds.erase( deadEnds.begin()+index );

        // finds path from entrance to exit
        m_path = findPath(m_entrance[0],m_entrance[1],m_exit[0],m_exit[1]);
        pathLength = m_path.size();
    }

    getCell( m_entrance )->setIsEntranceOn();
    getCell( m_entrance )->setIsOccupiedOn();
    getCell( m_exit )->setIsExitOn();
    getCell( m_exit )->setIsOccupiedOn();

    std::cout<<"entrance: "<<m_entrance[0]<<", "<<m_entrance[1]<<std::endl;
    std::cout<<"exit:\t"<<m_exit[0]<<", "<<m_exit[1]<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// set up maze with corresponding doors and keys
// parameter for how many door/key pairs
void GameMaze::doDoorsAndKeys( const unsigned _num )
{
    // get number of dead ends in maze
    unsigned numDeadEnds = 0;
    for (unsigned z=0; z<m_northSouthZAxis; ++z)
    {
        for (unsigned x=0; x<m_eastWestXAxis; ++x)
        {
            if ( getCell(x,z)->getIsDeadEnd() )
            {
                ++numDeadEnds;
            }
        }
    }
    // if the user gives more doors/keys than dead ends
    // fix it
    unsigned numDoors;
    if ( _num > numDeadEnds )
    {
        numDoors = numDeadEnds;
    }
    else
    {
        numDoors = _num;
    }

    // set current cell to be the exit
    std::vector<unsigned> currentCell = m_exit;

    /**********************
      MAIN LOOP STARTS HERE
      *********************/

    // for the number of doors and keys, do stuff
    for (unsigned doorNum=0; doorNum<numDoors; ++doorNum)
    {
        std::cout<<"\t\t\t\t\tdoor: "<<doorNum+1<<"/"<<numDoors<<std::endl;
        //std::cout<<"current cell: "<<currentCell[0]<<","<<currentCell[1]<<std::endl;

        // get the path from exit to entrance
        std::string path = findPath( currentCell, m_entrance );

        // make sure the path isn't blocked
        assert( path != "X" );

        // if the path is less than 3, we can't add any more doors
        if ( path.size() < 3 )
        {
            return;
        }

        std::string pathToNextDoor;
        unsigned index;
        std::vector<unsigned> doorCell = currentCell;

        // loop until we get a door cell that isn't occupied
        while ( getCell( doorCell)->getIsOccupied() )
        {
            pathToNextDoor.clear();
            index = (unsigned)floor( ( rand()%path.size() )/( (float)numDoors+1 ) ) +1;
            //std::cout<<"size = "<<path.size()<<"\tindex = "<<index<<std::endl;

            for (unsigned i=0; i<index; ++i)
            {
                // traverse through path assigning up to index to pathToNextDoor
                pathToNextDoor += path[i];
            }
            std::cout<<"path to next door: "<<pathToNextDoor<<std::endl;
            // assign door cell to be at the end of the path
            doorCell = followPath( currentCell, pathToNextDoor );
        }

        // add door cell to a vector to contain door and key location pairs
        std::vector<std::vector<unsigned> > doorAndKey;
        doorAndKey.push_back( doorCell );
        // set door as occupied
        getCell( doorCell )->setIsOccupiedOn();

        // go to the cell after the door
        std::string nextInstr;
        nextInstr += path[index];
        currentCell = followPath( doorCell, nextInstr );

        std::vector<unsigned> keyCell;
        std::string tmpPath;
        std::string pathToKey;
        // make pathToKey a long string
        for (unsigned i=0; i<m_numCells; ++i)
        {
            pathToKey += 'X';
        }

        // cycle through all cells
        for (unsigned z=0; z<m_northSouthZAxis; ++z)
        {
            for (unsigned x=0; x<m_eastWestXAxis; ++x)
            {
                // if they ARE dead ends
                // and NOT occupied
                if ( getCell(x,z)->getIsDeadEnd() &&
                     !( getCell(x,z)->getIsOccupied() ) )
                {
                    std::vector<unsigned> tmpCell;
                    // make cell out of x,z
                    tmpCell.push_back(x);
                    tmpCell.push_back(z);
                    // find the path
                    tmpPath = findPath( currentCell, tmpCell );
                    //std::cout<<"temp path = "<<tmpPath<<std::endl;
                    // if the path is longer than 1 (this will also exclude any "X" paths)
                    // and if tmpPath is shorter than the existing path
                    if ( tmpPath.size() > 1 &&
                         tmpPath < pathToKey )
                    {
                        pathToKey = tmpPath;
                    }
                }
            }
        }

        // if after all that the path is stil blocked
        // i.e. there were no dead ends to put a key in
        if ( pathToKey[0] == 'X' )
        {
            // put the key on the way to the entrance
            pathToKey.clear();
            path = findPath( currentCell, m_entrance );
            {
                unsigned keyIndex = ( rand() % ( path.size() ) )+1;
                std::cout<<"key index = "<<keyIndex<<std::endl;
                for (unsigned i=0; i<keyIndex; ++i)
                {
                    pathToKey += path[i];
                }

                // follow the path
                keyCell = followPath( currentCell, pathToKey );
            }
            // add the keyCell to the door/key pair
            doorAndKey.push_back( keyCell );

            // return from the function early, not placing any more keys
            std::cout<<"Couldn't place all the keys - sorry!"<<std::endl;
            return;
        }

        // else if the path to a dead end was found
        else
        {
            std::cout<<"path to key "<<pathToKey<<std::endl;

            // follow the path to where we're going to put the key
            keyCell = followPath( currentCell, pathToKey );
            // add the keyCell to the door/key pair
            doorAndKey.push_back( keyCell );
            getCell( keyCell )->setIsOccupiedOn();

            // set the keyCell to be our new current cell
            currentCell = keyCell;
        }
        m_doorsKeys.push_back( doorAndKey );
    } // for number of doors loop

    std::cout<<"Placed all the doors you wanted!"<<std::endl;
}
