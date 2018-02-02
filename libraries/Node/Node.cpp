/*
 * Author: Sean Graff
 * Created: 2/1/18
 * Version: 1.0
 * 
 * Node Implementation file
 */ 

#include "Arduino.h"
#include "Node.h"

Node::Node(bool north, bool east, bool south, bool west){
    m_north = north;
    m_east = east;
    m_south = south;
    m_west = west;

    m_deadEnd = false;
    m_fork = false;
    m_explored = false;

    m_start = false;
    m_end = false;
}

Node::~Node(){
    // empty
}

bool Node::isNorthOpen(){
    return m_north;
}

bool Node::isEastOpen(){
    return m_east;
}

bool Node::isSouthOpen(){
    return m_south;
}

bool Node::isWestOpen(){
    return m_west;
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
    return m_north;
}

void Node::setNorth(Node* node){
    m_north = node;
}

Node* Node::getEast(){
    return m_east;
}

void Node::setEast(Node* node){
    m_east = node;
}

Node* Node::getSouth(){
    return m_south;
}

void Node::setSouth(Node* node){
    m_south = node;
}

Node* Node::getWest(){
    return m_west;
}

void Node::setWest(Node* node){
    m_west = node;
}
