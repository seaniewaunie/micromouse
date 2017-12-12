/*
 * Author: Sean Graff
 * Created: 12/11/17
 * Version: 1.0
 * 
 * Diagnostics Implementation file
 */ 

#include "Arduino.h"
#include "Diagnostics.h"


Diagnostics::Diagnostics(const int northSensorPin, const int eastSensorPin, \
                         const int westSensorPin, const int northLEDPin, \
                         const int eastLEDPin, const int westLEDPin)
{ 
    m_northSensor = new Sensor(northSensorPin);
    m_eastSensor = new Sensor(eastSensorPin);
    m_westSensor = new Sensor(westSensorPin);

    m_northLED = new LED(northLEDPin);
    m_eastLED = new LED(eastLEDPin);
    m_westLED = new LED(westLEDPin);
}

Diagnostics::~Diagnostics(){
    // because the private variables are stored in dynamic memory, need to destruct them.
    delete m_northSensor;
    delete m_eastSensor;
    delete m_westSensor;
    delete m_northLED;
    delete m_eastLED;
    delete m_westLED;
}

void Diagnostics::update(){
    // upon calling update, all sensors will be polled to determine if there is a wall
    // if there is no wall, the LED associated with it will turn on

    // north Sensor
    if(m_northSensor->isWall() == false) 
        m_northLED->turnON();
    else 
        m_northLED->turnOFF();
    
    // east Sensor
    if(m_eastSensor->isWall() == false)
        m_eastLED->turnON();
    else
        m_eastLED->turnOFF();

    if(m_westSensor->isWall() == false)
        m_westLED->turnON();
    else
        m_westLED->turnOFF();
}
