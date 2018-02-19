// Graph impl file


#include "Graph.h"

using namespace std;

Graph::Graph(){
    m_currentSize = 0;
    
    for(int i = 0; i < MAX_MAZE_SIZE; i++)
        m_dist[i] = INT_MAX, m_sptSet[i] = false;

    m_dist[STARTING_NODE] = 0;
}

Graph::~Graph(){
    // empty destructor
}

void Graph::addEdge(int u, int v, int w){
    m_adj[u].push_back(make_pair(v,w));
    m_adj[v].push_back(make_pair(u,w));
    m_currentSize++;
}

void Graph::printGraph(){
    int v, w;
    for(int i = 0; i < MAX_MAZE_SIZE; i++){
        if(m_adj[i].begin() != m_adj[i].end()){
            cout << "Node " << i << " makes an edge with \n";
            
            for( auto it = m_adj[i].begin(); it!=m_adj[i].end(); it++){
                v = it->first;
                w = it->second;
                cout << "\tNode " << v << " with edge weight = " << w << "\n";
            }
            cout << "\n";
        }
    }
}

void Graph::Dijkstra(){
    int u, v, w;
    for(int i = 0; i < MAX_MAZE_SIZE; i++){
        u = minDistance();
        for(auto it = m_adj[i].begin(); it!=m_adj[i].end(); it++){
            v = it->first;
            w = it->second;
            
            m_sptSet[u] = true;

            if(!m_sptSet[v] && w && m_dist[u] != INT_MAX && m_dist[u]+w < m_dist[v]){
                m_dist[v] = m_dist[u] + w;
            }

        }
    }
    
    printSolution();
}

void Graph::setEndIndex(int i){
    m_endIndex = i;
}

int Graph::minDistance(){
    int min = INT_MAX, min_index;
    
    for(int v = 0; v < MAX_MAZE_SIZE; v++)
        if(m_sptSet[v] == false && m_dist[v] <= min)
            min = m_dist[v], min_index = v;

    return min_index;
}

void Graph::printSolution(){
    cout << "Vertex\tDistance from Source\n";
    for(int i = 0; i < MAX_MAZE_SIZE; i++)
        if(m_dist[i] != INT_MAX)
            cout << i << "\t" << m_dist[i] << "\n";
}

