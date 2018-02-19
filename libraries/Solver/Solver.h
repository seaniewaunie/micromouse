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

class Solver {
    public:
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
        bool m_visited[MAX_MAZE_SIZE];
        int m_turnCounter;
        DIRECTION m_facing;
        int m_difference;
        DIRECTION m_dirTracker[MAX_MAZE_SIZE];
        bool m_deadEndTracker[MAX_MAZE_SIZE];
        bool m_startingNode;
        
        bool m_isSolved;

        bool m_eastIsWallTracker[MAX_MAZE_SIZE];
        bool m_westIsWallTracker[MAX_MAZE_SIZE];
        bool m_northIsWallTracker[MAX_MAZE_SIZE];
        bool m_southIsWallTracker[MAX_MAZE_SIZE];
        
        // begin sprint mode variables
        bool m_isReadyToSprint;

};

#endif
