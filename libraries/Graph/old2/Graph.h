// Author: Sean
// graph data structure to store maze layout
// also includes DFS search of layout

#ifndef GRAPH_H
#define GRAPH_H

//#include "ArduinoSTL.h"
#include <iostream>
#include <vector>

using namespace std;

#define TURN_WEIGHT 3
#define STRAIGHT_WEIGHT 1
#define MAX_MAZE_SIZE 49

class Graph{
    int V;
    vector<int> *adj;
    void DFSUtil(int v, bool visited[]);
     
    
    public:
        Graph(int V);
        ~Graph();
        
        void addEdge(int u, int v, int w);
        void DFS();
        void Dijkstra();
        void setEndIndex(int i);
        void setDeadEnd(int i); 

    private:
        int m_endIndex;
        bool m_deadEnd[MAX_MAZE_SIZE];
        vector<int> m_weight[MAX_MAZE_SIZE];
};

#endif
