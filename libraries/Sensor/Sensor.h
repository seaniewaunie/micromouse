/*
 * Author: Sean Graff
 * Created: 4/14/17
 * Version: 2.0
 *
 * Description: The sensor header file provides 3 functions to be used
 * by the micromouse control system.
 *
 * The constructor is initialized with the pin that the Trig/Echo is connected to for the sensor object.
 * Note, the Sensor now requires two pins for the Trigger/Echo.
 *
 * getDistance() returns the distance from an object.
 *
 * isWall() returns true/false if there is a wall within critical distance defined as 16 cm.
 */

#ifndef SENSOR_H
#define SENSOR_H

#include "Arduino.h"
//#include "NewPing.h"

class Sensor {

  public:
    Sensor();
    Sensor(const int, const int);
    ~Sensor();
    long getDistance();
    float ping();
    bool isWall();

  private:
    //NewPing *m_sonar;

    int m_trigPin;
    int m_echoPin;
};

#endif
