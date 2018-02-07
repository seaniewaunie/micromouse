/*
 * Author: Sean Graff
 * Created: 2/1/18
 * Version: 1.0
 * 
 * Node Implementation file
 */ 

#include "Arduino.h"
#include "Node.h"

#define DEADEND 0b0010 // this is the DIRECTION combination for a dead end

// a fork is when more than 1 direction excluding south is open
#define FORK1 0b1110
#define FORK2 0b1011
#define FORK3 0b0111
#define FORK4 0b1111

Node::Node(bool north, bool east, bool south, bool west, Node *prev){
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

    if(south == true
    m_start = false;
    m_end = false;

    // the south node is the one we just came from, which is sent in the Node() constructor
    m_southNode = prev;
}

Node::~Node(){
   // TODO 
}

void Node::setOrientation(uint8_t orient){
    m_orientation = orient;
}

uint8_t Node::getOrientation(){
    return m_orientation;
}

bool Node::isNorthOpen(){
    return m_orientation & N;
}

bool Node::isEastOpen(){
    return m_orientation & E;
}

bool Node::isSouthOpen(){
    return m_orientation & S;
}

bool Node::isWestOpen(){
    return m_orientation & W;
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
