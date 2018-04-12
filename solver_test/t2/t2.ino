#include <Solver.h>
#include <Button.h>
#include <Locomotion.h>


// Pin Declarations
#define NORTH_SENSOR_PIN 13
#define EAST_SENSOR_PIN 12
#define WEST_SENSOR_PIN 11
  
#define MODE_LED_PIN A5
#define SOUTH_LED_PIN A4
#define WEST_LED_PIN A3
#define EAST_LED_PIN A2
#define NORTH_LED_PIN A1

//#define BUTTON_PIN 0



// Instantiate Objects

//Button button(BUTTON_PIN, PULLDOWN);

Solver solver = Solver();
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println(sizeof(Node));
  //Serial.print(sizeof(dijkstra_t));
  //loco = new Locomotion();
  //loco->goForward();

  delay(1000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  //if(button.uniquePress()){
  //delay(1000);
    //Serial.println("Button pressed");
    //e.DFS();
    solver.nextNode();
  //}
  solver.getDiagnostics()->update();
  delay(50);
  
}

