// Author: Sean
// just default mazes for testing
//

#ifndef EXAMPLEMAZE_H
#define EXAMPLEMAZE_H

//#include "ArduinoSTL.h"
#include <iostream>
#include <list>

using namespace std;

#define MAZE_MAX

enum DIRECTION{
    N,
    E,
    S,
    W
};


class ExampleMaze{
    int V;
    list<int> *adj;
    void DFSUtil(int v, bool visited[]);

    public:
        ExampleMaze(int V);
//        ~ExampleMaze();
        
        void addEdge(int v, int w);
        void DFS();
};

ExampleMaze::ExampleMaze(int V){
    this->V = V;
    adj = new list<int>[V];
}

void ExampleMaze::addEdge(int v, int w){
    adj[v].push_back(w);
}

void ExampleMaze::DFSUtil(int v, bool visited[]){
    visited[v] = true;
    cout << v << " ";
    

    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i){
        if(!visited[*i])
            DFSUtil(*i, visited);
    }
}

void ExampleMaze::DFS(){
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            DFSUtil(i, visited);

}

#endif
