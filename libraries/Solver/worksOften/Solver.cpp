// Sean Graff
// 2/12/18
//
// Solver Impl. file

#include "Solver.h"

using namespace std;

Solver::Solver(){
    //empty
}

Solver::Solver( const int northSensorPin, const int eastSensorPin, \
                const int westSensorPin, const int northLEDPin, \
                const int eastLEDPin, const int westLEDPin, \
                const int southLEDPin, const int modeLEDPin)
{
    m_diagnostics = new Diagnostics(northSensorPin, eastSensorPin, \
                                    westSensorPin, northLEDPin, \
                                    eastLEDPin, westLEDPin, \
                                    southLEDPin, modeLEDPin);
    
    m_graph = new Graph();
    
    //m_loco = new Locomotion();

    m_currentPosition = STARTING_INDEX;

    m_turnCounter = 0;
    m_facing = N;

    m_startingNode = true;

    m_isSolved = false;    

    m_isReadyToSprint = false;

}

Solver::~Solver(){
    delete m_diagnostics;
    //delete m_graph;
}

Diagnostics* Solver::getDiagnostics(){
    return m_diagnostics;
}

void Solver::nextNode(){
    // visually represent how long this function takes by flashing the MODE led
    m_diagnostics->getModeLED()->turnON();
 
    int wallCount = 0;

    bool northIsWall;
    bool eastIsWall;
    bool westIsWall;
    bool southIsWall;

    //Serial.print("m_facing before: ");
    //Serial.println(m_facing);
    Serial.print(F("m_currentPosition before: "));
    Serial.println(m_currentPosition);
    
    Node* currentNode = &m_nodeContainer[m_currentPosition];
    // a maze is solved if distance check returns true or 
    if(!m_isSolved)
        m_isSolved = ( m_diagnostics->update() );

    // TODO: I thought of a really awesome way to upgrade this algorithm, I'll try doing that soon

    // if the maze hasn't been solved
    if(!m_isSolved){
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
            m_difference = currentNode->direction - m_facing;
            if(m_difference < -1) m_difference = m_difference * -1; // makeshift abs() function

            cout << "m_difference between current facing and previous facing: " << m_difference << std::endl;
            
            m_facing = currentNode->direction;
        }

        
        // update local variables to resemble current node
        northIsWall = currentNode->northIsWall;
        eastIsWall = currentNode->eastIsWall;
        westIsWall = currentNode->westIsWall;
        southIsWall = currentNode->southIsWall;

        // at this point a decision on where to move needs to be made
        // explore any unvisited nodes first -- clockwise priority excluding south

        if( !m_nodeContainer[m_currentPosition+incrementNorth()].visited && !northIsWall){
            m_currentPosition += incrementNorth();
            
            goForward();
        }
        else if( !m_nodeContainer[m_currentPosition+incrementEast()].visited && !eastIsWall){
            m_currentPosition += incrementEast();
           
            turnRight();
        }
        else if( !m_nodeContainer[m_currentPosition+incrementWest()].visited && !westIsWall){
            m_currentPosition += incrementWest();
           
            turnLeft();
        }
        else{
            // all routes the mouse could take have been explored
            // at this point the mouse needs to move to nodes that are not leading to dead ends
            if( !m_nodeContainer[m_currentPosition+incrementNorth()].deadEnd && !northIsWall){
                m_currentPosition += incrementNorth();
               
                goForward();
            }
            else if( !m_nodeContainer[m_currentPosition+incrementEast()].deadEnd && !eastIsWall){
                m_currentPosition += incrementEast();
                
                turnRight();
            }
            else if( !m_nodeContainer[m_currentPosition+incrementWest()].deadEnd && !westIsWall){
                m_currentPosition += incrementWest();
                              
                turnLeft();
            }
            else{
                
                currentNode->deadEnd = true;

                m_currentPosition += incrementSouth();
               
                turnAround();
            
            }
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

        m_graph->Dijkstra();
        m_graph->storeEndPath(m_currentPosition);

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
        int nextIndex;
        for(int i = 0; i < m_graph->getSPSize(); i++){
            nextIndex = m_graph->getNextSPIndex();
            
            cout << "moving to " << nextIndex << endl;

        }
            
    }

    //Serial.print("m_facing after: ");
    //Serial.println(m_facing);
    Serial.print(F("m_currentPosition after: "));
    Serial.println(m_currentPosition);

    
}


