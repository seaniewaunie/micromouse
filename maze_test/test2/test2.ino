#include <LED.h>
#include <QueueArray.h>
#include <Maze.h>
#include <sensor.h>
#include <stdio.h>
#include <Diagnostics.h>

// Pin Declarations
#define NORTH_SENSOR_PIN 13
#define EAST_SENSOR_PIN 12
#define WEST_SENSOR_PIN 11

#define NORTH_LED_PIN 7
#define EAST_LED_PIN 6
#define WEST_LED_PIN 5
#define SOUTH_LED_PIN 4


// Instantiate Diagnostics Object
Diagnostics diagnostics(NORTH_SENSOR_PIN, WEST_SENSOR_PIN, EAST_SENSOR_PIN, \
                        NORTH_LED_PIN,    WEST_LED_PIN,    EAST_LED_PIN);


// TODO: create a button object
const int buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;


LED southLED(SOUTH_LED_PIN);

Maze *maze;

const int start = 7;
const int goal = 1;
int index = start;
uint8_t mutex = 1;

void setup() {
  Serial.begin(9600);
  maze = new Maze();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      
      if(index != goal) {
        Serial.print("currently at node: ");  Serial.println(index);
        //* sensor call
        uint8_t sensorD = (8*diagnostics.getNorthSensor()->isWall()) + (4*diagnostics.getWestSensor()->isWall()) + (1*diagnostics.getWestSensor()->isWall()) + (2*mutex);
        mutex = rshift(mutex,1);
        
        uint8_t D = maze->getNext(_maze1[index]);
        index += maze->nextIndex;
        Serial.print("next node is: "); Serial.println(index);
        lightLED(D);
        Serial.println();
      }
      else {
        QueueArray<uint8_t> finalseq = maze->getPath();
        while(!finalseq.isEmpty()) {
          lightLED(finalseq.pop());
          delay(1000);       
        }
        exit(0);
      }
      } else {
        /* empty */
      }
      delay(50);
  }
  lastButtonState = buttonState;
  diagnostics.update();
}

// function for notifying turning -- flashes LED a few times
void lightLED(uint8_t D) {
  for(int i = 0; i < 10; i++){
    switch(D) {
      case N: Serial.println("N"); diagnostics.getNorthLED()->flashLED(); break;
      case E: Serial.println("E"); diagnostics.getEastLED()->flashLED(); break;
      case S: Serial.println("S"); southLED.flashLED(); break;
      case W: Serial.println("W"); diagnostics.getWestLED()->flashLED(); break;
      }
  }
}
