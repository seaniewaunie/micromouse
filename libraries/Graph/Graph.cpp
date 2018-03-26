// Graph impl file


#include "Graph.h"

using namespace std;

Graph::Graph(){
    m_currentSize = 0;
    
    for(int i = 0; i < MAX_MAZE_SIZE; i++){
        m_dutilContainer[i].dist = MAX;
        m_dutilContainer[i].sptSet = false;
        m_dutilContainer[i].parent = MAX;
    }

    //m_dist[STARTING_NODE] = 0;
    
    m_dutilContainer[STARTING_NODE].parent = -1;
    //m_parent[STARTING_NODE] = -1;
   
    m_shortestPath = queue<int>();
    //m_shortestPath = new QueueArray<uint8_t>();
    // shortest path will always start with 0
    //m_shortestPath.push_back(STARTING_NODE);
    //m_shortestPath->setPrinter(Serial);
}

Graph::~Graph(){
    // empty destructor
    //delete m_shortestPath;
}

void Graph::addEdge(int u, int v, int w){
    m_adj[u].push_back(make_pair(v,w));
    m_adj[v].push_back(make_pair(u,w));
    m_currentSize++;
}

/*
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
*/

void Graph::printPath(int from, int to){
    if(m_dutilContainer[from].parent == -1)
        return;
   
    if(m_dutilContainer[from].parent != MAX)
        printPath(m_dutilContainer[from].parent, to);

    Serial.print(from);
    Serial.print(" ");
}


void Graph::printSolution(int from, int to){
    int src = from;
    cout << "Node\tDistance\tPath" << endl;
    for(int i = 0; i < MAX_MAZE_SIZE; i++){
        if(m_dutilContainer[i].dist != MAX){
            cout << src << "->" << i;
            cout << "\t" << m_dutilContainer[i].dist;
            cout << "\t" << src << " ";
            if(m_dutilContainer[i].parent != MAX)
                if(i == to)
                    storePath(to, src);
                    //printPath(i, src);
                else
                    printPath(to, src);
            cout << "\n";
        }
    }
}


void Graph::Dijkstra(int from, int to){
    // reset distances 
    for(int i = 0; i < MAX_MAZE_SIZE; i++){
        m_dutilContainer[i].dist = MAX;
        m_dutilContainer[i].sptSet = false;
        m_dutilContainer[i].parent = MAX;
    }  

    m_dutilContainer[from].parent = -1;
 
    m_dutilContainer[from].dist = 0;
    
    
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
            m_dutilContainer[u].sptSet = true;

            if(!m_dutilContainer[v].sptSet && w && m_dutilContainer[u].dist != MAX && m_dutilContainer[u].dist+w < m_dutilContainer[v].dist){
                m_dutilContainer[v].dist = m_dutilContainer[u].dist + w;
                m_dutilContainer[v].parent = u;
            }
        }
        //cout << "\n";
    }
    storePath(to, from);

    //printSolution(from, to);
}

uint8_t Graph::minDistance(){
    int min = MAX, min_index;
    
    for(int v = 0; v < MAX_MAZE_SIZE; v++)
        if(m_dutilContainer[v].sptSet == false && m_dutilContainer[v].dist <= min)
            min = m_dutilContainer[v].dist, min_index = v;

    return min_index;
}

/*
void Graph::storeEndPath(int end){
    if(m_parent[end] == -1)
        return;
    
    if(m_parent[end] != MAX)
        storeEndPath(m_parent[end]);

    //cout << end << " ";
    m_pathLength++;
    m_shortestPath->push(end);
}
*/

void Graph::storePath(int from, int to){
    if(m_dutilContainer[from].parent == -1){
        return;
    }

    if(m_dutilContainer[from].parent != MAX)
        storePath(m_dutilContainer[from].parent, to);

    Serial.print(from);
    Serial.print(" and ");
    //m_pathLength++;
    m_shortestPath.push(static_cast<int>(from));
    cout << m_shortestPath.back() << endl;
    //m_shortestPath.pop();
}


queue<int> Graph::getShortestPath(){
    return m_shortestPath;
}

uint8_t Graph::getDistance(int to){
    return m_dutilContainer[to].dist;
}

bool Graph::isSPEmpty(){
    return m_shortestPath.empty();
}

int Graph::getNextSPIndex(){
    //m_shortestPath.pop_back();
    int ret = m_shortestPath.front();
    m_shortestPath.pop();
    cout << ret << endl;
    return ret;
}

