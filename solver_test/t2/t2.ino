#include <Solver.h>
#include <Button.h>

// Pin Declarations
#define NORTH_SENSOR_PIN 2
#define EAST_SENSOR_PIN 3
#define WEST_SENSOR_PIN 4
  
#define NORTH_LED_PIN 5
#define EAST_LED_PIN 6
#define WEST_LED_PIN 7
#define SOUTH_LED_PIN 8

#define MODE_LED_PIN 9

#define BUTTON_PIN 10

// Instantiate Diagnostics Object
Solver solver(NORTH_SENSOR_PIN, EAST_SENSOR_PIN, WEST_SENSOR_PIN, \
                        NORTH_LED_PIN,    EAST_LED_PIN,    WEST_LED_PIN, \
                        SOUTH_LED_PIN, MODE_LED_PIN);

Button button(BUTTON_PIN, PULLDOWN);
 

//Graph test(49);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println(sizeof(Node));
  Serial.print(sizeof(dijkstra_t));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(button.uniquePress()){
  
    Serial.println("Button pressed");
    //e.DFS();
    solver.nextNode();
  }
  
  solver.getDiagnostics()->update();
  delay(50);
  
}

