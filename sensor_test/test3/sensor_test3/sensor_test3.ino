#include "Sensor.h"

#define NORTH_SENSOR_PIN 13
#define EAST_SENSOR_PIN 12
#define WEST_SENSOR_PIN 11

// Instantiate Sensor Objects
Sensor north(NORTH_SENSOR_PIN);
Sensor east(EAST_SENSOR_PIN);
Sensor west(WEST_SENSOR_PIN);

void setup() {
  // set up for sensors is taken care of in the constructor
  Serial.begin(9600);
}

void loop() {
  Serial.print("North Distance: ");
  Serial.println( north.getDistance() );

  Serial.print("East Distance: ");
  Serial.println( east.getDistance() );

  Serial.print("West Distance: ");
  Serial.println( west.getDistance() );
  delay(1000);
  
}
