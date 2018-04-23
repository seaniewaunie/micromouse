/*
 * Author: Sean Graff
 * Created: 12/8/17
 * Version: 2.0
 * Last Edited: 4/13/18
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
 ***** Due to memory constraints, the LED functionality had to be removed.
 *
 */

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "Arduino.h"
#include "Sensor.h"
#include "LED.h"
//#include "Node.h"

#define NORTH_SENSOR_TRIG_PIN A0
#define NORTH_SENSOR_ECHO_PIN A1
#define EAST_SENSOR_TRIG_PIN 13
#define EAST_SENSOR_ECHO_PIN 4
#define WEST_SENSOR_TRIG_PIN A3
#define WEST_SENSOR_ECHO_PIN A4

#define MODE_LED_PIN LED_BUILTIN

enum DIRECTION{
    N,
    E,
    S,
    W
};

class Diagnostics {

  public:
    Diagnostics();

    ~Diagnostics();

    bool update();
    void celebrate();

    void blinkLED(DIRECTION dir);

    bool checkWin();

    Sensor *getNorthSensor();
    Sensor *getEastSensor();
    Sensor *getWestSensor();

    LED *getModeLED();


  private:
    // the micromouse has 3 sensors per the Preliminary Design
    Sensor *m_northSensor;
    Sensor *m_eastSensor;
    Sensor *m_westSensor;

    // LED for mode of operation
    LED *m_modeLED;
};

#endif
