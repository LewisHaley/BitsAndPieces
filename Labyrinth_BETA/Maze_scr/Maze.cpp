#include "Maze/Maze.h"

//----------------------------------------------------------------------------------------------------------------------
// default contructor
Maze::Maze()
{
    //std::cout<<"default maze constructed"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// user defined constructor
Maze::Maze(
        const unsigned _x,
        const unsigned _z
        )
{
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
    //std::cout<<"UD maze constructed"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// destructor
Maze::~Maze()
{
    // free memory used by cells
    for (unsigned z=0; z<m_northSouthZAxis; ++z)
    {
        for (unsigned x=0; x<m_eastWestXAxis; ++x)
        {
            delete m_maze[z][x];
        }
    }
    //std::cout<<"Maze destroyed"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// sets up maze with borders on appropriate cells
// removes walls where there are borders
void Maze::setUp()
{
    // NORTHERN BORDER
    for (unsigned cell=0; cell<m_eastWestXAxis; ++cell)
    {
        m_maze[m_northSouthZAxis-1][cell]->setHasNBOn();
    }
    // EASTERN BORDER
    for (unsigned cell=0; cell<m_northSouthZAxis; ++cell)
    {
        m_maze[cell][0]->setHasEBOn();
    }
    // SOUTHERN BORDER
    for (unsigned cell=0; cell<m_eastWestXAxis; ++cell)
    {
        m_maze[0][cell]->setHasSBOn();
    }
    // WESTERN BORDER
    for (unsigned cell=0; cell<m_northSouthZAxis; ++cell)
    {
        m_maze[cell][m_eastWestXAxis-1]->setHasWBOn();
    }
}

//----------------------------------------------------------------------------------------------------------------------
// creates the maze paths using depth first search algorithm
void Maze::makeMazeDFS()
{
    // choose random cell to start from
    unsigned randStartX = rand() % m_eastWestXAxis;
    unsigned randStartZ = rand() % m_northSouthZAxis;
    // current cell is (x,z)
    std::vector<unsigned> currentCell;
    currentCell.push_back( randStartX );
    currentCell.push_back( randStartZ );
    //std::cout<<"random start cell ("<<randStartX<<", "<<randStartZ<<")"<<std::endl;

    // create empty contain for list of visited cells
    std::vector<std::vector<unsigned> > cellStack;

    unsigned cellsVisited = 1;

    // while there are still cells which haven't been visited
    while ( cellsVisited < m_numCells )
    {
        // make empty vectors for storing possible neighbour cells
        std::vector<unsigned> N,E,S,W;
        // make an empty vector for storing neighbour cells
        std::vector<std::vector<unsigned> > neighbours;
        // check whether the NESW cells of the current cell
        // will fall outside of range
        // NORTH
        if ( currentCell[1]+1 < m_northSouthZAxis )
        {
            N.push_back( currentCell[0] );
            N.push_back( currentCell[1]+1 );
            // if cell has all walls intact/has not been visited before
            if ( m_maze[N[1]][N[0]]->getNW() &&
                 m_maze[N[1]][N[0]]->getEW() &&
                 m_maze[N[1]][N[0]]->getSW() &&
                 m_maze[N[1]][N[0]]->getWW()) // i.e. if all these return TRUE
            {
                // add it to neighbours
                neighbours.push_back( N );
            }
        }
        // EAST
        if ( currentCell[0]-1 < m_eastWestXAxis )
        {
            E.push_back( currentCell[0]-1 );
            E.push_back( currentCell[1] );
            if ( m_maze[E[1]][E[0]]->getNW() &&
                 m_maze[E[1]][E[0]]->getEW() &&
                 m_maze[E[1]][E[0]]->getSW() &&
                 m_maze[E[1]][E[0]]->getWW()) // i.e. if all these return TRUE
            {
                // add it to neighbours
                neighbours.push_back( E );
            }
        }
        // SOUTH
        if ( currentCell[1]-1 < m_northSouthZAxis )
        {
            S.push_back( currentCell[0] );
            S.push_back( currentCell[1]-1 );
            if ( m_maze[S[1]][S[0]]->getNW() &&
                 m_maze[S[1]][S[0]]->getEW() &&
                 m_maze[S[1]][S[0]]->getSW() &&
                 m_maze[S[1]][S[0]]->getWW()) // i.e. if all these return TRUE
            {
                // add it to neighbours
                neighbours.push_back( S );
            }
        }
        // WEST
        if ( currentCell[0]+1 < m_eastWestXAxis )
        {
            W.push_back( currentCell[0]+1 );
            W.push_back( currentCell[1] );
            if ( m_maze[W[1]][W[0]]->getNW() &&
                 m_maze[W[1]][W[0]]->getEW() &&
                 m_maze[W[1]][W[0]]->getSW() &&
                 m_maze[W[1]][W[0]]->getWW()) // i.e. if all these return TRUE
            {
                // add it to neighbours
                neighbours.push_back( W );
            }
        }
        /*
        std::cout<<"neighbours"<<std::endl;
        for (unsigned i=0; i<neighbours.size(); ++i)
        {
            std::cout<<"("<<neighbours[i][0]<<", "<<neighbours[i][1]<<")"<<std::endl;
        }*/

        // if there are neighbouring cells
        if ( neighbours.size() ) // if size isn't 0, it's true
        {
            std::vector<unsigned> moveTo;
            // randomly index into neighbours list
            unsigned index = rand() % neighbours.size();
            moveTo.push_back( neighbours[index][0] );
            moveTo.push_back( neighbours[index][1] );
            /*
            std::cout<<"moving to cell ";
            std::cout<<"("<<moveTo[0]<<", "<<moveTo[1]<<")"<<std::endl;*/

            // add current cell to list of visited cells
            cellStack.push_back( currentCell );

            // if moving north
            if ( moveTo == N )
            {
                // set current cell to not have a north wall
                m_maze[currentCell[1]][currentCell[0]]->setHasNWOff();
                // set the cell we're moving to to have no south wall
                m_maze[moveTo[1]][moveTo[0]]->setHasSWOff();
                // set the cell we're moving to to be part of the maze
                m_maze[moveTo[1]][moveTo[0]]->setIsPathOn();
                // make cell we've moved to the current cell
                currentCell = moveTo;
                //std::cout<<"Moved north!"<<std::endl;
            }
            // if moving east
            else if ( moveTo == E )
            {
                // set current cell to not have a east wall
                m_maze[currentCell[1]][currentCell[0]]->setHasEWOff();
                // set the cell we're moving to to have no west wall
                m_maze[moveTo[1]][moveTo[0]]->setHasWWOff();
                // set the cell we're moving to to be part of the maze
                m_maze[moveTo[1]][moveTo[0]]->setIsPathOn();
                // make cell we've moved to the current cell
                currentCell = moveTo;
                //std::cout<<"Moved east!"<<std::endl;
            }
            // if moving south
            else if ( moveTo == S )
            {
                // set current cell to not have a south wall
                m_maze[currentCell[1]][currentCell[0]]->setHasSWOff();
                // set the cell we're moving to to have no north wall
                m_maze[moveTo[1]][moveTo[0]]->setHasNWOff();
                // set the cell we're moving to to be part of the maze
                m_maze[moveTo[1]][moveTo[0]]->setIsPathOn();
                // make cell we've moved to the current cell
                currentCell = moveTo;
                //std::cout<<"Moved south!"<<std::endl;
            }
            // if moving west
            else if ( moveTo == W )
            {
                // set current cell to not have a west wall
                m_maze[currentCell[1]][currentCell[0]]->setHasWWOff();
                // set the cell we're moving to to have no east wall
                m_maze[moveTo[1]][moveTo[0]]->setHasEWOff();
                // set the cell we're moving to to be part of the maze
                m_maze[moveTo[1]][moveTo[0]]->setIsPathOn();
                // make cell we've moved to the current cell
                currentCell = moveTo;
                //std::cout<<"Moved west!"<<std::endl;
            }
            cellsVisited += 1;
            // calculate percent of maze completed
            float tmp = ( (float)cellsVisited / (float)m_numCells )*100.0f;
            m_percentComplete = (unsigned)tmp;
            std::cout<<"Loading: "<<m_percentComplete<<"%\r";
        }

        // if there are no cells to move into/ neighbours.size() = 0
        else
        {
            // set cell as not maze path
            m_maze[currentCell[1]][currentCell[0]]->setIsPathOff();
            // go back to the last visited cell, make it the current cell
            currentCell = cellStack.back();
            // remove it from the stack
            cellStack.pop_back();
            //std::cout<<"went back to: "<<currentCell[0]<<", "<<currentCell[1]<<std::endl;
        }
    }
    std::cout<<"DFS maze created"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// hunt and kill algorithm for forming maze path
void Maze::makeMazeHAK()
{
    // choose random cell to start from
    unsigned randStartX = rand() % m_eastWestXAxis;
    unsigned randStartZ = rand() % m_northSouthZAxis;
    // current cell is (x,z)
    std::vector<unsigned> currentCell;
    currentCell.push_back( randStartX );
    currentCell.push_back( randStartZ );
    // set current cell to be part of maze
    m_maze[currentCell[1]][currentCell[0]]->setIsMazeOn();
    //std::cout<<"random start cell ("<<randStartX<<", "<<randStartZ<<")"<<std::endl;

    // create empty contain for list of visited cells
    std::vector<std::vector<unsigned> > cellStack;

    unsigned cellsVisited = 1;

    // while there are still cells which haven't been visited
    while ( cellsVisited < m_numCells )
    {
        // make empty vectors for storing possible neighbour cells
        std::vector<unsigned> N,E,S,W;
        // make an empty vector for storing neighbour cells
        std::vector<std::vector<unsigned> > neighbours;
        // check whether the NESW cells of the current cell
        // will fall outside of range
        // NORTH
        if ( currentCell[1]+1 < m_northSouthZAxis )
        {
            N.push_back( currentCell[0] );
            N.push_back( currentCell[1]+1 );
            // if cell has all walls intact/has not been visited before
            if ( m_maze[N[1]][N[0]]->getNW() &&
                 m_maze[N[1]][N[0]]->getEW() &&
                 m_maze[N[1]][N[0]]->getSW() &&
                 m_maze[N[1]][N[0]]->getWW()) // i.e. if all these return TRUE
            {
                // add it to neighbours
                neighbours.push_back( N );
                // mark cell as fronier
                m_maze[N[1]][N[0]]->setIsFrontierOn();
            }
        }
        // EAST
        if ( currentCell[0]-1 < m_eastWestXAxis )
        {
            E.push_back( currentCell[0]-1 );
            E.push_back( currentCell[1] );
            if ( m_maze[E[1]][E[0]]->getNW() &&
                 m_maze[E[1]][E[0]]->getEW() &&
                 m_maze[E[1]][E[0]]->getSW() &&
                 m_maze[E[1]][E[0]]->getWW()) // i.e. if all these return TRUE
            {
                // add it to neighbours
                neighbours.push_back( E );
                // mark cell as fronier
                m_maze[E[1]][E[0]]->setIsFrontierOn();
            }
        }
        // SOUTH
        if ( currentCell[1]-1 < m_northSouthZAxis )
        {
            S.push_back( currentCell[0] );
            S.push_back( currentCell[1]-1 );
            if ( m_maze[S[1]][S[0]]->getNW() &&
                 m_maze[S[1]][S[0]]->getEW() &&
                 m_maze[S[1]][S[0]]->getSW() &&
                 m_maze[S[1]][S[0]]->getWW()) // i.e. if all these return TRUE
            {
                // add it to neighbours
                neighbours.push_back( S );
                // mark cell as fronier
                m_maze[S[1]][S[0]]->setIsFrontierOn();
            }
        }
        // WEST
        if ( currentCell[0]+1 < m_eastWestXAxis )
        {
            W.push_back( currentCell[0]+1 );
            W.push_back( currentCell[1] );
            if ( m_maze[W[1]][W[0]]->getNW() &&
                 m_maze[W[1]][W[0]]->getEW() &&
                 m_maze[W[1]][W[0]]->getSW() &&
                 m_maze[W[1]][W[0]]->getWW()) // i.e. if all these return TRUE
            {
                // add it to neighbours
                neighbours.push_back( W );
                // mark cell as fronier
                m_maze[W[1]][W[0]]->setIsFrontierOn();
            }
        }

        /*
        std::cout<<"neighbours"<<std::endl;
        for (unsigned i=0; i<neighbours.size(); ++i)
        {
            std::cout<<"("<<neighbours[i][0]<<", "<<neighbours[i][1]<<")"<<std::endl;
        }*/

        // if there are neighbouring cells
        if ( neighbours.size() ) // if size isn't 0, it's true
        {
            std::vector<unsigned> moveTo;
            // randomly index into neighbours list
            unsigned index = rand() % neighbours.size();
            moveTo.push_back( neighbours[index][0] );
            moveTo.push_back( neighbours[index][1] );

            /*
            std::cout<<"moving to cell ";
            std::cout<<"("<<moveTo[0]<<", "<<moveTo[1]<<")"<<std::endl;*/

            // add current cell to list of visited cells
            cellStack.push_back( currentCell );

            // if moving north
            if ( moveTo == N )
            {
                // set current cell to not have a north wall
                m_maze[currentCell[1]][currentCell[0]]->setHasNWOff();
                // set the cell we're moving to to have no south wall
                m_maze[moveTo[1]][moveTo[0]]->setHasSWOff();
                // make cell we've moved to the current cell
                currentCell = moveTo;
                //std::cout<<"Moved north!"<<std::endl;
                // mark cell as part of the maze
                m_maze[currentCell[1]][currentCell[0]]->setIsMazeOn();
                // mark cell as NOT frontier
                m_maze[currentCell[1]][currentCell[0]]->setIsFrontierOff();
            }
            // if moving east
            else if ( moveTo == E )
            {
                // set current cell to not have a east wall
                m_maze[currentCell[1]][currentCell[0]]->setHasEWOff();
                // set the cell we're moving to to have no west wall
                m_maze[moveTo[1]][moveTo[0]]->setHasWWOff();
                // make cell we've moved to the current cell
                currentCell = moveTo;
                //std::cout<<"Moved east!"<<std::endl;
                // mark cell as part of the maze
                m_maze[currentCell[1]][currentCell[0]]->setIsMazeOn();
                // mark cell as NOT frontier
                m_maze[currentCell[1]][currentCell[0]]->setIsFrontierOff();
            }
            // if moving south
            else if ( moveTo == S )
            {
                // set current cell to not have a south wall
                m_maze[currentCell[1]][currentCell[0]]->setHasSWOff();
                // set the cell we're moving to to have no north wall
                m_maze[moveTo[1]][moveTo[0]]->setHasNWOff();
                // make cell we've moved to the current cell
                currentCell = moveTo;
                //std::cout<<"Moved south!"<<std::endl;
                // mark cell as part of the maze
                m_maze[currentCell[1]][currentCell[0]]->setIsMazeOn();
                // mark cell as NOT frontier
                m_maze[currentCell[1]][currentCell[0]]->setIsFrontierOff();
            }
            // if moving west
            else if ( moveTo == W )
            {
                // set current cell to not have a west wall
                m_maze[currentCell[1]][currentCell[0]]->setHasWWOff();
                // set the cell we're moving to to have no east wall
                m_maze[moveTo[1]][moveTo[0]]->setHasEWOff();
                // make cell we've moved to the current cell
                currentCell = moveTo;
                //std::cout<<"Moved west!"<<std::endl;
                // mark cell as part of the maze
                m_maze[currentCell[1]][currentCell[0]]->setIsMazeOn();
                // mark cell as NOT frontier
                m_maze[currentCell[1]][currentCell[0]]->setIsFrontierOff();
            }
            // set all remaining neighbours to be frontier cells

            cellsVisited += 1;
            // calculate percent of maze completed
            float tmp = ( (float)cellsVisited / (float)m_numCells )*100.0f;
            m_percentComplete = (unsigned)tmp;
            std::cout<<"Loading: "<<m_percentComplete<<"%\r";
        }
        // if there are no cells to move into ( neighbours.size() = 0 )
        else
        {
            // set cell as dead end
            m_maze[currentCell[1]][currentCell[0]]->setIsPathOff();

            //std::cout<<"entered hunting mode"<<std::endl;
            // cycle through all cells in maze
            // make list of frontier cells
            std::vector<std::vector<unsigned> > frontiers;
            for (unsigned z=0; z<m_northSouthZAxis; ++z)
            {
                for (unsigned x=0; x<m_eastWestXAxis; ++x)
                {
                    if ( m_maze[z][x]->getIsFrontier() )
                    {
                        std::vector<unsigned> tmpCell;
                        tmpCell.push_back( x );
                        tmpCell.push_back( z );
                        frontiers.push_back( tmpCell );
                        //std::cout<<"found frontier ("<<x<<", "<<z<<")"<<std::endl;
                    }
                }
            }
            // randomly choose frontier cell
            unsigned index = rand() % frontiers.size();
            currentCell = frontiers[index];
            // set it to be part of the maze, and no longer frontier
            m_maze[currentCell[1]][currentCell[0]]->setIsMazeOn();
            m_maze[currentCell[1]][currentCell[0]]->setIsFrontierOff();
            //std::cout<<"jumped to ("<<currentCell[0]<<", "<<currentCell[1]<<") ";

            neighbours.clear();
            N.clear();
            E.clear();
            S.clear();
            W.clear();

            // find the neighbours to the new current cell
            // NORTH
            if ( currentCell[1]+1 < m_northSouthZAxis )
            {
                N.push_back( currentCell[0] );
                N.push_back( currentCell[1]+1 );
                // if cell is part of the maze
                if ( m_maze[N[1]][N[0]]->getIsMaze() )
                {
                    // add it to neighbours
                    neighbours.push_back( N );
                }
            }
            // EAST
            if ( currentCell[0]-1 < m_eastWestXAxis )
            {
                E.push_back( currentCell[0]-1 );
                E.push_back( currentCell[1] );
                // if cell is part of the maze
                if ( m_maze[E[1]][E[0]]->getIsMaze() )
                {
                    // add it to neighbours
                    neighbours.push_back( E );
                }
            }
            // SOUTH
            if ( currentCell[1]-1 < m_northSouthZAxis )
            {
                S.push_back( currentCell[0] );
                S.push_back( currentCell[1]-1 );
                // if cell is part of the maze
                if ( m_maze[S[1]][S[0]]->getIsMaze() )
                {
                    // add it to neighbours
                    neighbours.push_back( S );
                }
            }
            // WEST
            if ( currentCell[0]+1 < m_eastWestXAxis )
            {
                W.push_back( currentCell[0]+1 );
                W.push_back( currentCell[1] );
                // if cell is part of the maze
                if ( m_maze[W[1]][W[0]]->getIsMaze() )
                {
                    // add it to neighbours
                    neighbours.push_back( W );
                }
            }

            // choose a random cell from neighbours
            index = rand() % neighbours.size();
            std::vector<unsigned> neighbour = neighbours[index];
            // if the neighbour was to the north
            if ( neighbour == N )
            {
                // set current cell north wall off
                m_maze[currentCell[1]][currentCell[0]]->setHasNWOff();
                // set neighbour cell south wall off
                m_maze[neighbour[1]][neighbour[0]]->setHasSWOff();
            }
            // if the neighbour was to the east
            else if ( neighbour == E )
            {
                // set current cell east wall off
                m_maze[currentCell[1]][currentCell[0]]->setHasEWOff();
                // set neighbour cell west wall off
                m_maze[neighbour[1]][neighbour[0]]->setHasWWOff();
            }
            // if the neighbour was to the south
            else if ( neighbour == S )
            {
                // set current cell south wall off
                m_maze[currentCell[1]][currentCell[0]]->setHasSWOff();
                // set neighbour cell north wall off
                m_maze[neighbour[1]][neighbour[0]]->setHasNWOff();
            }
            // if the neighbour was to the north
            else if ( neighbour == W )
            {
                // set current cell west wall off
                m_maze[currentCell[1]][currentCell[0]]->setHasWWOff();
                // set neighbour cell east wall off
                m_maze[neighbour[1]][neighbour[0]]->setHasEWOff();
            }

            // set all remaining neighbours who aren't already part of the maze
            for (unsigned i=0; i<neighbours.size(); ++i)
            {
                if( !( m_maze[neighbours[i][1]][neighbours[i][0]]->getIsMaze() ) )
                {
                    m_maze[neighbours[i][1]][neighbours[i][0]]->setIsFrontierOn();
                }
            }
            cellsVisited += 1;
            // calculate percent of maze completed
            float tmp = ( (float)cellsVisited / (float)m_numCells )*100.0f;
            m_percentComplete = (unsigned)tmp;
            std::cout<<"Loading: "<<m_percentComplete<<"%\r";
        }
    }
    std::cout<<"\nHAK maze created"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// returns pointer to cell in maze
Cell* Maze::getCell(
        const unsigned _x,
        const unsigned _z
        )
{
    Cell* o_cellptr;
    o_cellptr = m_maze[_z][_x];
    //std::cout<<o_cellptr<<std::endl;
    return o_cellptr;
}

//----------------------------------------------------------------------------------------------------------------------
// return pointer to cell in the maze
// arguments _coord an unsigned vector representing a coordinate in the maze
Cell* Maze::getCell( const std::vector<unsigned> _coord )
{
    assert( _coord.size() == 2 );
    Cell* o_cellptr;
    o_cellptr = m_maze[_coord[1]][_coord[0]];
    //std::cout<<o_cellptr<<std::endl;
    return o_cellptr;
}
//----------------------------------------------------------------------------------------------------------------------
// resets maze as if new
void Maze::reset()
{
    // sets all cells back to original state as if created again
    for (unsigned z=0; z>m_northSouthZAxis; ++z)
    {
        for (unsigned x=0; x>m_eastWestXAxis; ++x)
        {
            // reset cell
            m_maze[z][x]->reset();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
