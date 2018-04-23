#include <Locomotion.h>
#include <Button.h>

#define BUTTON_PIN A2
/* Reading rotary encoder values from single motor 
 * and adjusting duty cycle via PID 
 *  by Erfan Turdi
 */

/* Arduino only have 2 digital pins that can detect 
 * rising and falling edge of signal allowing interrupt
 */

/* ROTARY ENCODER CIRCUIT CONNECTION!!
 *  
 *  Hall Sensor B Vout --> DIGITAL PIN 3
 *  Hall Sensor A Vout --> DIGITAL PIN 2
 *  Hall sensor GND --> Arduino GND 
 *  Hall sensor Vcc --> Arduino 5V
 *  +motor --> H-bridge pin 1
 *  -motor --> H-bridge pin 2
 */

Button button(BUTTON_PIN, PULLDOWN);
Locomotion* loco = new Locomotion();

void setup() {
  Serial.begin(115200);
}

void loop() {
  
  if(button.uniquePress()){
    loco->goForward();
    loco->goForward();
    loco->goForward();
    loco->turnRight();
    //delay(2000);
    //loco->turnRight();
    //delay(2000);
    //loco->turnLeft();
    //delay(2000);
    //loco->makeUTurn();
  }
}

