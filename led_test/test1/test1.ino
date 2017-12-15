// Author: Sean Graff
// Description: this program demonstrates the LED object, using 3 led's and repeatedly turning each on on then off, the flashes each one 
// ten times

#include "LED.h"

#define NORTH_LED_PIN 7
#define EAST_LED_PIN 6
#define WEST_LED_PIN 5

// Instantiate LED Objects
LED north_led(NORTH_LED_PIN);
LED west_led(WEST_LED_PIN);
LED east_led(EAST_LED_PIN);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  north_led.turnON();
  delay(1000);
  north_led.turnOFF();
  delay(1000);
  
  west_led.turnON();
  delay(1000);
  west_led.turnOFF();
  delay(1000);
  
  east_led.turnON();
  delay(1000);
  east_led.turnOFF();
  delay(1000);

  for(int i = 0; i < 10; i++){
    north_led.flashLED();
  }
  for(int i = 0; i < 10; i++){
    west_led.flashLED();
  }
  for(int i = 0; i < 10; i++){
    east_led.flashLED();
  }

  // random craziness
  for(int i = 0; i < 100; i++){
    if(i%2 == 0) north_led.flashLED();
    if(i%4 == 0) west_led.flashLED();
    if(i%8 == 0) east_led.flashLED();
    if(i%9 == 0){
      north_led.turnON();
      west_led.turnON();
      east_led.turnON();
    }
  }
  
}
