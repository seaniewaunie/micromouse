#include <iostream>
#include "Graph.h"

int main(){
    
    Graph e(48);

    e.setEndIndex(27);

/* 
 * 6       e   
 * 5 x     x   x    
 * 4 x x x x   x    
 * 3   x   x   x    
 * 2   x x x x x     
 * 1 x x   x   x    
 * 0 x   x x x x     
 *   0 1 2 3 4 5 6
 */

    e.DFS();
    //cout << "gets here" << endl;

    return 0;
}

