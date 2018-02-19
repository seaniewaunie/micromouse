// Sean Graff

#ifndef GRAPH_H
#define GRAPH_H

#include "ArduinoSTL.h"
//#include <iostream>
//#include <vector>
//#include <utility>
//#include <limits.h>

#define MAX_MAZE_SIZE 30
#define STARTING_NODE 0
#define INT_MAX 0b11111111

class Graph{

    public:
        Graph();
        ~Graph();

        void addEdge(int u, int v, int w);
        void printGraph();
        void Dijkstra();

        // dijkstra utilities
        int minDistance();
        void printSolution();
        void printPath(int j);
        //void storeEndPath(int j);

    private:
        // weighted graph variables
        //std::vector< std::pair<int, int> > m_adj[MAX_MAZE_SIZE];
        //int m_currentSize;

        // dijkstra variables
        bool m_sptSet[MAX_MAZE_SIZE];
        uint8_t m_dist[MAX_MAZE_SIZE]; // tells distance to node
        //std::vector<uint8_t> m_shortestPath; // contains indexes in order of shortest path to end
        char m_parent[MAX_MAZE_SIZE];
        

        // going to have to move the graph into the .ino file
        //uint8_t graph[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
};

#endif
