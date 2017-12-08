#include "Arduino.h"
#include "Sensor.h"

// The Maximum Distance of the HC-SR04 is 400cm as per the Spec sheet
#define MAX_DISTANCE 400

#define CRITICAL_DISTANCE 16

Sensor::Sensor(const int pin){
    m_pin = pin;
    m_sonar = new NewPing(m_pin, m_pin, MAX_DISTANCE);
}

Sensor::~Sensor(){
    delete m_sonar;
}

float Sensor::getDistance(){
    return m_sonar->ping_cm();
}

bool Sensor::isWall(){
    if(getDistance() < CRITICAL_DISTANCE)
        return true;

    return false;
}
