/*
 * Author: Sean Graff
 * Created: 12/8/17
 * Version: 1.0
 * 
 * Sensor Implementation file
 */ 

#include "Arduino.h"
#include "Sensor.h"

// The Maximum Distance of the HC-SR04 is 400cm as per the Spec sheet
#define MAX_DISTANCE 400
#define MIN_DISTANCE 4

#define CRITICAL_DISTANCE 16 // we determined 16 to be the critical distance

Sensor::Sensor(const int pin){
    m_pin = pin;
    m_sonar = new NewPing(m_pin, m_pin, MAX_DISTANCE);
}

Sensor::~Sensor(){
    delete m_sonar;
}

float Sensor::getDistance(){
    float ret;
    ret = m_sonar->ping_cm();
    if(ret >= MIN_DISTANCE && ret <= MAX_DISTANCE)
        return m_sonar->ping_cm();
    else
        return MAX_DISTANCE;
    
}

bool Sensor::isWall(){
    if(getDistance() < CRITICAL_DISTANCE)
        return true;

    return false;
}
