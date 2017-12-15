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

#define LED_DELAY_MS 100

LED::LED(const int pin){
    m_pin = pin;
    pinMode(m_pin, OUTPUT);
}

LED::~LED(){
    // no dynamic memory
}

void LED::turnON(){
    digitalWrite(m_pin, HIGH);
}

void LED::turnOFF(){
    digitalWrite(m_pin, LOW);
}

void LED::flashLED(){
    turnON();
    delay(LED_DELAY_MS);
    turnOFF();
    delay(LED_DELAY_MS);
}
