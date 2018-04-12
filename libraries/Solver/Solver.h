// Author: Sean
// Version: 2
// Date: Feb. 11

// first the maze needs to be mapped
// so the first run will be adding edges to a graph


#ifndef SOLVER_H
#define SOLVER_H

//#include "Arduino.h"
#include "Diagnostics.h"
#include "Graph.h"
#include "Locomotion.h"

#define VERTICAL_INCREMENT 1
#define HORIZONTAL_INCREMENT 7

#define TURN_WEIGHT 5
#define STRAIGHT_WEIGHT 1

#define STARTING_INDEX 0 // starting index doesn't matter in this design

// the bitfield for information that each node has associated with it
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
        ~Solver();

        Diagnostics* getDiagnostics();

        void nextNode();

        int incrementNorth();
        int incrementEast();
        int incrementSouth();
        int incrementWest();

        void findShortestUnvisitedPath();
        void traverseShortestPath();

        void goForward();
        void turnRight();
        void turnLeft();
        void turnAround();

        void shift();

    private:
        Graph *m_graph;
        Diagnostics *m_diagnostics;
        Locomotion *m_loco;

        int m_currentPosition;
        int m_turnCounter;
        DIRECTION m_facing;

        int m_difference;
        bool m_startingNode;
        bool m_isSolved;

        Node m_nodeContainer[MAX_MAZE_SIZE];

        // begin sprint mode variables
        bool m_isReadyToSprint;

};

#endif
