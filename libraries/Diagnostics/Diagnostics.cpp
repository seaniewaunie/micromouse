/*
 * Author: Sean Graff
 * Created: 12/11/17
 * Version: 1.3
 * Last Edit: 1/30/18
 *
 * Diagnostics Implementation file
 */

#include "Arduino.h"
#include "Diagnostics.h"
#include "Locomotion.h"

#define LED_DELAY_MS 100
#define MAZE_LENGTH_CM 108

Diagnostics::Diagnostics() {

/*
    m_northSensor = new Sensor(NORTH_SENSOR_TRIG_PIN, NORTH_SENSOR_ECHO_PIN);
    m_eastSensor = new Sensor(EAST_SENSOR_TRIG_PIN, EAST_SENSOR_ECHO_PIN);
    m_westSensor = new Sensor(WEST_SENSOR_TRIG_PIN, WEST_SENSOR_ECHO_PIN);
*/
    m_modeLED = new LED(MODE_LED_PIN);
}

Diagnostics::~Diagnostics(){
    // because the private variables are stored in dynamic memory, need to destruct them.
  /*  delete m_northSensor;
    delete m_eastSensor;
    delete m_westSensor;
    delete m_modeLED;
*/
}

bool Diagnostics::update(){

    return checkWin();
}


// upon finishing a maze, the micromouse will celebrate!
void Diagnostics::celebrate(){
    for(int i = 0; i < 10; i++){
        m_modeLED->turnOFF();
        delay(LED_DELAY_MS);

        m_modeLED->turnON();
        delay(LED_DELAY_MS);
    }
    m_modeLED->turnOFF();
}

// check to see if the micromouse is done
bool Diagnostics::checkWin(){
    // poll north first
    /*
    if(m_northSensor->getDistance() > MAZE_LENGTH_CM/2){
        // now poll east
        if(m_eastSensor->getDistance() > MAZE_LENGTH_CM/2){
            //now west
            if(m_westSensor->getDistance() > MAZE_LENGTH_CM/2){
                return true;
            }
        }
    }
    */
    
    if(fSensor->getDistance() > MAZE_LENGTH_CM/2){
        // now poll east
        if(rSensor->getDistance() > MAZE_LENGTH_CM/2){
            //now west
            if(lSensor->getDistance() > MAZE_LENGTH_CM/2){
                return true;
            }
        }
    }

    return false;
}

void Diagnostics::blinkLED(DIRECTION dir){
    // Do nothing
}


Sensor* Diagnostics::getNorthSensor(){
//    return m_northSensor;
    return fSensor;
}

Sensor* Diagnostics::getEastSensor(){
    //return m_eastSensor;
    return rSensor;
}

Sensor* Diagnostics::getWestSensor(){
    //return m_westSensor;
    return lSensor;
}

LED* Diagnostics::getModeLED(){
    return m_modeLED;
}
