// Program to find Dijkstra's shortest path using
// priority_queue in STL
//#include "ArduinoSTL.h"
#include "Pair.h"
#include "Vector.h"
using namespace std;
# define INF 0x3f3f3f3f
 
// iPair ==>  Integer Pair
typedef Pair<int, int> iPair;
 
// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V;    // No. of vertices
 
    // In a weighted graph, we need to store vertex
    // and weight Pair for every edge
    Vector< Pair<int, int> > *adj;
 
public:
    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int u, int v, int w);
 
    // prints shortest path from s
    void shortestPath(int s);
};
 
