/*
 * Author: Sean Graff
 * Created: 12/11/17
 * Version: 1.1
 * 
 * Diagnostics Implementation file
 */ 

#include "Arduino.h"
#include "Diagnostics.h"

#define LED_DELAY_MS 100

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
}


// upon finishing a maze, the micromouse will celebrate!
void Diagnostics::celebrate(){
    for(int i = 0; i < 10; i++){
        m_northLED->turnON();
        m_eastLED->turnON();
        m_westLED->turnON();
        delay(LED_DELAY_MS);
        m_northLED->turnOFF();
        m_eastLED->turnOFF();
        m_westLED->turnOFF();
        delay(LED_DELAY_MS);
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
