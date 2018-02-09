/*
 * Author: Sean Graff
 * Created: 2/1/18
 * Version: 1.0
 * Last Edit: 2/1/18
 *
 * Solver Implementation file
 */

#include "Arduino.h"
#include "Solver.h"

Solver::Solver( const int northSensorPin, const int eastSensorPin, \
                const int westSensorPin, const int northLEDPin, \
                const int eastLEDPin, const int westLEDPin, \
                const int southLEDPin, const int modeLEDPin)
{
    m_diagnostics = new Diagnostics(northSensorPin, eastSensorPin, \
                                    westSensorPin, northLEDPin, \
                                    eastLEDPin, westLEDPin, \
                                    southLEDPin, modeLEDPin);
    //Serial.println("Initializing Solver Object");

    //m_curr = createNode(STARTING_INDEX);
    m_curr = NULL;
    m_prev = NULL;

    for(int i = 0; i < MAX_MAZE_SIZE; i++){
        m_visited[i] = false;
    }
    
    m_connectedNodes = 0;
    m_starting = false;
    m_solved = false;
    //m_button = new Button(2, PULLDOWN);
}

Solver::~Solver(){
    delete m_diagnostics;
}
/*
// TODO: this will return a direction
DIRECTION Solver::calculateNextMovement(){
    
    /* The next movement of the micromouse is calculated in the following way:
     * First, the diagnostics system polls all sensors
     * Then, the sensors data is interpreted in the following way.
     * Each direction is checked to see if a wall exists.
     * When a wall does not exist, that direction is added to a stack of open possible routes the mouse could take for that node.
 
     * The Solver checks the top node to see if it has been explored.    
     * When the mouse empties a stack for a node, the node is considered "explored".
     * If it hasn't, it will move to that node and repeat the process.
     * If the mouse reaches a dead end, it needs to back track to the node with multiple possibilities. (If that doesn't exist, something went wrong or the maze is unsolvable)
     *
    
    
    m_diagnostics->update();
    // a wall corresponds to false ( it is not travelable )
    bool currentNorth, currentEast, currentWest, currentSouth;
  
    // NOTE: a '1' indicates that there IS a wall
    // this means a larger number for the orientation is more likely to have a wall to the north
    currentNorth = m_diagnostics->getNorthSensor()->isWall();
    currentEast = m_diagnostics->getEastSensor()->isWall();
    currentWest = m_diagnostics->getWestSensor()->isWall();


    // south is ALWAYS free other than when the mouse is at start. I interpreted the mouse being at start when
    // the data structure storing the mouses movements is empty.
    if(m_queue.isEmpty()){
        currentSouth = true;
        m_prev = NULL; 
    }
    else{
        currentSouth = false;
        m_prev = m_curr;
    }
   
    // create the node using the information we have gathered.
    m_curr = new Node(currentNorth, currentEast, currentSouth, currentWest, m_prev);
    m_curr->printInformation();
    
    m_queue.enqueue(m_curr);
    
}
*/
Diagnostics* Solver::getDiagnostics(){
    return m_diagnostics;
}

Node* Solver::getCurrentNode(){
    return m_curr;
}

Node* Solver::createNode(int id){
    Node* ret;
    
    m_solved = m_diagnostics->update();
    // a wall corresponds to false ( it is not travelable )
    bool currentNorth, currentEast, currentWest, currentSouth;
  
    // NOTE: a '1' indicates that there IS a wall
    // this means a larger number for the orientation is more likely to have a wall to the north
    currentNorth = m_diagnostics->getNorthSensor()->isWall();
    currentEast = m_diagnostics->getEastSensor()->isWall();
    currentWest = m_diagnostics->getWestSensor()->isWall();

    // south is ALWAYS free other than when the mouse is at start. I interpreted the mouse being at start when
    // the data structure storing the mouses movements is empty.
    if(m_starting){
        currentSouth = true;
        m_prev = NULL;
        m_starting = false;
    }
    else{
        currentSouth = false;
        m_prev = m_curr;
    }
 
    // create the node using the information we have gathered.
    ret = new Node(currentNorth, currentEast, currentSouth, currentWest, id, m_prev);
    ret->printInformation();
    
    return ret;
}

// DFS functions
void Solver::dfs(int s){
    //Serial.println("waiting for button press");
    //Serial.println("got a button press");

    m_visited[s] = true;
    

    if(m_adj[s][STARTING_INDEX] == NULL){
        m_prev = NULL;
        //m_curr = createNode(s);
        m_starting = false;
        //Serial.println("finished creating the starting node");
    }
    

    // dynamically create the maze as we go
    if(m_prev != NULL){
        //Serial.println("m_prev is not null");
        //*m_prev = m_curr;
        //m_curr = createNode(s);
        //m_adj[m_curr->getID()].push_back(m_prev);
        //m_adj[m_prev->getID()].push_back(m_curr);
        //*/
    }
    else{
        //Serial.println("moving m_curr to adjacency matrix");
        //m_adj[STARTING_INDEX].push_back(m_curr);
    }

    for(int i = 0; i < m_adj[s].size(); ++i){
        if(m_solved == false){
            if(m_visited[m_adj[s][i]->getID()] == false){
                //Serial.println("recursively calling dfs");
                //dfs(m_adj[s][i]->getID());
            }
        }
    } 
}

void Solver::solve(){
    //Serial.println("entering solve function");
    for(int i = STARTING_INDEX; i < MAX_MAZE_SIZE; i++){
        if(m_solved == false){
            if(m_visited[i] == false){
                //Serial.println("calling dfs");
                dfs(i);
                m_connectedNodes++;
            }
        }
    }
    if(m_solved == true){
        m_diagnostics->celebrate();
        Serial.println("The maze has been solved");
    }
}

// end DFS functions

void Solver::printStack(){
    
}

StackArray<Node*> Solver::getStack(){
    return m_stack;
}

void Solver::printQueue(){

}

QueueArray<Node*> Solver::getQueue(){
    return m_queue;
}
