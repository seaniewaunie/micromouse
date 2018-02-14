#include "Graph.h"

Graph::Graph(int V){
    this->V = V;
    adj = new vector<int>[V];
}

Graph::~Graph(){
    delete adj;
}

void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[]){
    visited[v] = true;
    cout << v << " ";
    

    vector<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i){
        if(!visited[*i])
            DFSUtil(*i, visited);
    }
}

void Graph::DFS(){
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            DFSUtil(i, visited);

}


