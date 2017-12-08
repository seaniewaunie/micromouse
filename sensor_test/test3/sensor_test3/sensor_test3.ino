#include "Sensor.h"

#define NORTH_SENSOR_PIN 13

// Instantiate Sensor Objects
Sensor north(NORTH_SENSOR_PIN);

void setup() {
  // set up for sensors is taken care of in the constructor
  Serial.begin(9600);
}

void loop() {
  Serial.print("North Distance: ");
  Serial.println( north.getDistance() );
  delay(1000);
}
