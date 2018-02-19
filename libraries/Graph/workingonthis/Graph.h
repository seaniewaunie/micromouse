// Sean Graff

#ifndef GRAPH_H
#define GRAPH_H

#include "ArduinoSTL.h"
//#include <iostream>
#include <vector>
#include <utility>
//#include <limits.h>

#define MAX_MAZE_SIZE 49
#define STARTING_NODE 0
#define INT_MAX 0b11111111

class Graph{

    public:
        Graph();
        ~Graph();

        void addEdge(uint8_t u, uint8_t v, uint8_t w);
        void Dijkstra();

        // dijkstra utilities
        uint8_t minDistance();
/*
        void printGraph();
        void printSolution();
        void printPath(uint8_t j);
*/      
        void storeEndPath(uint8_t j);

    private:
        // weighted graph variables
        //std::vector< std::pair<uint8_t, uint8_t> > m_adj[MAX_MAZE_SIZE];
        
        // dijkstra variables
        bool m_sptSet[MAX_MAZE_SIZE];
        uint8_t m_dist[MAX_MAZE_SIZE]; // tells distance to node
        std::vector<uint8_t> m_shortestPath; // contains indexes in order of shortest path to end
        uint8_t m_parent[MAX_MAZE_SIZE];
        uint8_t graph[MAX_MAZE_SIZE][MAX_MAZE_SIZE];

};

#endif
