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

#define encoderPinA 2 //Digital interrupt pin on Arduino triggered by hall effect sensor A 
#define encoderPinB 3 //Digital interrupt pin on Arduino triggered by hall effect sensor B

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
volatile signed long int revolution = 0; //stores and keep track of numbers of revolution (297 cycles/revolution)

volatile byte inputValue = 0; //to read digital values of pin 2 and 3

const float wheel_circum = 2 * PI * 1.43; //in cetimeters
unsigned long sampleDuration = 500; //in milliseconds
float sampleTime = 1/sampleDuration;

unsigned int dutyCycle = 0;
unsigned long previousMillis = 0;
float actual_distance = 0;

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
  spinMotorA(dutyCycle);
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > sampleDuration) {
    previousMillis = currentMillis;
    pid_setDutyCycle(18.0);
    Serial.print("DC: ");
    Serial.println(dutyCycle);
  }
}

void spinMotorA(unsigned int dutyCycle) {
  
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
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

#define Kp 5
#define Kd 0.05
#define Ki 0

void pid_setDutyCycle(const float desired_distance) {
  static float last_error = 0, integral = 0, derivative = 0;
  
  actual_distance = ((float)encoderPos/CPR) * wheel_circum;
  Serial.print("distance_travelled: ");
  Serial.println(actual_distance);
  
  float error = (100.0 * (desired_distance - actual_distance)/float(desired_distance));

  Serial.print("error: ");
  Serial.println(error);
  derivative = error - last_error;
  float my_dutyCycle = (error * Kp) + (derivative * Kd) + (integral * Ki);

  Serial.print("my_dutyCycle: ");
  Serial.println(my_dutyCycle);
  
  last_error = error;

  if(my_dutyCycle >= 255.0) {
    dutyCycle = 255;
  }
  else if(my_dutyCycle < 55.0) {
    dutyCycle = 0;
  }
  else {
    dutyCycle = int(my_dutyCycle);
    //dutyCycle = int((my_dutyCycle/100.0) * 255);
    integral += error*sampleTime;
  }
}
 
