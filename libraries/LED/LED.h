/*
 * Author: Sean Graff
 * Created: 12/11/17
 * Version: 1.0
 * 
 * Description: This LED object will allow for quick instancing of LED objects
 * and will be supplimenting the Diagnostic system specifically.
 *
 * turnON() turns the LED on
 *
 * turnOFF() turns the LED off
 *
 * flashLED() repeatedly turns the LED on and off
 *
 */

#ifndef LED_H
#define LED_H

#include "Arduino.h"

class LED {
  
  public:
    LED(const int pin);
    ~LED();
    void turnON();
    void turnOFF();
    void flashLED();

  private:
    int m_pin;
};

#endif
