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

#define LED_DELAY_MS 100
#define MAZE_LENGTH_CM 108

Diagnostics::Diagnostics() {

    m_northSensor = new Sensor(NORTH_SENSOR_PIN);
    m_eastSensor = new Sensor(EAST_SENSOR_PIN);
    m_westSensor = new Sensor(WEST_SENSOR_PIN);

    m_northLED = new LED(NORTH_LED_PIN);
    m_eastLED = new LED(EAST_LED_PIN);
    m_westLED = new LED(WEST_LED_PIN);
    m_southLED = new LED(SOUTH_LED_PIN);

    m_modeLED = new LED(MODE_LED_PIN);
}

Diagnostics::~Diagnostics(){
    // because the private variables are stored in dynamic memory, need to destruct them.
    delete m_northSensor;
    delete m_eastSensor;
    delete m_westSensor;
    delete m_northLED;
    delete m_eastLED;
    delete m_westLED;
    delete m_southLED;
    delete m_modeLED;
}

bool Diagnostics::update(){
    // upon calling update, all sensors will be polled to determine if there is a wall
    // if there is no wall, the LED associated with it will turn on

    // north Sensor
    if(m_northSensor->isWall())
        m_northLED->turnON();
    else
        m_northLED->turnOFF();

    // east Sensor
    if(m_eastSensor->isWall())
        m_eastLED->turnON();
    else
        m_eastLED->turnOFF();

    if(m_westSensor->isWall())
        m_westLED->turnON();
    else
        m_westLED->turnOFF();

    return checkWin();
}


// upon finishing a maze, the micromouse will celebrate!
void Diagnostics::celebrate(){
    for(int i = 0; i < 10; i++){
        m_northLED->turnOFF();
        m_eastLED->turnOFF();
        m_westLED->turnOFF();
        m_southLED->turnOFF();
        m_modeLED->turnOFF();
        delay(LED_DELAY_MS);

        m_northLED->turnON();
        m_eastLED->turnON();
        m_westLED->turnON();
        m_southLED->turnON();
        m_modeLED->turnON();
        delay(LED_DELAY_MS);
    }

    m_northLED->turnOFF();
    m_eastLED->turnOFF();
    m_westLED->turnOFF();
    m_southLED->turnOFF();
    m_modeLED->turnOFF();

}

// check to see if the micromouse is done
bool Diagnostics::checkWin(){
    // poll north first
    if(m_northSensor->getDistance() > MAZE_LENGTH_CM/2){
        // now poll east
        if(m_eastSensor->getDistance() > MAZE_LENGTH_CM/2){
            //now west
            if(m_westSensor->getDistance() > MAZE_LENGTH_CM/2){
                return true;
            }
        }
    }
    return false;
}

void Diagnostics::blinkLED(DIRECTION dir){
    LED *useThis;

    switch(dir){
        case N:
            useThis = m_northLED;
            break;
        case E:
            useThis = m_eastLED;
            break;
        case S:
            useThis = m_southLED;
            break;
        case W:
            useThis = m_westLED;
            break;
    }

    for(int i = 0; i < 4; i++){
        useThis->flashLED();
    }

}


Sensor* Diagnostics::getNorthSensor(){
    return m_northSensor;
}

Sensor* Diagnostics::getEastSensor(){
    return m_eastSensor;
}

Sensor* Diagnostics::getWestSensor(){
    return m_westSensor;
}

LED* Diagnostics::getNorthLED(){
    return m_northLED;
}

LED* Diagnostics::getEastLED(){
    return m_eastLED;
}

LED* Diagnostics::getWestLED(){
    return m_westLED;
}

LED* Diagnostics::getSouthLED(){
    return m_southLED;
}

LED* Diagnostics::getModeLED(){
    return m_modeLED;
}
