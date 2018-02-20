// Author: Sean
// Version: 2
// Date: Feb. 11

// first the maze needs to be mapped
// so the first run will be adding edges to a graph


#ifndef SOLVER_H
#define SOLVER_H

#include "Arduino.h"
#include "Diagnostics.h"
//#include "Node.h"

#include "Graph.h"

// defined in Graph.h
//#define MAX_MAZE_SIZE 49 //7x7 = 49 nodes
// NOTE: I know it's a 6x6 maze, but there is an exit node... so I'm accounting for that

#define VERTICAL_INCREMENT 1
#define HORIZONTAL_INCREMENT 7

#define TURN_WEIGHT 5
#define STRAIGHT_WEIGHT 1

#define STARTING_INDEX 0 // starting index doesn't matter in this design

// the bitfield for booleans that each node has associated with it
struct Node{
    bool visited:1;
    DIRECTION direction:2;
    bool deadEnd:1;
    bool eastIsWall:1;
    bool westIsWall:1;
    bool northIsWall:1;
    bool southIsWall:1;
};

class Solver {
    public:
        Solver();
        Solver(const int northSensorPin, const int eastSensorPin, \
            const int westSensorPin, const int northLEDPin, \
            const int eastLEDPin, const int westLEDPin, \
            const int southLEDPin, const int modeLEDPin);
        ~Solver();
        
        Diagnostics* getDiagnostics();

        void nextNode(); 
        
        int incrementNorth();
        int incrementEast();
        int incrementSouth();
        int incrementWest();

        void goForward();
        void turnRight();
        void turnLeft();
        void turnAround();

        void shift();

    private:
        Graph *m_graph;
        Diagnostics *m_diagnostics;
        int m_currentPosition;
        int m_turnCounter;
        DIRECTION m_facing;
        int m_difference;
        bool m_startingNode;
        
        bool m_isSolved;

// this variable will take up 1 byte * 49 
// TODO: could make dynamic?
        Node m_nodeContainer[MAX_MAZE_SIZE];

/*
// these variables take up A LOT of memory
        DIRECTION m_dirTracker[MAX_MAZE_SIZE];
        bool m_deadEndTracker[MAX_MAZE_SIZE];
        bool m_eastIsWallTracker[MAX_MAZE_SIZE];
        bool m_westIsWallTracker[MAX_MAZE_SIZE];
        bool m_northIsWallTracker[MAX_MAZE_SIZE];
        bool m_southIsWallTracker[MAX_MAZE_SIZE];
        bool m_visited[MAX_MAZE_SIZE];
*/    

        // begin sprint mode variables
        bool m_isReadyToSprint;

};

#endif
