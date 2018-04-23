#include <Solver.h>
#include <Button.h>

#define BUTTON_PIN A2
Button button(BUTTON_PIN, PULLDOWN);

Solver *solver;

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  solver = new Solver();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(button.uniquePress()){
    delay(1000);
    Serial.println(freeRam());
    Serial.println(F("Button pressed"));
    solver->getLocomotion()->goForward();
    /*
    solver->getLocomotion()->turnLeft();
    solver->getLocomotion()->turnRight();
    solver->getLocomotion()->makeUTurn();
    solver->getLocomotion()->goForward();
    solver->getLocomotion()->makeUTurn();
    */
    //solver->nextNode();
  }
  solver->getDiagnostics()->update();
  delay(10);
  
}

