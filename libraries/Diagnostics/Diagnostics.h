/*
 * Author: Sean Graff
 * Created: 12/8/17
 * Version: 1.1
 * Last Edited: 1/30/18
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
 * The MODE LED signifies which mode the micromouse is operating in. When this LED is OFF, the MM is operating in "Traversal" mode.
 * When the LED is ON, the MM is operating in "Sprint" mode.
 *
 */

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "Arduino.h"
#include "Sensor.h"
#include "LED.h"
//#include "Node.h"

enum DIRECTION{
    N,
    E,
    S,
    W
};

class Diagnostics {
  
  public:
    Diagnostics();
    Diagnostics(const int northSensorPin, const int eastSensorPin, \
                const int westSensorPin, const int northLEDPin, \
                const int eastLEDPin, const int westLEDPin, \
                const int southLEDPin, const int modeLEDPin);

    ~Diagnostics();
    bool update();
    void celebrate();
    
    void blinkLED(DIRECTION dir);

    bool checkWin();

    Sensor *getNorthSensor();
    Sensor *getEastSensor();
    Sensor *getWestSensor();
    
    LED *getNorthLED();
    LED *getEastLED();
    LED *getWestLED();
    LED *getSouthLED();
    
    LED *getModeLED();
    

  private:
    // the micromouse has 3 sensors per the Preliminary Design
    Sensor *m_northSensor;
    Sensor *m_eastSensor;
    Sensor *m_westSensor;
    
    // LED's to suppliment each sensor
    LED *m_northLED;
    LED *m_eastLED;
    LED *m_westLED;
    LED *m_southLED;

    // LED for mode of operation
    LED *m_modeLED;
};

#endif
