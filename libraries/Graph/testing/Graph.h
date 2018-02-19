// Sean Graff

#ifndef GRAPH_H
#define GRAPH_H

//#include "ArduinoSTL.h"
#include <iostream>
#include <vector>
#include <utility>
//#include <limits.h>

#define MAX_MAZE_SIZE 49
#define STARTING_NODE 0
#define INT_MAX 999

class Graph{

    public:
        Graph();
        ~Graph();

        void addEdge(int u, int v, int w);
        void printGraph();
        void Dijkstra();
        void setEndIndex(int i);

        // dijkstra utilities
        int minDistance();
        void printSolution();

    private:
        // weighted graph variables
        int m_endIndex;
        std::vector< std::pair<int, int> > m_adj[MAX_MAZE_SIZE];
        int m_currentSize;

        // dijkstra variables
        bool m_sptSet[MAX_MAZE_SIZE];
        int m_dist[MAX_MAZE_SIZE]; // tells distance to node

};

#endif
