#include "Graph.h"

Graph::Graph(int V){
    this->V = V;
    adj = new vector<int>[V];
    m_endIndex = 0;

    for(int i = 0; i < MAX_MAZE_SIZE; i++){
        m_deadEnd[i] = false;
        //m_weight[i] = 999;
    }

}

Graph::~Graph(){
    // this causes an error when attempting to delete
    //delete adj;
}

void Graph::setEndIndex(int i){
    m_endIndex = i;
}

void Graph::setDeadEnd(int i){
    m_deadEnd[i] = true;
}

void Graph::addEdge(int u, int v, int w){
    m_weight[u].push_back(w);
    adj[u].push_back(v);
}

void Graph::DFSUtil(int v, bool visited[]){
    visited[v] = true;
    cout << v << " ";
    
    if(v == m_endIndex){
        cout << "\nfound end node" << endl; 
    }
    
    vector<int>::iterator i;
    if(adj[v].size() < 2){
        for(i = adj[v].begin(); i != adj[v].end(); ++i){
            if(!visited[*i] && !m_deadEnd[*i]){
                DFSUtil(*i, visited);
            }
        }
    }
    else{
        // find smallest weight in adj and take that path
        //cout << " this node may have multiple routes" << endl;
        int minWeight = m_weight[v][0];
        int minWeightIndex = adj[v][0];
        for(i = adj[v].begin()+1; i != adj[v].end(); ++i){
            if(minWeight > m_weight[v][*i]){
                minWeight = m_weight[v][*i];
                minWeightIndex = adj[v][*i];
            }
        }
        if(!visited[minWeightIndex] && !m_deadEnd[minWeightIndex]){
            DFSUtil(minWeightIndex, visited);
        }
    }

}

// for unweighted graph
void Graph::DFS(){
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    for(int i = 0; i < V; i++)
        if(visited[i] == false && !m_deadEnd[i])
            DFSUtil(i, visited);

}

void Graph::Dijkstra(){

}

