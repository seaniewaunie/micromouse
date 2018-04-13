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
}

Sensor::~Sensor(){
		/* do nothing */
}

long Sensor::getDistance(){
		long duration;
	  digitalWrite(m_trigPin, LOW);
	  delayMicroseconds(2);
	  digitalWrite(m_trigPin, HIGH);
	  delayMicroseconds(10);
	  digitalWrite(m_trigPin, LOW);
	  duration = pulseIn(m_echoPin, HIGH);
	  return (duration/2) / 29.1;
}

bool Sensor::isWall(){
    if(getDistance() < CRITICAL_DISTANCE)
        return true;
    return false;
}
