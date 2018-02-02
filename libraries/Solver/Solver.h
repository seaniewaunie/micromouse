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
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "Arduino.h"
#include "Diagnostics.h"
#include "Node.h"

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


  private:
    Diagnostics *m_diagnostics; 

    Node *m_curr;



};

#endif
