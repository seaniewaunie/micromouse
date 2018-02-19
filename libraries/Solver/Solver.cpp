// Sean Graff
// 2/12/18
//
// Solver Impl. file

#include "Solver.h"

using namespace std;

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

    m_currentPosition = STARTING_INDEX;

    for(int i = 0; i < MAX_MAZE_SIZE; i++){
        m_visited[i] = false;
        m_deadEndTracker[i] = false;
        m_eastIsWallTracker[i] = false;
        m_westIsWallTracker[i] = false;
        m_northIsWallTracker[i] = false;
        m_southIsWallTracker[i] = false;
    }

    m_turnCounter = 0;
    m_facing = N;

    m_startingNode = true;

    m_isSolved = false;    

    m_isReadyToSprint = false;

}

Solver::~Solver(){
    delete m_diagnostics;
    delete m_graph;
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
    Serial.print("m_currentPosition before: ");
    Serial.println(m_currentPosition);
    
     // a maze is solved if distance check returns true or 
    // the current position % 6 == 0  <-- this is good for north,
    // but we need a good way to know we have solved the maze
    // if the exit is on the sides
    if(!m_isSolved)
        m_isSolved = ( m_diagnostics->update() );

    // if the maze hasn't been solved
    if(!m_isSolved){
        // if the node hasn't been mapped before
        if( !m_visited[m_currentPosition] ){
            Serial.println("Node has not been mapped before");
            m_difference = 0;
            // if north has no wall
            if( !m_diagnostics->getNorthSensor()->isWall() ){
                // add an edge from the current node to the north node
                m_graph->addEdge( m_currentPosition, m_currentPosition+incrementNorth(), STRAIGHT_WEIGHT );  
                //m_graph->addEdge( m_currentPosition, m_currentPosition+incrementNorth() );  
            }
            else{
                wallCount++;
                m_northIsWallTracker[m_currentPosition] = true;
            }
            
            if( !m_diagnostics->getEastSensor()->isWall() ){
                m_graph->addEdge( m_currentPosition, m_currentPosition+incrementEast(), TURN_WEIGHT );
                //m_graph->addEdge( m_currentPosition, m_currentPosition+incrementEast() );
            }
            else{
                wallCount++;
                m_eastIsWallTracker[m_currentPosition] = true;
            }
            
            if( !m_diagnostics->getWestSensor()->isWall() ){
                m_graph->addEdge(m_currentPosition, m_currentPosition+incrementWest(), TURN_WEIGHT); 
                //m_graph->addEdge( m_currentPosition, m_currentPosition+incrementWest() );
            }
            else{
                wallCount++;
                m_westIsWallTracker[m_currentPosition] = true;
                if(wallCount == 3){
                    m_deadEndTracker[m_currentPosition] = true;
                    //m_graph->setDeadEnd(m_currentPosition);
                }
            }
            
            if(m_startingNode){
                m_startingNode = false;
                m_southIsWallTracker[m_currentPosition] = true;
            }

/*
            // no longer needed in new graph implementation
            // there's always an edge to the node south of the mouse except for the startingNode
            if( !m_startingNode ){ 
                m_graph->addEdge( m_currentPosition, m_currentPosition+incrementSouth() );
            }
            else{
                m_startingNode = false;
                m_southIsWallTracker[m_currentPosition] = true;
            }
*/

            // save the direction the mouse was facing when this node was mapped
            m_dirTracker[m_currentPosition] = m_facing;
            m_visited[m_currentPosition] = true;
        }
        else{
            //Serial.println("retrieving data from memory");
            // the node has been mapped before -- find orientation it was mapped
            // TODO: this could be an error because the locomotion has to turn around to
            // account for this -- in the end, interpretting the maze is much easier though
            Serial.println("adjusting to m_facing stored from memory"); 
           
            
            // refine this to work perfectly
            m_difference = m_dirTracker[m_currentPosition] - m_facing;
            if(m_difference < -1) m_difference = m_difference * -1; // makeshift abs() function

            cout << "m_difference between current facing and previous facing: " << m_difference << std::endl;
            
            m_facing = m_dirTracker[m_currentPosition];
        }

        
        // update local variables to resemble current node
        northIsWall = m_northIsWallTracker[m_currentPosition];
        eastIsWall = m_eastIsWallTracker[m_currentPosition];
        westIsWall = m_westIsWallTracker[m_currentPosition];
        southIsWall = m_southIsWallTracker[m_currentPosition];

        // visually represent which direction mouse is facing BEFORE motion
        //m_diagnostics->blinkLED(m_facing);

        // at this point a decision on where to move needs to be made
        // explore any unvisited nodes first -- clockwise priority excluding south


                    
        if( !m_visited[m_currentPosition + incrementNorth()] && !northIsWall ){
            m_currentPosition += incrementNorth();
            
            goForward();
        }
        else if( !m_visited[m_currentPosition + incrementEast()] && !eastIsWall ){
            m_currentPosition += incrementEast();
           
            turnRight();
        }
        else if( !m_visited[m_currentPosition + incrementWest()] && !westIsWall ){
            m_currentPosition += incrementWest();
           
            turnLeft();
        }
        else{
            // all routes the mouse could take have been explored
//            m_deadEndTracker[m_currentPosition] = true;
            // at this point the mouse needs to move to nodes that are not leading to dead ends
            if( !m_deadEndTracker[m_currentPosition + incrementNorth()] && !northIsWall ){
                m_currentPosition += incrementNorth();
               
                goForward();
            }
            else if( !m_deadEndTracker[m_currentPosition + incrementEast()] && !eastIsWall ){
                m_currentPosition += incrementEast();
                
                turnRight();
            }
            else if( !m_deadEndTracker[m_currentPosition + incrementWest()] && !westIsWall ){
                m_currentPosition += incrementWest();
                              
                turnLeft();
            }
            else{
                m_deadEndTracker[m_currentPosition] = true;
               
                //m_graph->setDeadEnd(m_currentPosition);

                m_currentPosition += incrementSouth();
               
                turnAround();
            
            }
        }
        // visually represent which direction mouse is facing AFTER motion
        //m_diagnostics->blinkLED(m_facing); 
        
        m_diagnostics->getModeLED()->turnOFF();

    }
    else if(!m_isReadyToSprint){
        // can celebrate and also perform DFS to find the shortest path, and visually represent sprint mode
        m_diagnostics->celebrate();
        m_diagnostics->getModeLED()->turnON();
        m_isSolved = true;

        // call the shortest path function to store directions
        m_isReadyToSprint = true;
        m_graph->printGraph();
        m_graph->Dijkstra(); 
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
    }

    //Serial.print("m_facing after: ");
    //Serial.println(m_facing);
    Serial.print("m_currentPosition after: ");
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


void Solver::goForward(){
    // TODO: MAY not need to worry about difference for this one
    if(m_difference == 2){

    }
    else if(m_difference == 1){

    }
    else if(m_difference == -1){

    }
    else{
        m_diagnostics->getNorthLED()->flashLED();
        m_diagnostics->getNorthLED()->flashLED();
    }
}

void Solver::turnRight(){
    //Serial.println("Turning right");
    if(m_difference == 2){
        m_diagnostics->getWestLED()->flashLED();
        m_diagnostics->getWestLED()->flashLED();
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
        m_diagnostics->getEastLED()->flashLED();
        m_diagnostics->getEastLED()->flashLED();
    }
    m_facing = static_cast<DIRECTION>((m_facing + 1)%4);
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
