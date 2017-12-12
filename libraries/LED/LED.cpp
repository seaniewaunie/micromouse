/*
 * Author: Sean Graff
 * Created: 12/11/17
 * Version: 1.0
 *
 * LED Implementation file
 *
 */ 


#include "Arduino.h"
#include "LED.h"

#define SENSOR_DELAY_MS 100

LED::LED(const int pin){
    m_pin = pin;
    pinMode(m_pin, OUTPUT);
}

LED::~LED(){
    // no dynamic memory
}

LED::turnON(){
    digitalWrite(m_pin, HIGH);
}

LED::turnOFF(){
    digitalWrite(m_pin, LOW);
}

LED::flashLED(){
    turnON();
    delay(SENSOR_DELAY_MS);
    turnOFF();
}
