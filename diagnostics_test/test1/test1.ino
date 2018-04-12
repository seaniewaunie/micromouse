// Author: Sean Graff
// Description: this program demonstrates the Diagnostic System Object and implementation.

#include "Diagnostics.h"

// Pin declarations for Sensors
#define NORTH_SENSOR_PIN 13
#define EAST_SENSOR_PIN 12
#define WEST_SENSOR_PIN 11

// Pin declarations for LED's
#define MODE_LED_PIN A5
#define SOUTH_LED_PIN A4
#define WEST_LED_PIN A3
#define EAST_LED_PIN A2
#define NORTH_LED_PIN A1

// Instantiate Diagnostics Object
Diagnostics diagnostics(NORTH_SENSOR_PIN, WEST_SENSOR_PIN, EAST_SENSOR_PIN, \
                        NORTH_LED_PIN,    WEST_LED_PIN,    EAST_LED_PIN,    \
                        SOUTH_LED_PIN, MODE_LED_PIN);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  //for(int i = 0; i < 100; i++){
    diagnostics.update();
    delay(100);
  //}
  //diagnostics.celebrate();
  //diagnostics.getNorthLED()->flashLED();
  //delay(1000);
}
