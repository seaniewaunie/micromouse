// Sean Graff
// 2/12/18
//
// Solver Impl. file

#include "Solver.h"

using namespace std;

Solver::Solver()
{
    m_diagnostics = new Diagnostics();

    m_graph = new Graph();

    m_loco = new Locomotion();

    m_currentPosition = STARTING_INDEX;

    m_turnCounter = 0;
    m_facing = N;

    m_startingNode = true;

    m_isSolved = false;

    m_isReadyToSprint = false;
    m_difference = 0;

    for(uint8_t i = 0; i < MAX_MAZE_SIZE; i++){
        m_nodeContainer[i].visited = false;
        m_nodeContainer[i].northIsWall = false;
        m_nodeContainer[i].eastIsWall = false;
        m_nodeContainer[i].westIsWall = false;
        m_nodeContainer[i].southIsWall = false;
        m_nodeContainer[i].deadEnd = false;
    }

}

Solver::~Solver(){
    delete m_diagnostics;
    //delete m_graph;
}

Diagnostics* Solver::getDiagnostics(){
    return m_diagnostics;
}

Locomotion* Solver::getLocomotion(){
    return m_loco;
}

bool Solver::nextNode(){
    // visually represent how long this function takes by flashing the MODE led
    m_diagnostics->getModeLED()->turnON();

    int wallCount = 0;

    bool northIsWall;
    bool eastIsWall;
    bool westIsWall;
    bool southIsWall;

    //Serial.print("m_facing before: ");
    //Serial.println(m_facing);
    //Serial.print(F("m_currentPosition before: "));
    //Serial.println(m_currentPosition);

    Node* currentNode = &m_nodeContainer[m_currentPosition];
    // a maze is solved if distance check returns true or
    if(!m_isSolved)
        m_isSolved = ( m_diagnostics->update() );

    // if the maze hasn't been solved
    if(!m_isSolved){
        //Serial.print("node visited: ");
        //Serial.println(currentNode->visited);
        // if the node hasn't been mapped before
        //if( !m_visited[m_currentPosition] ){
        if( !currentNode->visited ){
            //Serial.println("Node has not been mapped before");
            m_difference = 0;
            // if north has no wall
            if( !m_diagnostics->getNorthSensor()->isWall() ){
                // add an edge from the current node to the north node
                m_graph->addEdge( m_currentPosition, m_currentPosition+incrementNorth(), STRAIGHT_WEIGHT );
            }
            else{
                wallCount++;
                currentNode->northIsWall = true;
            }

            if( !m_diagnostics->getEastSensor()->isWall() ){
                m_graph->addEdge( m_currentPosition, m_currentPosition+incrementEast(), TURN_WEIGHT );
            }
            else{
                wallCount++;
                currentNode->eastIsWall = true;
            }

            if( !m_diagnostics->getWestSensor()->isWall() ){
                m_graph->addEdge(m_currentPosition, m_currentPosition+incrementWest(), TURN_WEIGHT);
            }
            else{
                wallCount++;
                currentNode->westIsWall = true;
                if(wallCount == 3){
                    currentNode->deadEnd = true;
                }
            }

            if(m_startingNode){
                m_startingNode = false;
                currentNode->southIsWall = true;
            }

            // save the direction the mouse was facing when this node was mapped
            currentNode->direction = m_facing;
            currentNode->visited = true;
        }
        else{
            //Serial.println("adjusting to m_facing stored from memory");


            // TODO: refine this to work perfectly
           // m_difference = currentNode->direction - m_facing;
            m_difference = currentNode->direction - m_facing;
            if(m_difference < 0) m_difference = m_difference * -1; // makeshift abs() function

            //cout << "m_difference between current facing and previous facing: " << m_difference << std::endl;

            //m_facing = currentNode->direction;
        }


        // update local variables to resemble current node
        northIsWall = currentNode->northIsWall;
        eastIsWall = currentNode->eastIsWall;
        westIsWall = currentNode->westIsWall;
        southIsWall = currentNode->southIsWall;
        //*
        Serial.println(m_currentPosition);
        Serial.print("N, E, W: ");
        Serial.print(northIsWall);
        Serial.print(",");
        Serial.print(eastIsWall);
        Serial.print(",");
        Serial.println(westIsWall);

        Serial.print("m_facing, difference: ");
        Serial.print(m_facing);
        Serial.print(",");
        Serial.print(m_difference);
        Serial.print(",");
        Serial.println(currentNode->deadEnd);
       //*/

        // at this point a decision on where to move needs to be made
        // explore any unvisited nodes first -- clockwise priority excluding south

        if( !m_nodeContainer[m_currentPosition+incrementNorth()].visited && !northIsWall){
            goForward();
            m_currentPosition += incrementNorth();

        }
        else if( !m_nodeContainer[m_currentPosition+incrementEast()].visited && !eastIsWall){
            turnRight();
            //m_currentPosition += incrementNorth();

            m_currentPosition += incrementEast();
        }
        else if( !m_nodeContainer[m_currentPosition+incrementWest()].visited && !westIsWall){
            turnLeft();
            //m_currentPosition += incrementNorth();

            m_currentPosition += incrementWest();

        }
        else{
            // all routes the mouse could take have been explored
            // at this point the mouse needs to move to nodes that are not leading to dead ends
/*            if( !m_nodeContainer[m_currentPosition+incrementNorth()].deadEnd && !northIsWall){
                goForward();
                m_currentPosition += incrementNorth();

            }
            else if( !m_nodeContainer[m_currentPosition+incrementEast()].deadEnd && !eastIsWall){
                turnRight();
                //m_currentPosition += incrementNorth();
                m_currentPosition += incrementEast();

            }
            else if( !m_nodeContainer[m_currentPosition+incrementWest()].deadEnd && !westIsWall){
                turnLeft();
                //m_currentPosition += incrementNorth();
                m_currentPosition += incrementWest();

            }
            else{
                turnAround();

                m_currentPosition += incrementSouth();
                //m_currentPosition += incrementNorth();
                currentNode->deadEnd = true;


            }
*/
            turnAround();

            m_currentPosition += incrementSouth();
            //m_currentPosition += incrementNorth();
            currentNode->deadEnd = true;


        }

        // visually represent when algorithm is 'done' working
        m_diagnostics->getModeLED()->turnOFF();
    }
    else if(!m_isReadyToSprint){
        // can celebrate and also perform DFS to find the shortest path, and visually represent sprint mode
        m_diagnostics->celebrate();
        m_diagnostics->getModeLED()->turnON();
        m_isSolved = true;

        // call the shortest path function to store directions
        m_isReadyToSprint = true;

        //m_graph->Dijkstra();
        //m_graph->storeEndPath(m_currentPosition);

        m_currentPosition = 0;
    }
    else{
        // button pressed AND shortest path is set in memory...
        // delay for 5 seconds after button press...
        for(int i = 0; i < 5; i++){
            m_diagnostics->getModeLED()->turnON();
            delay(500);
            m_diagnostics->getModeLED()->turnOFF();
            delay(500);
        }
        m_diagnostics->getModeLED()->turnON();

        // traverse the path to get to the end
        /*
        int nextIndex;
        for(int i = 0; i < m_graph->getSPSize(); i++){
            nextIndex = m_graph->getNextSPIndex();

            cout << "moving to " << nextIndex << endl;

        }
        */
    }

    //Serial.print("m_facing after: ");
    //Serial.println(m_facing);
    //Serial.print(F("m_currentPosition after: "));
    //Serial.println(m_currentPosition);
    
    if(!m_isSolved) return false;
    else return true;
}


