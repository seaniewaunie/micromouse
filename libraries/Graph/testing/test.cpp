#include <iostream>
#include "Graph.h"

using namespace std;

int main(){

    Graph g;
    g.addEdge(0,7,5);
    g.addEdge(7,8,1);
    g.addEdge(0,42,5);
    g.addEdge(42,43,5);
    g.addEdge(42,35,1);
    g.addEdge(35,36,5);
    g.addEdge(36,37,1);
    g.addEdge(37,38,1);
    g.addEdge(37,44,5);
    g.addEdge(44,45,5);
    g.addEdge(45,3,5);
    g.addEdge(3,2,5);
    g.addEdge(2,1,1);
    g.addEdge(2,9,5);
    g.addEdge(9,10,5);
    g.addEdge(10,11,1);


    g.printGraph();

    g.Dijkstra();
    return 0;
}
