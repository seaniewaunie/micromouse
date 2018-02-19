#include <iostream>
#include "Graph.h"

using namespace std;

int main(){

    Graph g;
    g.addEdge(0,7,5);
    g.addEdge(7,14,1);
    g.addEdge(14,21,1);
    g.addEdge(14,15,5);
    g.addEdge(15,16,1);
    g.addEdge(15,8,5);
    g.addEdge(15,22,5);
    g.addEdge(16,17,1);
    g.addEdge(17,18,1);

    g.addEdge(0,42,5);
    g.addEdge(42,35,1);
    g.addEdge(42,43,5);
    g.addEdge(43,44,1);
    g.addEdge(44,45,1);
    g.addEdge(45,46,1);
    g.addEdge(46,47,1);
    g.addEdge(47,40,5);
    g.addEdge(40,39,5);
    g.addEdge(39,38,1);
    g.addEdge(38,37,1);
    g.addEdge(37,36,1);

    g.addEdge(44,2,5);
    g.addEdge(2,9,1);
    g.addEdge(2,1,5);

    g.addEdge(45,3,5);
    g.addEdge(3,10,1);
    
    g.addEdge(3,4,5);
    g.addEdge(4,11,5);
    g.addEdge(11,12,5);
    g.addEdge(12,5,5);
    g.addEdge(12,19,5);
    g.addEdge(19,26,1);
    g.addEdge(26,25,5);
    g.addEdge(25,24,1);
    g.addEdge(24,23,1);
    g.addEdge(23,30,5);

    //g.setEndIndex(30);

    //g.printGraph();

    g.Dijkstra();
    //g.printSolution();
    g.storeEndPath(30);
    return 0;
}
