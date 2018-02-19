#include <iostream>
#include "Graph.h"

using namespace std;

int main(){

    Graph g;
    g.addEdge(0,1,1);
    g.addEdge(1,2,1);
    g.addEdge(1,8,5);
    g.addEdge(8,9,5);
    g.addEdge(8,15,1);
    g.addEdge(9,10,1);

    g.printGraph();

    g.Dijkstra();
    return 0;
}
