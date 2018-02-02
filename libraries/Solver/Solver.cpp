/*
 * Author: Sean Graff
 * Created: 2/1/18
 * Version: 1.0
 * Last Edit: 2/1/18
 *
 * Solver Implementation file
 */

#include "Arduino.h"
#include "Solver.h"

Solver::Solver( const int northSensorPin, const int eastSensorPin, \
                const int westSensorPin, const int northLEDPin, \
                const int eastLEDPin, const int westLEDPin, \
                const int southLEDPin, const int modeLEDPin)
{
    m_diagnostics = new Diagnostics(northSensorPin, eastSensorPin, \
                                    westSensorPin, northLEDPin, \
                                    eastLEDPin, westLEDPin, \
                                    southLEDPin, modeLEDPin);
}

Solver::~Solver(){
    delete m_diagnostics;
}

// TODO: this will return a direction
DIRECTION Solver::calculateNextMovement(){
    
    /* The next movement of the micromouse is calculated in the following way:
     * First, the diagnostics system polls all sensors
     * Then, the sensors data is interpreted in the following way.
     * Each direction is checked to see if a wall exists.
     * When a wall does not exist, that direction is added to a stack of open possible routes the mouse could take for that node.
 
     * The Solver checks the top node to see if it has been explored.    
     * When the mouse empties a stack for a node, the node is considered "explored".
     * If it hasn't, it will move to that node and repeat the process.
     * If the mouse reaches a dead end, it needs to back track to the node with multiple possibilities. (If that doesn't exist, something went wrong or the maze is unsolvable)
     *
     */
    
    m_diagnostics->update();

    if(m_diagnostics->getNorthSensor()->isWall()){
       
    }
    if(m_diagnostics->getEastSensor()->isWall()){

    }
    if(m_diagnostics->getWestSensor()->isWall()){

    }
    
    // south is ALWAYS free other than when the mouse is at start. I interpreted the mouse being at start when
    // the data structure storing the mouses movements is empty.
}

Diagnostics* Solver::getDiagnostics(){
    return m_diagnostics;
}

