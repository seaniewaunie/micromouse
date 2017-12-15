/*
 * Author: Sean Graff
 * Created: 12/8/17
 * Version: 1.0
 * 
 * Description: The diagnostic system allows for visual inspection to ensure that the Micromouse
 * is performing as expected. For our purpose, it will also serve as a tool to demonstrate 
 * the progress that the Micromouse is making
 *
 * The Diagnostic Object requires 6 pins, 1 for each sensor and 1 for each LED in the North, East, and West directions
 *
 * update() polls each sensor's "isWall()" function, then calls "turnON()" or "flashLED()" for the respective
 * sensors LED object. This function would ideally be called often
 *
 * As described in the Preliminary design, an LED will light up when there is no wall within critical distance of the sensor,
 * and an LED will flash when the Micromouse is turning
 *
 * For the demonstration and this version of the file, the diagnostic system will not diagnose the act of turning
 *
 */

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "Arduino.h"
#include "Sensor.h"
#include "LED.h"

class Diagnostics {
  
  public:
    Diagnostics(const int northSensorPin, const int eastSensorPin, \
                const int westSensorPin, const int northLEDPin, \
                const int eastLEDPin, const int westLEDPin);

    ~Diagnostics();
    void update();

    Sensor *getNorthSensor();
    Sensor *getEastSensor();
    Sensor *getWestSensor();
    
    LED *getNorthLED();
    LED *getEastLED();
    LED *getWestLED();


  private:
    // the micromouse has 3 sensors per the Preliminary Design
    Sensor *m_northSensor;
    Sensor *m_eastSensor;
    Sensor *m_westSensor;
    
    // LED's to suppliment each sensor
    LED *m_northLED;
    LED *m_eastLED;
    LED *m_westLED;
};

#endif
