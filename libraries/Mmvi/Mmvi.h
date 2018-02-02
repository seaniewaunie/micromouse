/*
 * Author: Sean Graff
 * Created: 1/31/18
 * Version: 1.0
 * Last Edited: 1/31/18
 *
 * Description: The Mouse object (MMVI) is a structure that combines all
 * of the modularized designs which include: 
 * - the diagnostics system ( which includes the sensor system )
 * - the maze solving algorithm
 * - the locomotion system
 * 
 *
 *
 */

#ifndef MMVI_H
#define MMVI_H

#include "Arduino.h"

// include all the modularized systems
#include "Diagnostics.h"
#include "Maze.h"

enum MODE {
    Traversal,
    Sprint
};

class Mmvi {
  
  public:
    Mmvi();
    ~Mmvi();
    
    void setMode(MODE mode);
    MODE getMode();
    
    void TraversalSolve();
    void SprintSolve();
    
    bool isFinished(); 
    
    Diagnostics getDiagnostics();

    Maze getMaze();

  private:
    bool m_finished;
    MODE m_mode;
    Diagnostics m_diagnostics;
    Maze m_maze;
};

#endif
