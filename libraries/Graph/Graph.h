// Author: Sean
// graph data structure to store maze layout
// also includes DFS search of layout

#ifndef GRAPH_H
#define GRAPH_H

#include "ArduinoSTL.h"
//#include <iostream>
#include <vector>

using namespace std;

#define MAZE_MAX

class Graph{
    int V;
    vector<int> *adj;
    void DFSUtil(int v, bool visited[]);

    public:
        Graph(int V);
        ~Graph();
        
        void addEdge(int v, int w);
        void DFS();
};

#endif