// the increment functions add to the position relative to the mouses facing direction.
// when the mouse's north sensor is pointing(facing) east, moving the mouse "north" is actually moving
// the mouse object east one node in the graph

// these increment functions could be implemented with a modulous type circular function possible
int Solver::incrementNorth(){
//    Serial.println("Increment North called");
    switch(m_nodeContainer[m_currentPosition].direction){
        case N:
            if(m_currentPosition+VERTICAL_INCREMENT < MAX_MAZE_SIZE)
                return VERTICAL_INCREMENT;
            else
                return VERTICAL_INCREMENT-MAX_MAZE_SIZE;
            break;
        case E:
            if(m_currentPosition+HORIZONTAL_INCREMENT < MAX_MAZE_SIZE)
                return HORIZONTAL_INCREMENT;
            else
                return HORIZONTAL_INCREMENT-MAX_MAZE_SIZE;
            break;
        case S:
            if(m_currentPosition-VERTICAL_INCREMENT < 0)
                return MAX_MAZE_SIZE-VERTICAL_INCREMENT;
            else
                return -VERTICAL_INCREMENT;
            break;
        case W:
            if(m_currentPosition-HORIZONTAL_INCREMENT >= 0)
                return -HORIZONTAL_INCREMENT;
            else
                return MAX_MAZE_SIZE-HORIZONTAL_INCREMENT;
            break;
    }
}

