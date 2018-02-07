// Working maze solver
// Date: 12/15/2017
// Authors: Sean and Erfan

#include <LED.h>
#include <Diagnostics.h>
#include <QueueArray.h>
#include <Maze.h>
#include <stdio.h>
  

// Pin Declarations
#define NORTH_SENSOR_PIN 13
#define EAST_SENSOR_PIN 12
#define WEST_SENSOR_PIN 11

#define NORTH_LED_PIN 7
#define EAST_LED_PIN 6
#define WEST_LED_PIN 5
#define SOUTH_LED_PIN 4

#define MODE_LED_PIN 3

// Instantiate Diagnostics Object
Diagnostics diagnostics(NORTH_SENSOR_PIN, EAST_SENSOR_PIN, WEST_SENSOR_PIN, \
                        NORTH_LED_PIN,    EAST_LED_PIN,    WEST_LED_PIN, \
                        SOUTH_LED_PIN, MODE_LED_PIN);


// TODO: create a button object
const int buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;

Maze *maze;

const int start = 7;
const int goal = 1;
int index = start;
uint8_t mutex = 0; //TODO: What is mutex doing? normally 1 -- Mutex is for the starting node -- it's making sure south is closed...
bool fistNode = true;
void setup() {
  Serial.begin(9600);
  maze = new Maze();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      uint8_t sensorD = (8*diagnostics.getNorthSensor()->isWall()) + (4*diagnostics.getEastSensor()->isWall()) + (1*diagnostics.getWestSensor()->isWall());
      //uint8_t sensorD = (8*diagnostics.getNorthSensor()->isWall()) + (4*diagnostics.getEastSensor()->isWall()) + (1*diagnostics.getWestSensor()->isWall()) + (2*mutex);
      //mutex = mutex & 0;
      //mutex = 0; // after the first node, the mutex is always 0 (because moving north causes south to be open)
      if(sensorD != 0 || diagnostics.checkWin() == false) {
        //Serial.print("currently at node: ");  Serial.println(index);
        Serial.print("SensorD: "); Serial.println(sensorD);
        //uint8_t D = maze->getNext(_maze1[index]);
        uint8_t D = maze->getNext(sensorD);
        Serial.print("D is: "); Serial.println(D);
        //index += maze->nextIndex;
        //Serial.print("next node is: "); Serial.println(index);
        lightLED(D);
        Serial.println();
      }
      else {
        if(diagnostics.checkWin()){
            diagnostics.celebrate();
            delay(2000);
            Serial.println("done");
            QueueArray<uint8_t> finalseq = maze->getPath();
            while(!finalseq.isEmpty()) {
              lightLED(finalseq.pop());
              delay(1000);       
            }
            exit(0);
        } // check win
      }
    }
      delay(50);
  }
  lastButtonState = buttonState;
  diagnostics.update();
  delay(50);
}

// function for notifying turning -- flashes LED a few times
void lightLED(uint8_t D) {
  for(int i = 0; i < 10; i++){
    switch(D) {
      case N: Serial.println("N"); diagnostics.getNorthLED()->flashLED(); break;
      case E: Serial.println("E"); diagnostics.getEastLED()->flashLED(); break;
      case S: Serial.println("S"); diagnostics.getSouthLED()->flashLED(); break;
      case W: Serial.println("W"); diagnostics.getWestLED()->flashLED(); break;
      }
  }
}
