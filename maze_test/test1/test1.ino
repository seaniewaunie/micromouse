#include <LED.h>
#include <QueueArray.h>
#include <Maze.h>
#include <sensor.h>
#include <stdio.h>

const int buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;

const LED northLED(7);
const LED eastLED(5);
const LED westLED(6);
const LED southLED(4);

Maze* maze;

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
        /* sensor call
         *   uint8_t sensorD = (8*northSensor.isWall()) + (4*eastSensor.isWall()) + (1*wastSensor.isWall()) + (2*mutex);
         *   mutex = rshift(mutex,1);
         */
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
}

void lightLED(uint8_t D) {
  switch(D) {
    case N: Serial.println("N"); northLED.flashLED(); break;
    case E: Serial.println("E"); eastLED.flashLED(); break;
    case S: Serial.println("S"); southLED.flashLED(); break;
    case W: Serial.println("W"); westLED.flashLED(); break;
    }
}
