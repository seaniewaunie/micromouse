/*
 * Author: Sean and Erfan
 * Created: 2/1/18
 * Version: 1.0
 * Last Edited: 2/1/18
 *
 * Description: Solver is the maze solving object for this MM6. Solver works by exploring the maze and attempting to map
 * it to memory. Once the maze is mapped, it calculates the fastest route to the end of the maze from the start.
 *
 * It uses the MODE LED from the Diagnostics system to signify whether it needs to explore in "Traversal" mode, or whether it knows
 * the fastest route, and is ready to perform in "Sprint" mode.
 *
 * The Solver is heavily dependent on the Sensor System. It makes use of the Diagnostics systems "update" function to poll each of the
 * sensors. Based on the sensors results, it is able to map a node in the maze.
 *
 * The solver is able to keep track of forks in the maze, where multiple paths are possible to take. During Traversal mode, it will
 * explore each of these options in search for the exit. Once it finds the exit, it will know that it found it, and mark it in memory,
 * but it will return to the maze and explore the other routes in case one of them lead to a faster solution.
 *
 *
 * calculateNextMovement() uses a very detailed DFS... or Best First Search
 *
 *
 * The queue stores the final path, the stack is used to store directions at each node.
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "ArduinoSTL.h"
//#include "Button.h"
#include <vector>

#include "Arduino.h"
#include "Diagnostics.h"
#include "Node.h"
// may not need these two below
#include "StackArray.h"
#include "QueueArray.h"

#define MAX_MAZE_SIZE 36 //6x6 = 36 nodes
#define MAX_MAZE_EDGES 60 // there are 60 traversable edges
#define STARTING_INDEX 0


class Solver {
  
  public:
    Solver( const int northSensorPin, const int eastSensorPin, \
            const int westSensorPin, const int northLEDPin, \
            const int eastLEDPin, const int westLEDPin, \
            const int southLEDPin, const int modeLEDPin);
    ~Solver();
    
    // TODO: this will return a direction
    DIRECTION calculateNextMovement();

    Diagnostics* getDiagnostics();
    
    Node* getCurrentNode();
    
    Node* createNode(int id);

    // begin DFS functions
    void dfs(int s);

    void solve();

    // end DFS functions 

    bool isSolved(){ return m_solved; }

    void printStack();
    StackArray<Node*> getStack();

    void printQueue();
    QueueArray<Node*> getQueue();


  private:
    Diagnostics *m_diagnostics; 

    Node *m_curr;
    Node *m_prev;

// TODO: delete stack and queue
//    StackArray<Node*> m_stack;

//    QueueArray<Node*> m_queue;

    std::vector<Node*> m_adj[MAX_MAZE_SIZE];
    bool m_visited[MAX_MAZE_SIZE];
    
    bool m_starting;

    int m_connectedNodes;

    bool m_solved;

    int m_index;

// debugging button
//    Button *m_button;
};

#endif
