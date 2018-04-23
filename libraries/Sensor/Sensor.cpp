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
#define MIN_DISTANCE 0

#define CRITICAL_DISTANCE 16 // we determined 16 to be the critical distance

Sensor::Sensor(){
    /* do nothing */
}

Sensor::Sensor(const int trigPin, const int echoPin){
    m_trigPin = trigPin;
    m_echoPin = echoPin;
    /* Arduino Setting Code */
    pinMode(m_trigPin, OUTPUT);
    pinMode(m_echoPin, INPUT);

    m_sonar = new NewPing(trigPin, echoPin, MAX_DISTANCE);
}

Sensor::~Sensor(){
    delete m_sonar;
}

long Sensor::getDistance(){
    long duration;
    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin, LOW);
    duration = pulseIn(m_echoPin, HIGH);

    long distance = duration/2/29.1;
    // if it's greater than this distance, an error occured
    if(distance < MAX_DISTANCE)
        return distance;
    else
        return MAX_DISTANCE;


}

float Sensor::ping(){
    return m_sonar->ping_cm();
}

bool Sensor::isWall(){
    if(ping() < CRITICAL_DISTANCE)
        return true;
    return false;
}
