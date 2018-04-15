#include <Solver.h>
#include <Button.h>

#define BUTTON_PIN A3
Button button(BUTTON_PIN, PULLDOWN);

Solver *solver;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  solver = new Solver();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(button.uniquePress()){
    Serial.println(F("Button pressed"));
    solver->nextNode();
  }
  solver->getDiagnostics()->getModeLED()->flashLED();
  delay(100);
  
}

