#include <Sensor.h>

/* Reading rotary encoder values from single motor 
 * and adjusting duty cycle via PID 
 *  by Erfan Turdi
 */

/* Arduino only have 2 digital pins that can detect 
 * rising and falling edge of signal allowing interrupt
 */

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;

int in1V = HIGH;
int in2V = LOW;

#define encoderPinA 2 //Digital interrupt pin on Arduino triggered by hall effect sensor A 
#define encoderPinB 3 //Digital interrupt pin on Arduino triggered by hall effect sensor B
#define sensorPin 13  //Sensor trig pin

Sensor sensor(sensorPin);

/* ROTARY ENCODER CIRCUIT CONNECTION!!
 *  
 *  Hall Sensor B Vout --> DIGITAL PIN 3
 *  Hall Sensor A Vout --> DIGITAL PIN 2
 *  Hall sensor GND --> Arduino GND 
 *  Hall sensor Vcc --> Arduino 5V
 *  +motor --> H-bridge pin 1
 *  -motor --> H-bridge pin 2
 */

/* Motor specifications */
#define CPR 297 //cycles per revolution
#define EPC 4 //events per cycle
#define EPR 1188 //events per revolution

volatile signed long int encoderPos = 0; //stores and keep track of numbers of cycles (motor shaft)

volatile byte inputValue = 0; //to read digital values of pin 2 and 3

const float wheel_circum = 2 * PI * 0.43; //in cetimeters
unsigned long encoderSampleDuration = 300, sensorSampleDuration = 500;//in milliseconds
float encoderSampleTime = 1/encoderSampleDuration, sensorSampleTime = 1/sensorSampleDuration;

unsigned int encoderDutyCycle, sensorDutyCycle, combinedDutyCycle = 0;
unsigned long encoderPreviousMillis = 0, sensorPreviousMillis = 0;

void setup() {

  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  //attaching interrupt service routine to digital pins
  //i.e. encoderA_ISR will be called if pin 2 detects rising edge
  attachInterrupt(digitalPinToInterrupt(encoderPinA),encoderA_ISR,RISING);
  attachInterrupt(digitalPinToInterrupt(encoderPinB),encoderB_ISR,RISING);

  Serial.begin(115200);
  Serial.println(encoderPos);
 
}

void loop() {
  /* motor code */
  spinMotorA(combinedDutyCycle);
  
  unsigned long currentMillis = millis();

  // encoder sampling
  if(currentMillis - encoderPreviousMillis > encoderSampleDuration) {
    encoderPreviousMillis = currentMillis;
    encoderPID_setDutyCycle(18.0);
  }

  currentMillis = millis();
  if(currentMillis - sensorPreviousMillis > sensorSampleDuration) {
    sensorPreviousMillis = currentMillis;
    sensorPID_setDutyCycle(5.3);
  }

  combinedDutyCycle = int(encoderDutyCycle + 0.2*sensorDutyCycle);
}

void spinMotorA(unsigned int dutyCycle) {
  
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, in1V);
  digitalWrite(in2, in2V);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, dutyCycle);
}

void encoderA_ISR() {

  inputValue = (PIND & B00001100);
  if(inputValue == B00001100) {
    encoderPos--;
  }
}

void encoderB_ISR() {

  inputValue = (PIND & B00001100);
  if(inputValue == B00001100) {
    encoderPos++;
  }
}

#define Sp 1
#define Sd 0
#define Si 0

void sensorPID_setDutyCycle(const float desired_distance) {
  static float last_error = 0, integral = 0, derivative = 0;
  
  float actual_distance = sensor.getDistance();
  Serial.print("distance_away: ");
  Serial.println(actual_distance);

  float error = (100.0 * (desired_distance - actual_distance)/float(desired_distance));
  Serial.print("error: ");
  Serial.println(error);
  
  derivative = last_error - error;
  
  float my_dutyCycle = (error * Sp) + (derivative * Sd) + (integral * Si);
  
  Serial.print("my_dutyCyle: ");
  Serial.println(my_dutyCycle);
  
  last_error = error;
    
  if(my_dutyCycle >= 255.0) {
    sensorDutyCycle = 255;
  }
  else if(my_dutyCycle < 50.0) {
    sensorDutyCycle = 0;
  }
  else {
    sensorDutyCycle = int(my_dutyCycle);
    integral += error;
  }
}

#define Ep 4
#define Ed 0.33
#define Ei 0.5

void encoderPID_setDutyCycle(const float desired_distance) {
  static float last_error = 0, integral = 0, derivative = 0;
  
  float actual_distance = ((float)encoderPos/CPR) * wheel_circum;
  Serial.print("distance_travelled: ");
  Serial.println(actual_distance);

  float error = 100.0 * ((desired_distance - actual_distance)/desired_distance);
  Serial.print("error: ");
  Serial.println(error);
  
  derivative = (last_error - error);

  float my_dutyCycle = (error * Ep) + (derivative * Ed) + (derivative * Ei);
  
  Serial.print("my_dutyCyle: ");
  Serial.println(my_dutyCycle);
  
  if(error*last_error < 0) {
    flipPolarity();
  }
  
  last_error = error;
   
  my_dutyCycle = abs(my_dutyCycle);
  
  if(my_dutyCycle >= 255.0) {
    encoderDutyCycle = 255;
  }
  else if(my_dutyCycle < 50.0) {
    encoderDutyCycle = 0;
  }
  else {
    encoderDutyCycle = int(my_dutyCycle);
    integral += error;
  }
}

void flipPolarity() {
  if(in1V == HIGH && in2V == LOW) {
    in1V = LOW;
    in2V = HIGH;
  }
  else {
    in1V = HIGH;
    in2V = LOW;
  }
}
 