int Solver::incrementEast(){
//    Serial.println("Increment East called");
    switch(m_nodeContainer[m_currentPosition].direction){
        case N:
            if(m_currentPosition+HORIZONTAL_INCREMENT < MAX_MAZE_SIZE)
                return HORIZONTAL_INCREMENT;
            else
                return HORIZONTAL_INCREMENT-MAX_MAZE_SIZE;
            break;
        case E:
            if(m_currentPosition-VERTICAL_INCREMENT < 0)
                return MAX_MAZE_SIZE-VERTICAL_INCREMENT;
            else
                return -VERTICAL_INCREMENT;
            break;
        case S:
            if(m_currentPosition-HORIZONTAL_INCREMENT >= 0)
                return -HORIZONTAL_INCREMENT;
            else
                return MAX_MAZE_SIZE-HORIZONTAL_INCREMENT;
            break;
        case W:
            if(m_currentPosition+VERTICAL_INCREMENT < MAX_MAZE_SIZE)
                return VERTICAL_INCREMENT;
            else
                return VERTICAL_INCREMENT-MAX_MAZE_SIZE;
            break;
    }
}

int Solver::incrementSouth(){
//    Serial.println("Increment South called");
    switch(m_nodeContainer[m_currentPosition].direction){
        case N:
            if(m_currentPosition-VERTICAL_INCREMENT < 0)
                return MAX_MAZE_SIZE-VERTICAL_INCREMENT;
            else
                return -VERTICAL_INCREMENT;
            break;
        case E:
            if(m_currentPosition-HORIZONTAL_INCREMENT >= 0)
                return -HORIZONTAL_INCREMENT;
            else
                return MAX_MAZE_SIZE-HORIZONTAL_INCREMENT;
            break;
        case S:
            if(m_currentPosition+VERTICAL_INCREMENT < MAX_MAZE_SIZE)
                return VERTICAL_INCREMENT;
            else
                return VERTICAL_INCREMENT-MAX_MAZE_SIZE;
            break;
        case W:
            if(m_currentPosition+HORIZONTAL_INCREMENT < MAX_MAZE_SIZE)
                return HORIZONTAL_INCREMENT;
            else
                return HORIZONTAL_INCREMENT-MAX_MAZE_SIZE;
            break;
    }
}

int Solver::incrementWest(){
    //Serial.println("Increment West called");
    switch(m_nodeContainer[m_currentPosition].direction){
        case N:
            if(m_currentPosition-HORIZONTAL_INCREMENT >= 0)
                return -HORIZONTAL_INCREMENT;
            else
                return MAX_MAZE_SIZE-HORIZONTAL_INCREMENT;
            break;
        case E:
            if(m_currentPosition+VERTICAL_INCREMENT < MAX_MAZE_SIZE)
                return VERTICAL_INCREMENT;
            else
                return VERTICAL_INCREMENT-MAX_MAZE_SIZE;
            break;
        case S:
            if(m_currentPosition+HORIZONTAL_INCREMENT < MAX_MAZE_SIZE)
                return HORIZONTAL_INCREMENT;
            else
                return HORIZONTAL_INCREMENT-MAX_MAZE_SIZE;
            break;
        case W:
            if(m_currentPosition-VERTICAL_INCREMENT < 0)
                return MAX_MAZE_SIZE-VERTICAL_INCREMENT;
            else
                return -VERTICAL_INCREMENT;
            break;
    }
}

