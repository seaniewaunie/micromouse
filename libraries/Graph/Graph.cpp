// Graph impl file


#include "Graph.h"

using namespace std;

Graph::Graph(){
    m_currentSize = 0;
    
    for(int i = 0; i < MAX_MAZE_SIZE; i++)
        m_dist[i] = INT_MAX, m_sptSet[i] = false, m_parent[i] = 99;

    m_dist[STARTING_NODE] = 0;
    
    m_parent[STARTING_NODE] = -1;
    // shortest path will always start with 0
    m_shortestPath.push_back(STARTING_NODE);

    m_pathLength = 0;
    m_SPIndex = 0;
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

void Graph::printPath(int j){
    if(m_parent[j] == -1)
        return;
    
    //if(m_parent[j] != 99)
        printPath(m_parent[j]);

    cout << j << " ";
}

void Graph::printSolution(){
    int src = 0;
    cout << F("Node\tDistance\tPath") << endl;
    for(int i = 1; i < MAX_MAZE_SIZE; i++){
        if(m_dist[i] != INT_MAX){
            cout << src << "->" << i;
            cout << "\t" << m_dist[i];
            cout << "\t" << src << " ";
            if(m_parent[i] != 99)
                printPath(i);
            cout << "\n";
        }
    }
}


void Graph::Dijkstra(){
    int u, v, w;
    // each index in maze
    for(int i = 0; i < MAX_MAZE_SIZE-1; i++){
        //cout << "Node: " << i << "\n";
        u = minDistance();
        // each element in vector for index in maze
        for(auto it = m_adj[u].begin(); it!=m_adj[u].end(); it++){
            v = it->first;
            w = it->second;
            //cout << "\t\tu: " << u << "\tv: " << v << "\tw: " << w << endl;
            m_sptSet[u] = true;

            if(!m_sptSet[v] && w && m_dist[u] != INT_MAX && m_dist[u]+w < m_dist[v]){
                m_dist[v] = m_dist[u] + w;
                m_parent[v] = u;
            }
        }
        //cout << "\n";
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

void Graph::storeEndPath(int end){
    if(m_parent[end] == -1)
        return;
    
    if(m_parent[end] != 99)
        storeEndPath(m_parent[end]);

    //cout << end << " ";
    m_pathLength++;
    m_shortestPath.push_back(end);
}

int Graph::getNextSPIndex(){ 
    return m_shortestPath[m_SPIndex++];
}

int Graph::getSPSize(){
    return m_pathLength;
}

