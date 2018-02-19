// Graph impl file


#include "Graph.h"

using namespace std;

Graph::Graph(){
    //m_currentSize = 0;
     
    for(uint8_t i = 0; i < MAX_MAZE_SIZE; i++)
        m_dist[i] = INT_MAX, m_sptSet[i] = false;
    
    m_parent[STARTING_NODE] = -1;
    m_dist[STARTING_NODE] = 0;

    //cout << "gets here" << endl;

    // initialize graph    
    for(uint8_t i = 0; i < MAX_MAZE_SIZE; i++){
        for(uint8_t j = 0; j < MAX_MAZE_SIZE; j++){
            graph[i][j] = 0;
        }
    }


}

Graph::~Graph(){
    // empty destructor
}

void Graph::addEdge(uint8_t u, uint8_t v, uint8_t w){
    //m_adj[u].push_back(make_pair(v,w));
    //m_adj[v].push_back(make_pair(u,w));
    //m_currentSize++;
    graph[u][v] = w;
    graph[v][u] = w;
}

/*
void Graph::printGraph(){
    uint8_t v, w;
    for(uint8_t i = 0; i < MAX_MAZE_SIZE; i++){
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

void Graph::printPath(uint8_t j){
    if(m_parent[j] == -1)
        return;

    printPath(m_parent[j]);

    cout << j << " ";
}

void Graph::printSolution(){
    uint8_t src = 0;
    cout << "Node\tDistance\tPath" << endl;
    for(uint8_t i = 1; i < MAX_MAZE_SIZE; i++){
        if(m_dist[i] != INT_MAX){
            cout << src << "->" << i;
            cout << "\t" << m_dist[i];
            cout << "\t\t" << src << " ";
            printPath(i);
            cout << "\n";
        }
    }
}
*/
void Graph::storeEndPath(uint8_t j){
    
    if(m_parent[j] == -1)
        return;

    storeEndPath(m_parent[j]);
    
    cout << j << " ";
    m_shortestPath.push_back(j);
}

void Graph::Dijkstra(){
    // convert m_adj to [49][49] adjacency matrix
    
    uint8_t u, v, w;
    // convert m_adj to matrix
/*
    for(uint8_t i = 0; i < MAX_MAZE_SIZE; i++){
        for(auto it = m_adj[i].begin(); it!=m_adj[i].end(); it++){
            v = it->first;
            w = it->second;
            graph[i][v] = w;
            graph[v][i] = w;
        }
    }
*/

    // perform Dijkstras algorithm
    for(uint8_t count = 0; count < MAX_MAZE_SIZE-1; count++){
        uint8_t u = minDistance();

        m_sptSet[u] = true;

        for(int x = 0; x < MAX_MAZE_SIZE; x++){
            if(!m_sptSet[x] && graph[u][x] && m_dist[u] != INT_MAX && m_dist[u] + graph[u][x] < m_dist[x]){
                m_parent[x] = u;
                m_dist[x] = m_dist[u] + graph[u][x];
            }
        }
    }

    //printSolution();
}

/*
void Graph::setEndIndex(int i){
    m_endIndex = i;
}
*/
uint8_t Graph::minDistance(){
    uint8_t min = INT_MAX, min_index;
    
    for(uint8_t v = 0; v < MAX_MAZE_SIZE; v++)
        if(m_sptSet[v] == false && m_dist[v] <= min)
            min = m_dist[v], min_index = v;

    return min_index;
}
/*
void Graph::printSolution(){
    cout << "Vertex\tDistance from Source\n";
    for(int i = 0; i < MAX_MAZE_SIZE; i++)
        if(m_dist[i] != INT_MAX)
            cout << i << "\t" << m_dist[i] << "\n";
}
*/
