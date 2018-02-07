/*
 * Author: Sean and Erfan
 * Created: 2/1/18
 * Version: 1.0
 * Last Edited: 2/1/18
 *
 * Description: Every node in the maze has 3 possibilities and 1 guarantee (besides the start) of open directions that can be traversed.
 * South is ALWAYS guaranteed to be open besides at the start of the maze. In the starting node, south is considered closed.
 *
 * A node is "explored" when every possible route has been taken
 * A node is a "fork" when it has multiple possible routes
 * A node is a "dead end" when it has no possible routes
 *
 * A direction is set to open when it's respective sensor returns false for isWall()
 *
 * m_orientation saves the state in which the node was explored last.
 */

#ifndef NODE_H
#define NODE_H

#include "Arduino.h"

enum DIRECTION{
    N=8,
    E=4,
    S=2,
    W=1
};

class Node {
  
  public:
    Node(bool north, bool east, bool south, bool west, Node *prev);
    ~Node();

    void setOrientation(uint8_t orient);
    void rotateLeft();
    void rotateRight();
    void turnAround();

    uint8_t getOrientation();

    bool isNorthOpen();
    bool isEastOpen();
    bool isSouthOpen();
    bool isWestOpen();
    
    void setDeadEnd(bool val);
    void setFork(bool val);
    void setExplored(bool val);

    bool isDeadEnd();
    bool isFork();
    bool isExplored();

    void setStart(bool val);
    void setEnd(bool val);
    
    bool isStart();
    bool isEnd();

    Node* getNorth();
    void setNorth(Node* node);
    
    Node* getEast();
    void setEast(Node* node);

    Node* getSouth();
    void setSouth(Node* node);

    Node* getWest();
    void setWest(Node* node);

  private:
    uint8_t m_orientation;
    
    bool m_northDir;
    bool m_eastDir;
    bool m_southDir;
    bool m_westDir;

    bool m_deadEnd;
    bool m_fork;
    bool m_explored;

    bool m_start;
    bool m_end;

    Node* m_northNode;
    Node* m_eastNode;
    Node* m_southNode;
    Node* m_westNode;
};

#endif
