#include <Solver.h>
#include <Button.h>

#define BUTTON_PIN A2

Solver *solver;

Button button(BUTTON_PIN, PULLDOWN);

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  solver = new Solver();
  //Serial.println(freeRam());
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(freeRam());
  //*
  solver->getDiagnostics()->update();
  //solver->getDiagnostics()->getModeLED()->flashLED();
  if(button.uniquePress()){
    /*
    Serial.println("North, East, West");
    Serial.print(solver->getDiagnostics()->getNorthSensor()->isWall());
    Serial.print(", \t");
    Serial.print(solver->getDiagnostics()->getEastSensor()->isWall());
    Serial.print(", \t");
    Serial.println(solver->getDiagnostics()->getWestSensor()->isWall());
    */
    //Serial.println("button pressed");
    solver->getDiagnostics()->getModeLED()->flashLED();
    solver->getDiagnostics()->getModeLED()->flashLED();
    solver->getDiagnostics()->getModeLED()->flashLED();
    delay(2000);
    
    while(!solver->nextNode()); // do while returning false
  }
  
  delay(100);
  //*/
}
