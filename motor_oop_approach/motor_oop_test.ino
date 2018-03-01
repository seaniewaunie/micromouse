#include <PID.h>
#include <Motor.h>
#include <Sensor.h>
using namespace std;
using namespace micromouse_pid_functions;

/* Reading rotary encoder values from single motor 
 * and adjusting duty cycle via PID 
 *  by Erfan Turdi
 */

/* Arduino only have 2 digital pins that can detect 
 * rising and falling edge of signal allowing interrupt
 */

// connect motor controller pins to Arduino digital pins
// motor one
#define LMotorEnable 10
#define LMotorIn1 9
#define LMotorIn2 8
#define LEncoderPinA 3 //Digital interrupt pin on Arduino triggered by hall effect sensor A 
#define LEncoderPinB 4 //Digital interrupt pin on Arduino triggered by hall effect sensor B



/* ROTARY ENCODER CIRCUIT CONNECTION!!
 *  
 *  Hall Sensor B Vout --> DIGITAL PIN 3
 *  Hall Sensor A Vout --> DIGITAL PIN 2
 *  Hall sensor GND --> Arduino GND 
 *  Hall sensor Vcc --> Arduino 5V
 *  +motor --> H-bridge pin 1
 *  -motor --> H-bridge pin 2
 */

Motor leftMotor;
Motor rightMotor;

void setup() {
  leftMotor = Motor(LMotorEnable,LMotorIn1,LMotorIn2,LEncoderPinA,LEncoderPinB);
  rightMotor = Motor();

  attachInterrupt(digitalPinToInterrupt(leftMotor.encoder.getEncoderAPin()),LeftEncoderEventA_ISR_Wrapper,RISING);
  attachInterrupt(digitalPinToInterrupt(leftMotor.encoder.getEncoderBPin()),LeftEncoderEventB_ISR_Wrapper,RISING); 

  moveStraight(&leftMotor,&rightMotor,18.0);
  Serial.begin(115200);

}

void loop() {
}


void LeftEncoderEventA_ISR_Wrapper() {
  leftMotor.encoder.encoderEventA_ISR();
}

void LeftEncoderEventB_ISR_Wrapper() {
  leftMotor.encoder.encoderEventB_ISR();
}

