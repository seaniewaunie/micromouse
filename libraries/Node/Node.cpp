/*
 * Author: Sean Graff
 * Created: 2/1/18
 * Version: 1.0
 * 
 * Node Implementation file
 */ 

#include "Arduino.h"
#include "Node.h"

// NOTE: a '1' indicates there IS a wall there

#define DEADEND 0b1101 // this is the DIRECTION combination for a dead end

// a fork is when more than 1 direction excluding south is open
#define FORK1 0b0001
#define FORK2 0b0100
#define FORK3 0b1000
#define FORK4 0b0000

#define MASK 0b1111

Node::Node(bool north, bool east, bool south, bool west, int id, Node *prev){
    // set constant booleans for directions
    m_northDir = north;
    m_eastDir = east;
    m_southDir = south;
    m_westDir = west;

    // set orientation ex. NESW --> 0010 if in dead end
    m_orientation = N*m_northDir + E*m_eastDir + S*m_southDir + W*m_westDir;
    
    // determine if the node is a dead end
    if(m_orientation == DEADEND)
        m_deadEnd = true;
    else
        m_deadEnd = false;
    
    // determine if the node is a fork
    if(m_orientation == FORK1 || m_orientation == FORK2 || m_orientation == FORK3 || m_orientation == FORK4)
        m_fork = true;
    else
        m_fork = false;
   
    // when creating a new node, m_explored is always false
    // this gets updated to true AFTER completing all possible directions on a node
    m_explored = false;
    m_visited = false;

    // we are at the start if south is currently blocked
    // technically we should NEVER go back through the start
    m_start = m_southDir;

    // m_diagnostics and the Solver will update this... by default it is false
    m_end = false;

    // the south node is the one we just came from, which is sent in the Node() constructor
    m_southNode = prev;
    
    m_id = id; 

}

Node::~Node(){
   // TODO 
}

void Node::setOrientation(uint8_t orient){
    m_orientation = orient;
}

// circular left shift when the node is rotated left...
// N->E, E->S, S->W, W->N
// so NESW becomes ESWN
void Node::rotateLeft(){
    m_orientation = (m_orientation << 1) & MASK | (m_orientation >> 3);
}

// NESW becomes WNES
void Node::rotateRight(){
   m_orientation = (m_orientation << 3) & MASK | (m_orientation >> 1);
}
// circular shift twice
// NESW becomes SWNE
void Node::turnAround(){
   m_orientation = (m_orientation << 2) & MASK | (m_orientation >> 2); 
}

uint8_t Node::getOrientation(){
    return m_orientation;
}

int Node::getID(){
    return m_id;
}

bool Node::isNorthOpen(){
    return !(m_orientation & N);
}

bool Node::isEastOpen(){
    return !(m_orientation & E);
}

bool Node::isSouthOpen(){
    return !(m_orientation & S);
}

bool Node::isWestOpen(){
    return !(m_orientation & W);
}

void Node::setDeadEnd(bool val){
    m_deadEnd = val;
}

void Node::setFork(bool val){
    m_fork = val;
}

void Node::setExplored(bool val){
    m_explored = val;
}

void Node::setVisited(bool val){
    m_visited = val;
}

bool Node::hasBeenVisited(){
    return m_visited;
}

bool Node::isDeadEnd(){
    return m_deadEnd;
}

bool Node::isFork(){
    return m_fork;
}

bool Node::isExplored(){
    return m_explored;
}

void Node::setStart(bool val){
    m_start = val;
}

void Node::setEnd(bool val){
    m_end = val;
}

bool Node::isStart(){
    return m_start;
}

bool Node::isEnd(){
    return m_end;
}

Node* Node::getNorth(){
    return m_northNode;
}

void Node::setNorth(Node* node){
    m_northNode = node;
}

Node* Node::getEast(){
    return m_eastNode;
}

void Node::setEast(Node* node){
    m_eastNode = node;
}

Node* Node::getSouth(){
    return m_southNode;
}

void Node::setSouth(Node* node){
    m_southNode = node;
}

Node* Node::getWest(){
    return m_westNode;
}

void Node::setWest(Node* node){
    m_westNode = node;
}
/*
void Node::printInformation(){
    Serial.println("----------------------------");
    Serial.println("Information on node:");
    Serial.println("----------------------------");
    Serial.print("orientation: "); Serial.println(m_orientation);
    
    if(m_northDir)
        Serial.println("North has a wall");
    else
        Serial.println("North is open");
    
    if(m_eastDir)
        Serial.println("East has a wall");
    else
        Serial.println("East is open");
    
    if(m_southDir)
        Serial.println("South has a wall");
    else
        Serial.println("South is open");

    if(m_westDir)
        Serial.println("West has a wall");
    else
        Serial.println("West is open");

    if(m_deadEnd)
        Serial.println("*** This node is a dead end ***");

    if(m_fork)
        Serial.println("--- This node has multiple routes to explore ---");

    if(m_explored)
        Serial.println("&&& All routes have been explored in this node &&&");
    
    if(m_visited)
        Serial.println("### This node has been visited ###");

    Serial.println("----------------------------");
}
//*/
//*
// Eventually, we will comment out the above printInfo because
// it uses up a LOT of memory
void Node::printInformation(){
    Serial.println(m_id);
}
//*/
