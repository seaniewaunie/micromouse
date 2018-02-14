#include <iostream>
#include "ExampleMaze.h"

using namespace std;

int main(){
    ExampleMaze e(36);
   
    e.addEdge(0,1);
    e.addEdge(0,7);
    e.addEdge(0,42);
    e.addEdge(1,2);
    e.addEdge(1,8);
    e.addEdge(1,43);
    e.addEdge(1,0);
    e.addEdge(1,0);

    //e.DFS();
    DIRECTION facing = N;

    cout << facing << "\n";
    //facing = facing + 2;
    int num = 3;
    facing = static_cast<DIRECTION>((facing + num)%4); 
    cout << facing  << "\n";

    return 0;
}