// the increment functions add to the position relative to the mouses facing direction.
// when the mouse's north sensor is pointing(facing) east, moving the mouse "north" is actually moving
// the mouse object east one node in the graph

// these increment functions could be implemented with a modulous type circular function possible
int Solver::incrementNorth(){
//    Serial.println("Increment North called");
    switch(m_facing){
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
    switch(m_facing){
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
    switch(m_facing){
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
    switch(m_facing){
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
    if(m_difference == 2){
        m_diagnostics->getSouthLED()->flashLED();
        m_diagnostics->getSouthLED()->flashLED();
        // at this point, the locomotion objects "turn around" is called
    }
    else if(m_difference == 1){
        m_diagnostics->getEastLED()->flashLED();
        m_diagnostics->getEastLED()->flashLED();
    }
    else if(m_difference == -1){
        m_diagnostics->getWestLED()->flashLED();
        m_diagnostics->getWestLED()->flashLED();
    }
    else{
        m_diagnostics->getNorthLED()->flashLED();
        m_diagnostics->getNorthLED()->flashLED();
    }
    // at the end of this function, go forward is executed
    //m_loco->goForward();
}

void Solver::turnRight(){
    //Serial.println("Turning right");
    if(m_difference == 2){
        m_diagnostics->getWestLED()->flashLED();
        m_diagnostics->getWestLED()->flashLED();
        
        //m_loco->turnLeft();
    }
    else if(m_difference == 1){
        m_diagnostics->getNorthLED()->flashLED();
        m_diagnostics->getNorthLED()->flashLED();

        // nothing to do with orientation
    }
    else if(m_difference == -1){
        m_diagnostics->getSouthLED()->flashLED();
        m_diagnostics->getSouthLED()->flashLED();

        //m_loco->turnAround();
    }
    else{ 
        m_diagnostics->getEastLED()->flashLED();
        m_diagnostics->getEastLED()->flashLED();

        //m_loco->turnRight();
    }

    m_facing = static_cast<DIRECTION>((m_facing + 1)%4);
    
    // move to the next node
    //m_loco->goForward();
}

void Solver::turnLeft(){
    if(m_difference == 2){
        m_diagnostics->getEastLED()->flashLED();
        m_diagnostics->getEastLED()->flashLED();
    }
    else if(m_difference == 1){
        m_diagnostics->getNorthLED()->flashLED();
        m_diagnostics->getNorthLED()->flashLED();
    }
    else if(m_difference == -1){
        m_diagnostics->getSouthLED()->flashLED();
        m_diagnostics->getSouthLED()->flashLED();
    }
    else{ 
        m_diagnostics->getWestLED()->flashLED();
        m_diagnostics->getWestLED()->flashLED();
    }

    //Serial.println("Turning left");
    m_facing = static_cast<DIRECTION>((m_facing + 3)%4);
}

void Solver::turnAround(){
    //Serial.println("Turning around");
    if(m_difference == 2){
        m_diagnostics->getNorthLED()->flashLED();
        m_diagnostics->getNorthLED()->flashLED();
    }
    else if(m_difference == -1){
        m_diagnostics->getEastLED()->flashLED();
        m_diagnostics->getEastLED()->flashLED();
    }
    else if(m_difference == 1){
        m_diagnostics->getWestLED()->flashLED();
        m_diagnostics->getWestLED()->flashLED();
    }
    else{ 
        m_diagnostics->getSouthLED()->flashLED();
        m_diagnostics->getSouthLED()->flashLED();
    }

    m_facing = static_cast<DIRECTION>((m_facing + 2)%4);
}
