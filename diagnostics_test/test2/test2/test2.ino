// Author: Sean Graff
// Description: this program demonstrates the Diagnostic System Object and implementation.

#include "Diagnostics.h"



// Instantiate Diagnostics Object
Diagnostics *diagnostics = new Diagnostics();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //for(int i = 0; i < 100; i++){
    diagnostics->update();
    Serial.println("North, East, West");
    Serial.print(diagnostics->getNorthSensor()->getDistance());
    Serial.print(", \t");
    Serial.print(diagnostics->getEastSensor()->getDistance());
    Serial.print(", \t");
    Serial.println(diagnostics->getWestSensor()->getDistance());
    delay(100);
  //}
  //diagnostics.celebrate();
  //diagnostics.getNorthLED()->flashLED();
  //delay(1000);
}
