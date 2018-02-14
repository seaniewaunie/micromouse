#include <iostream>
#include "ExampleMaze.h"

using namespace std;

int main(){
    ExampleMaze e(36);
    
    for(int i = 0; i < 15; i++)
        e.addEdge(i, i+1);
    
    e.addEdge(15, 19);
    e.addEdge(16, 35);

    for(int i = 17; i < 35; i++)
        e.addEdge(i, i+1);
   
    //e.DFS();
    DIRECTION facing = N;

    cout << facing << "\n";
    //facing = facing + 2;
    int num = 3;
    facing = static_cast<DIRECTION>((facing + num)%4); 
    cout << facing  << "\n";

    return 0;
}