// TODO: these functions need to be verified
void Solver::goForward(){
    //Serial.println("go forward called");

    if(m_difference == 0){
        // do nothing we are good
    }
    else if(m_difference == 2){
        m_loco->makeUTurn();
        m_facing = static_cast<DIRECTION>((m_facing + 2)%4);
    }
    else if(m_difference == 1){
        if(m_nodeContainer[m_currentPosition].direction < m_facing){
            m_loco->turnLeft();
            m_facing = static_cast<DIRECTION>((m_facing + 3)%4);
       }
        else{
            m_loco->turnRight();
            m_facing = static_cast<DIRECTION>((m_facing + 1)%4);
        }
    }
    else if(m_difference == 3){
        if(m_nodeContainer[m_currentPosition].direction < m_facing){
            m_loco->turnRight();
            m_facing = static_cast<DIRECTION>((m_facing + 1)%4);
        }
        else{
            m_loco->turnLeft();
            m_facing = static_cast<DIRECTION>((m_facing + 3)%4);

        }
    }
    else{
        Serial.println("err GF");
    }
   // at the end of this function, go forward is executed
    m_loco->goForward();
}

void Solver::turnRight(){
    //Serial.println("Turn right called");

    if(m_difference == 0){
        m_loco->turnRight();
        m_facing = static_cast<DIRECTION>((m_facing + 1)%4);
    }
    else if(m_difference == 2){
        m_loco->turnLeft();
        m_facing = static_cast<DIRECTION>((m_facing + 3)%4);
    }
    else if(m_difference == 1){
        if(m_nodeContainer[m_currentPosition].direction < m_facing){
            // do nothing
       }
        else{
            m_loco->makeUTurn();
            m_facing = static_cast<DIRECTION>((m_facing + 2)%4);
        }
    }
    else if(m_difference == 3){
        if(m_nodeContainer[m_currentPosition].direction < m_facing){
            m_loco->makeUTurn();
            m_facing = static_cast<DIRECTION>((m_facing + 2)%4);
        }
        else{
            // do nothing
        }
    }
    else{
        Serial.println("err TR");
    }
    //m_facing = static_cast<DIRECTION>((m_facing + 1)%4);

    // move to the next node
    m_loco->goForward();
}

void Solver::turnLeft(){
    //Serial.println("turn left called");

    if(m_difference == 0){
        m_loco->turnLeft();
        m_facing = static_cast<DIRECTION>((m_facing + 3)%4);
    }
    else if(m_difference == 2){
        m_loco->turnRight();
        m_facing = static_cast<DIRECTION>((m_facing + 1)%4);
    }
    else if(m_difference == 1){
        if(m_nodeContainer[m_currentPosition].direction < m_facing){
            m_loco->makeUTurn();
            m_facing = static_cast<DIRECTION>((m_facing+2)%4);
       }
        else{
            // do nothing
        }
    }
    else if(m_difference == 3){
        if(m_nodeContainer[m_currentPosition].direction > m_facing){
            m_loco->makeUTurn();
            m_facing = static_cast<DIRECTION>((m_facing + 2)%4);
        }
        else{
            // do nothing
        }
    }
    else{
        Serial.println("err TL");
    }
     m_loco->goForward();

    //Serial.println("Turning left");
}

void Solver::turnAround(){
    //Serial.println("Turn around called");

    if(m_difference == 0){
        m_loco->makeUTurn();
        m_facing = static_cast<DIRECTION>((m_facing + 2)%4);
    }
    else if(m_difference == 2){
        // do nothing
    }
    else if(m_difference == 1){
        if(m_nodeContainer[m_currentPosition].direction < m_facing){
            m_loco->turnRight();
            m_facing = static_cast<DIRECTION>((m_facing+1)%4);
       }
        else{
            m_loco->turnLeft();
            m_facing = static_cast<DIRECTION>((m_facing+3)%4);
        }
    }
    else if(m_difference == 3){
        if(m_nodeContainer[m_currentPosition].direction > m_facing){
            m_loco->turnRight();
            m_facing = static_cast<DIRECTION>((m_facing+1)%4);
       }
        else{
            m_loco->turnLeft();
            m_facing = static_cast<DIRECTION>((m_facing+3)%4);
        }
    }
    else{
        Serial.println("err TA");
    }
    m_loco->goForward();

    //m_facing = static_cast<DIRECTION>((m_facing + 2)%4);
}
