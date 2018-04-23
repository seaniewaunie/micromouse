// Sean Graff
// Data structure for the physical maze
// graph is bi-directional and weighted
// each node has a vector of nodes which it is connected to

#ifndef GRAPH_H
#define GRAPH_H

#include "Arduino.h"
#include "ArduinoSTL.h"
//#include <iostream>
#include <vector>
#include <utility>
#include <queue>
//#include "QueueArray.h"

#define MAX_MAZE_SIZE 49
#define STARTING_NODE 0
#define MAX 99

// 2 bytes
struct dijkstra_t{
    bool sptSet:1;
    int parent:7;
    int dist:8;
};

class Graph{

    public:
        Graph();
        ~Graph();

        void addEdge(int u, int v, int w);
        //void printGraph();
        void Dijkstra(int from, int to);
        void setEndIndex(int i);

        // dijkstra utilities
        uint8_t minDistance();
        void printSolution(int from, int to);
        void printPath(int from, int to);
        //void storeEndPath(int end); // stores the path to end node
        void storePath(int from, int to);
        std::queue<uint8_t> getShortestPath();
        uint8_t getDistance(int to);

        bool isSPEmpty();
        int getNextSPIndex();

    private:
        // weighted graph variables
        uint8_t m_endIndex;
        std::vector< std::pair<uint8_t, uint8_t> > m_adj[MAX_MAZE_SIZE];
        uint8_t m_currentSize;

        // dijkstra variables
        std::queue<uint8_t> m_shortestPath; // keeps track of path to next node

        dijkstra_t m_dutilContainer[MAX_MAZE_SIZE];

        /*
        bool m_sptSet[MAX_MAZE_SIZE];
        uint8_t m_dist[MAX_MAZE_SIZE]; // tells distance to node
        uint8_t m_parent[MAX_MAZE_SIZE];
        */
};

#endif
